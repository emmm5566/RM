#include <opencv2/opencv.hpp>
#include <algorithm> //std::max,std::min



//匹配的灯条
struct LightBarPair
{   
public:
    cv::RotatedRect left;
    cv::RotatedRect right;
    bool isMatched;

    //构造函数
    LightBarPair() : isMatched(false) {}
    LightBarPair(const cv::RotatedRect& l, const cv::RotatedRect& r) : left(l), right(r), isMatched(true) {}
};



void preProcessing(const cv::Mat& img, cv::Mat& result);
std::vector<cv::RotatedRect> detectLightBars(const cv::Mat& img);
LightBarPair matchLightBarPair(const std::vector<cv::RotatedRect>& lightBars);
void drawAllLightBars(cv::Mat img, const std::vector<cv::RotatedRect>& lightBars);
void drawDetectionResult(cv::Mat& img, const LightBarPair& lightPair);



int main()
{
    cv::VideoCapture cap("/home/emmm/Desktop/scnu_rm/OpenCV/task/img/task2_video.mp4");
    if(!cap.isOpened())
    {
        std::cout << "Error opening video stream or file" << std::endl;
        return -1;
    }

    cv::Mat frame, imgPre;
    while(true)
    {
        cap >> frame;
        if(frame.empty())
        {
            break;
        }

        //预处理
        preProcessing(frame, imgPre);

        //检测灯条
        std::vector<cv::RotatedRect> lightBars = detectLightBars(imgPre);
        
        //匹配成对灯条
        LightBarPair matchedPair = matchLightBarPair(lightBars);

        //绘制结果
        drawAllLightBars(frame, lightBars); //绘制所有单个灯条
        drawDetectionResult(frame, matchedPair); //绘制配对成功的灯条

        cv::imshow("Image Preprocess", imgPre);
        cv::imshow("Armor Detection", frame);

        if(cv::waitKey(30) == 27) // ESC键退出
        {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}



//预处理
void preProcessing(const cv::Mat& img, cv::Mat& result)
{
    cv::Mat binary, Gaussian, erode;
    cv::Mat channels[3]; //通道分离结果
    int Threshold = 220; //二值化阈值
    int MaxVal = 255; //二值化最大值
    cv::Size GaussianKernel = cv::Size(5, 5); //高斯模糊核
    cv::Mat kernel = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3)); //形态学操作核

    if(img.empty())
    {
        result = cv::Mat();
        return;
    }

    //通道分离：将BGR图像拆为3个单通道channels[3]
    cv::split(img, channels); 
    //红色通道二值化：提取高亮度红色区域
    cv::threshold(channels[2], binary, Threshold, MaxVal, 0);
    //高斯模糊：平滑图像，减少高频噪声（如红色背景杂点）
    cv::GaussianBlur(binary, Gaussian, GaussianKernel, 0);
    //形态学操作：先腐蚀去噪，再膨胀恢复灯条轮廓
    cv::erode(Gaussian, erode, kernel);
    cv::dilate(erode, result, kernel);
}



