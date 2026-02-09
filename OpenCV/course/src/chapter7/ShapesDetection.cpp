#include <opencv2/opencv.hpp>

//获取轮廓
void getContours(cv::Mat imgDil, cv::Mat img)
{
    // 存储轮廓的容器：每个轮廓是一个点集（vector<cv::Point>）
    std::vector< std::vector<cv::Point> > contours;
    // 存储轮廓层级关系的容器（父子轮廓的索引信息），向量中的每个元素是cv::Vec4i(4个int向量)-[next, previous, child, parent]
    std::vector<cv::Vec4i> hierarchy;
    // 检测轮廓
    cv::findContours(imgDil, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    // 在原图上绘制轮廓（-1——绘制所有轮廓,0——绘制第1个轮廓）
    //cv::drawContours(img, contours, -1, cv::Scalar(255,0,255), 2);

    // 定义一个容器，用于存储每个轮廓的多边形逼近结果 - Polygon多边形
    std::vector< std::vector<cv::Point> > conPoly(contours.size()); //一定要在循环外
    // 存储每个多边形的最小边界矩形（Rect类型，包含左上角和宽高）
    std::vector<cv::Rect> boundRect(contours.size()); //一定要在循环外
    std::string objectType;

    //用面积过滤微小干扰
    for(int i=0; i<contours.size(); i++)
    {
        int area = contourArea(contours[i]);
        std::cout << area << std::endl;
        if(area > 1000)
        {
            //cv::drawContours(img, contours, i, cv::Scalar(255,0,255), 2);

            //多边形拟合
            // 计算轮廓的周长（true表示轮廓闭合）
            float peri = cv::arcLength(contours[i], true);
            // 多边形逼近（简化轮廓）
            // 参数：输入轮廓、输出多边形顶点、逼近精度（0.02*周长，值越小越接近原轮廓）、是否闭合
            cv::approxPolyDP(contours[i], conPoly[i], 0.02*peri, true);
            // 绘制简化后的多边形（紫色线条）
            cv::drawContours(img, conPoly, i, cv::Scalar(255,0,255), 2);
            std::cout << conPoly[i].size() << std::endl;

            //绘制外接矩形
            // 计算多边形的最小边界矩形（能完全包围多边形的最小矩形）
            boundRect[i] = cv::boundingRect(conPoly[i]);
            // 绘制边界矩形（绿色线条，线宽5）
            // tl()——左上角"top-left"，br()右下角——"bottom-right"
            rectangle(img, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0, 255, 0), 2);

            //根据顶点数判断形状
            int objCor = (int)conPoly[i].size(); //获取多边形顶点数
            if(objCor == 3) { objectType = "Triangle"; }
            else if(objCor == 4) 
            { 
                float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height; //宽高比
                std::cout << aspRatio << std::endl;
                if(aspRatio>0.95 && aspRatio<1.05) { objectType = "Square"; }
                else { objectType = "Rectangle"; } 
            }
            else if(objCor > 4) { objectType = "Circle"; }
            putText(img, objectType, {boundRect[i].x, boundRect[i].y-5}, cv::FONT_HERSHEY_PLAIN, 0.75, cv::Scalar(0, 69, 255), 1);
        }
    }
}

int main()
{
    std::string path = "/home/emmm/Desktop/scnu_rm/OpenCV/course/img/shape.png";
    cv::Mat imgOriginal = cv::imread(path);
    resize(imgOriginal, imgOriginal, cv::Size(), 0.25, 0.25);


    //去水印
    // 创建掩码（单通道，水印区域设为白色255，其他区域黑色0）
    cv::Mat mask = cv::Mat::zeros(imgOriginal.size(), CV_8UC1); // 初始化全黑掩码
    rectangle(imgOriginal, cv::Point(428, 484), cv::Point(498, 498), cv::Scalar(255, 255, 255), -1); // 标记水印区域为白色
    cv::Mat img;
    // 图像修复（利用周围像素填充水印区域）
    // 参数：原图、掩码、输出图、修复半径（3~5较合适）、修复算法（TELEA更常用）
    cv::inpaint(imgOriginal, mask, img, 3, cv::INPAINT_TELEA);


    //Preprocessing预处理 —— 图像边缘检测与增强
    cv::Mat imgGray, imgBlur, imgCanny, imgDil;
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(imgGray, imgBlur, cv::Size(3, 3), 3, 0);
    cv::Canny(imgBlur, imgCanny, 25, 75);
    cv:: Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::dilate(imgCanny, imgDil, kernel);

    getContours(imgDil, img);

    cv::imshow("Image Original", imgOriginal);
    cv::imshow("Image", img);
    cv::imshow("Image Dilation", imgDil);

    cv::waitKey(0);

    return 0;
}





// cv::contourArea —— 计算轮廓面积
// double contourArea(
//     InputArray contour,  // 输入轮廓（std::vector<cv::Point> 类型）
//     bool oriented = false  // 是否返回有方向的面积（默认false，返回绝对值）
// );

// cv::arcLength —— 计算轮廓周长（弧长）
// double arcLength(
//     InputArray curve,  // 输入曲线/轮廓（std::vector<cv::Point> 类型）
//     bool closed        // 曲线是否闭合（轮廓通常为true）
// );

// cv::approxPolyDP —— 轮廓多边形逼近
// void approxPolyDP(
//     InputArray curve,        // 输入轮廓（原始曲线）
//     OutputArray approxCurve, // 输出的近似多边形（顶点更少）
//     double epsilon,          // 逼近精度（原始轮廓与近似多边形的最大距离，单位：像素）
//     bool closed              // 是否闭合（通常为true）
// );
// epsilon：核心参数，决定近似精度。值越小，近似越接近原始轮廓（顶点多）；值越大，轮廓越简化（顶点少）。
// 实际中常用 epsilon = 0.02 * arcLength(curve, true)（周长的 2%），平衡精度和简化程度

// cv::drawContours —— 绘制轮廓
// void drawContours(
//     InputOutputArray image,  // 目标图像（绘制到该图像上）
//     InputArrayOfArrays contours,  // 轮廓集合（std::vector<std::vector<cv::Point>>）
//     int contourIdx,          // 要绘制的轮廓索引（-1表示绘制所有轮廓）
//     const Scalar& color,     // 轮廓颜色（如cv::Scalar(0,255,0)表示绿色）
//     int thickness = 1,       // 轮廓线宽（-1表示填充轮廓内部）
//     int lineType = cv::LINE_8,  // 线类型（默认即可）
//     InputArray hierarchy = noArray(),  // 轮廓层级（通常无需传入）
//     int maxLevel = INT_MAX,   // 绘制的最大层级（默认绘制所有层级）
//     Point offset = Point()    // 轮廓偏移量（默认无偏移）
// );