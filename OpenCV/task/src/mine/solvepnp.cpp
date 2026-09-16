#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>

//灯条
struct lightBar
{
    cv::RotatedRect rect;
    cv::Point2f center;
    cv::Point2f top;
    cv::Point2f bottom;
};

//灯条长轴端点
void lightBarPoints(lightBar & bar)
{
    // 确保长轴为垂直方向
    if (bar.rect.size.width < bar.rect.size.height) {
        bar.rect.angle = 90.0f; // 若宽度<高度，旋转角度修正为90度（竖直）
        std::swap(bar.rect.size.width, bar.rect.size.height); // 交换长宽，保证长轴为高度
    }

    // 长轴方向竖直（y轴负方向为上，正方向为下）
    float length = bar.rect.size.height;
    bar.top = bar.center + cv::Point2f(0, -length / 2.0f);   // 顶端（向上）
    bar.bottom = bar.center + cv::Point2f(0, length / 2.0f); // 底端（向下）
}



int main()
{
    //相机内参
    cv::Mat cameraMatrix = (cv::Mat_<double>(3,3) <<
        2422.61547, 0, 706.68406, //fx, 0, cx
        0, 2420.80771, 564.29241, //0, fy, cy
        0, 0, 1 //0, 0, 1
    );

    //畸变系数
    cv::Mat distCoeffs = (cv::Mat_<double>(5,1) << 
        -0.018647, 0.084359, -0.000925, 0.000312, 0.000000);

    //装甲板坐标（装甲板中心为原点，与imagePoints对应）
    //cv::Point3f - float，2.0会被隐式转换成double
    float LIGHTBAR_LENGTH = 5.6f; // 灯条长度（mm）
    float ARMOR_WIDTH = 13.5f; //装甲板宽度（mm）
    std::vector<cv::Point3f> objectPoints
    {
        {-ARMOR_WIDTH / 2.0f, -LIGHTBAR_LENGTH / 2.0f, 0}, //左上（x，y，z）
        {ARMOR_WIDTH / 2.0f, -LIGHTBAR_LENGTH / 2.0f, 0}, //右上
        {ARMOR_WIDTH / 2.0f, LIGHTBAR_LENGTH / 2.0f, 0}, //右下
        {-ARMOR_WIDTH / 2.0f, LIGHTBAR_LENGTH / 2.0f, 0} //左下
    };


    //滑块调整阈值
    int Threshold = 255;
    cv::namedWindow("Trackbars", (640, 200)); 
    cv::createTrackbar("Threshold", "Trackbars", &Threshold, 255);

    //打开视频
    cv::VideoCapture cap("/home/emmm/Desktop/scnu_rm/OpenCV/task/img/task2_video.mp4");
    if(!cap.isOpened())
    {
        std::cout << "Error opening video stream or file" << std::endl;
        return -1;
    }

    while(true)
    {
        cv::Mat frame;
        cap >> frame;
        if(frame.empty())
        {
            break;
        }

        //预处理
        cv::Mat channels[3];
        cv::Mat binary, Gaussian;
        int MaxVal = 255;
        cv::Size GaussianBlurKernel = cv::Size(5,5);
        cv::split(frame, channels); //分离通道
        cv::threshold(channels[2], binary, Threshold, MaxVal, 0); //二值化
        cv::GaussianBlur(binary, Gaussian, GaussianBlurKernel, 0); //高斯模糊

        //轮廓检测
        std::vector< std::vector <cv::Point> > contours;
        std::vector< cv::Vec4i > hierarchy;
        cv::findContours(Gaussian, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

        //筛选灯条
        std::vector<lightBar> lightBars;
        for(size_t i=0; i<contours.size(); i++)
        {
            double area = contourArea(contours[i]);
            if(area < 50.0) continue; //面积过滤

            //最小外接矩形
            cv::RotatedRect minRect = cv::minAreaRect(contours[i]);

            //长宽比检测
            float width = minRect.size.width;
            float height = minRect.size.height;
            if(width == 0 || height == 0) continue; //防止除零
            float aspectRatio = std::max(width, height) / std::min(width, height);
            if(aspectRatio >= 1.3 && std::max(height, width)>36)
            {
                //存储灯条信息
                lightBar bar;
                bar.rect = minRect;
                bar.center = minRect.center;
                lightBarPoints(bar); //计算灯条长轴端点
                lightBars.push_back(bar);

                //绘制最小外接矩形
                cv::Point2f vertices[4];
                minRect.points(vertices);
                for(int j=0; j<4; j++)
                {
                    cv::line(frame, vertices[j], vertices[(j+1)%4], cv::Scalar(0,255,0), 5);
                }
            }
        }

        //当检测到两个灯条时，框选并解算PnP
        if(lightBars.size() == 2)
        {
            lightBar& bar1 = lightBars[0];
            lightBar& bar2 = lightBars[1];

            // 两个灯条的所有顶点
            std::vector<cv::Point2f> allVertices;
            // 左灯条的4个顶点
            cv::Point2f leftVertices[4];
            bar1.rect.points(leftVertices); // 用旋转矩形的points()方法获取4个顶点
            allVertices.insert(allVertices.end(), leftVertices, leftVertices+4); // 向allVertices的末尾插入leftVertices中的4个元素
            // 右灯条的4个顶点
            cv::Point2f rightVertices[4];
            bar2.rect.points(rightVertices);
            allVertices.insert(allVertices.end(), rightVertices, rightVertices+4);

            // 大矩形的最小/最大x、y
            float minX = allVertices[0].x, maxX = allVertices[0].x; //初始化
            float minY = allVertices[0].y, maxY = allVertices[0].y; //初始化
            for(const auto& pt : allVertices) //pt相当于allVertices[i]
            {
                minX = std::min(minX, pt.x);
                maxX = std::max(maxX, pt.x);
                minY = std::min(minY, pt.y);
                maxY = std::max(maxY, pt.y);
            }
            // 大矩形的4个顶点
            cv::Point2f rectVertices[4] = {
                cv::Point2f(minX, minY),    // 左上
                cv::Point2f(maxX, minY),    // 右上
                cv::Point2f(maxX, maxY),    // 右下
                cv::Point2f(minX, maxY)     // 左下
            };

            // 绘制大矩形
            for(int i=0; i<4; i++)
            {
                cv::line(frame, rectVertices[i], rectVertices[(i+1)%4], cv::Scalar(0,0,255), 2);
            }

            //pnp解算
            std::vector<cv::Point2f> imagePoints(rectVertices, rectVertices+4);
            cv::Mat rvec, tvec;
            cv::solvePnP(objectPoints, imagePoints, cameraMatrix, distCoeffs, rvec, tvec);

            //输出xyz坐标（相机坐标系，mm）
            std::cout << tvec.at<double>(0) << ", " << tvec.at<double>(1) << ", " << tvec.at<double>(2) << std::endl;
        }

        cv::imshow("Gaussian", Gaussian);
        cv::imshow("Frame", frame);
        if(cv::waitKey(100) == 27)
        {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}





//rect.angle —— 旋转矩形的旋转角度
// float
// 旋转矩形相对于x 轴正方向的旋转角度，单位为度
// 以矩形的宽边（较短边） 为基准，角度范围通常在 [-90°, 0°) 或 [0°, 90°)（具体取决于宽高的相对大小）。
// 角度为正时，矩形逆时针旋转；角度为负时，顺时针旋转

//std::vector::insert —— 在向量的指定位置插入元素
// iterator insert(iterator position, const T& value); //插入单个元素
// iterator insert(iterator position, size_t count, const T& value); //插入多个相同元素
// template <class InputIt>
// iterator insert(iterator position, InputIt first, InputIt last); //插入一个范围的元素
// 将 [first, last) 范围内的所有元素插入到 position 位置