//检测灯条
std::vector<cv::RotatedRect> detectLightBars(const cv::Mat& img)
{
    std::vector< cv::RotatedRect> lightBars;

    //检测轮廓
    std::vector< std::vector <cv::Point> > contours; //轮廓
    std::vector< cv::Vec4i > hierarchy; //轮廓层级关系
    cv::findContours(img, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    //筛选灯条轮廓
    double minAspectRatio = 1.5;  // 灯条最小高宽比
    int minSize = 30;            // 灯条最小边长（长或宽）
    for(int i=0; i<contours.size(); i++)
    {
        //过滤小轮廓
        double area = contourArea(contours[i]);
        if(area < 50.0) continue; //面积过小视为噪声

        //轮廓外接矩形
        cv::RotatedRect minRect = cv::minAreaRect(contours[i]);

        //筛选长条状灯条（高宽比、尺寸过滤）
        double width = minRect.size.width;
        double height = minRect.size.height;
        if(width == 0 || height == 0) continue; //避免除零
        double aspectRatio = std::max(width,height) / std::min(width, height); //长/宽比
        if(aspectRatio >= minAspectRatio && std::max(width,height)>minSize)
        {
            lightBars.push_back(minRect);
        }
        
        //绘出来的轮廓是彩色三通道的cv::Scalar(0,0,255)，不能在二值图上画
        //cv::drawContours(result, contours, i, cv::Scalar(255,0,0), 10);
    }
    // for (const auto& contour : contours) {
    //     // 过滤过小轮廓
    //     double area = contourArea(contour);
    //     if (area < 50.0) continue; 

    //     // 计算轮廓的最小外接矩形
    //     RotatedRect minRect = minAreaRect(contour);

    //     // 筛选长条状灯条
    //     float width = minRect.size.width;
    //     float height = minRect.size.height;
    //     if (width == 0 || height == 0) continue;  
    //     float aspectRatio = max(width, height) / min(width, height);  
    //     if (aspectRatio >= ASPECT_RATIO_MIN && max(width, height) > MIN_SIZE) {
    //         lightBars.push_back(minRect);
    //     }
    // }
    
    return lightBars;
}



//匹配灯条
LightBarPair matchLightBarPair(const std::vector<cv::RotatedRect>& lightBars)
{
    //至少需要2个灯条才能匹配
    if(lightBars.size() < 2)
    {
        return LightBarPair(); //默认构造函数，isMatched=false
    }

    //通过相近面积（尺寸）匹配灯条
    double minAreaDiff = 10000; //最小相差面积，尽量往大了设置
    size_t matchIndex1 = 0, matchIndex2 = 0;
    for(size_t i=0; i<lightBars.size(); i++)
    {
        for(size_t j=i+1; j<lightBars.size(); j++)
        {
            // 计算两个灯条的面积差（最小外接矩形面积）
            double area1 = lightBars[i].size.area();
            double area2 = lightBars[i].size.area();
            double areaDiff = abs(area1 - area2);
            if(areaDiff < minAreaDiff)
            {
                minAreaDiff = areaDiff;
                matchIndex1 = i;
                matchIndex2 = j;
            }
        }
    }

    //区分左右灯条并输出（按中心x坐标）
    if(lightBars[matchIndex1].center.x < lightBars[matchIndex2].center.x)
    {
        return LightBarPair(lightBars[matchIndex1], lightBars[matchIndex2]);
    }
    else
    {
        return LightBarPair(lightBars[matchIndex2], lightBars[matchIndex1]);
    }

}



//绘制所有灯条（最小，最小外接矩形）
void drawAllLightBars(cv::Mat img, const std::vector<cv::RotatedRect>& lightBars)
{
    if(img.empty() || lightBars.empty()) return;

    std::vector<cv::Point2f> vertices(4); // 存储最小外接矩形的4个顶点
    for(const auto& bar : lightBars)
    {
        // 获取最小外接矩形的4个顶点
        bar.points(vertices.data());
        // 绘制矩形（蓝色：单个灯条）
        for(int i=0; i<4; i++)
        {
            line(img, vertices[i], vertices[(i+1)%4], cv::Scalar(255,0,0), 5);
        }
    }
}



//绘制匹配灯条（绿色，最大外接矩形）
void drawDetectionResult(cv::Mat& img, const LightBarPair& lightPair)
{
    if(img.empty() || !lightPair.isMatched) return;

     // 1. 收集两个灯条的所有顶点（用于计算最大外接矩形）
    std::vector<cv::Point2f> leftVertices(4), rightVertices(4);
    lightPair.left.points(leftVertices.data()); // 左侧灯条的4个顶点
    lightPair.right.points(rightVertices.data()); // 右侧灯条的4个顶点
    std::vector<cv::Point2f> allVertices = leftVertices;
    allVertices.insert(allVertices.end(), rightVertices.begin(), rightVertices.end()); // 合并8个顶点

    // 2. 计算包围所有顶点的最大外接矩形（轴对齐）
    //pt.x,pt.y都是float，min_必须为float
    float minX = allVertices[0].x, maxX = allVertices[0].x;
    float minY = allVertices[0].y, maxY = allVertices[0].y;
    for(const auto& pt : allVertices)
    {
        minX = std::min(minX, pt.x);
        maxX = std::max(maxX, pt.x);
        minY = std::min(minY, pt.y);
        maxY = std::max(maxY, pt.y);
    }
    cv::Rect maxRect((int)minX, (int)minY, (int)(maxX-minX), (int)(maxY-minY)); // 构造最大矩形

    // 3. 绘制最大外接矩形（绿色，仅保留这部分）
    rectangle(img, maxRect, cv::Scalar(0,255,0), 3);
}


//基于范围的for循环 range-based for loop
//for(range_declaration : range_expression) loop_statement
//range_declaration，变量声明，类型是元素类型或元素类型的引用
//range_expression，对象必须有begin,end迭代器
//使用auto占位符
//for(const auto& i : vector)
//for(auto i : string)