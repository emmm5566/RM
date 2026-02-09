#include <opencv2/opencv.hpp>

void Contour_external_maxmatrix(cv::Mat img);
void Contour_external_minmatrix(cv::Mat img);
void Contour_external_matrix(cv::Mat img);
void drawapp(cv::Mat result, cv::Mat img);



int main()
{
    cv::Mat img, img1, img2, img3; 
    img = cv::imread("/home/emmm/Desktop/scnu_rm/OpenCV/digital/img/shapes.png");
    resize(img, img, cv::Size(), 0.5, 0.5);

    img1 = img.clone();
    img2 = img.clone();
    img3 = img.clone();

    Contour_external_maxmatrix(img1);
    Contour_external_minmatrix(img2);
    Contour_external_matrix(img3);

    return 0;
}



//轮廓最大外接矩形 -- 矩形的边与图像坐标轴平行
//boundingRect(contours[n])
//Rect（轴对齐，无旋转角度）
//绘制 直接调用rectangle(image, rect, ...) 
//整数坐标（Point）
//无中心/角度，需手动计算（rect.x+rect.width/2 等）
void Contour_external_maxmatrix(cv::Mat img)
{
    cv::Mat gray, blus, binary;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY); //灰度化
    cv::GaussianBlur(gray, blus, cv::Size(9,9), 2, 2); //滤波
    cv::threshold(blus, binary, 170, 255, cv::THRESH_BINARY | cv::THRESH_OTSU); //自适应二值化

    //轮廓检测
    std::vector< std::vector<cv::Point> > contours; //轮廓
    std::vector<cv::Vec4i> hierarchy; //存放轮廓结构变量
    cv::findContours(binary, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point());

    //寻找轮廓的外接矩阵
    // 遍历所有检测到的轮廓（contours是存储轮廓的向量，contours.size()是轮廓的数量）
    for(int n = 0; n < contours.size(); n++)
    {
        // 1. 计算当前轮廓的“最大外接矩形”
        // boundingRect(contours[n])：根据第n个轮廓，计算其轴对齐的外接矩形（矩形边与图像坐标轴平行）
        // 返回值Rect是OpenCV的矩形类，包含矩形的左上角坐标(x,y)、宽度(width)、高度(height)
        cv::Rect rect = boundingRect(contours[n]);

        // 2. 在原始图像上绘制这个外接矩形
        rectangle(img, rect, cv::Scalar(255,0,0), 2, 8, 0); //用二值图检测轮廓，在原图上画外接矩形
    }

    cv::imshow("Contour_external_maxmatrix", img);
    cv::waitKey(2000);
}



//轮廓最小外接矩形
//minAreaRect(contours[n])
//RotatedRect（可旋转，含角度信息）
//绘制 需提取4个顶点，用line()循环连接 
//浮点坐标（Point2f，亚像素精度）
//自带中心（center）、旋转角度（angle）
void Contour_external_minmatrix(cv::Mat img)
{
    cv::Mat gray, blus, binary;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY); 
    cv::GaussianBlur(gray, blus, cv::Size(9,9), 2, 2); 
    cv::threshold(blus, binary, 170, 255, cv::THRESH_BINARY | cv::THRESH_OTSU); 

    std::vector< std::vector<cv::Point> > contours; 
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(binary, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point());

    //寻找轮廓的外接矩阵
    for(int n = 0; n < contours.size(); n++)
    {
        //最小外接矩阵
        cv::RotatedRect rrect = minAreaRect(contours[n]); //计算当前轮廓的“最小面积外接矩形”，返回值RotatedRect
        cv::Point2f vertices[4];
        rrect.points(vertices); //读取最小外接矩形的四个顶点
        cv::Point2f cpt = rrect.center; //获取旋转矩形的中心坐标（Point2f类型）

        //绘制旋转矩形的4条边
        // for(int i=0; i<4; i++)
        // {
        //     //当i=3时（第4个顶点），连接到第0个顶点，形成闭合矩形
        //     if(i == 3) 
        //     {
        //         line(img, vertices[i], vertices[0], cv::Scalar(0,255,0), 4, 8, 0);
        //         break;
        //     }
        //     // 其他情况：连接当前顶点i和下一个顶点i+1
        //     line(img, vertices[i], vertices[i+1], cv::Scalar(0,255,0), 4, 8, 0);
        // }
        for(int i=0; i<4; i++)
        {
            cv::Point2f point1 = vertices[i];
            cv::Point2f point2 = vertices[(i+1) % 4]; //最后一个连回第一个
            line(img, point1, point2, cv::Scalar(0,255,0), 4, 8, 0);
        }

        //绘制旋转矩形的中心（实心圆标记）
        circle(img, cpt, 4, cv::Scalar(0,255,0), 2, 8, 0);


    }

    cv::imshow("Contour_external_minmatrix", img);
    cv::waitKey(2000);
}



//轮廓多边形拟合
void Contour_external_matrix(cv::Mat img)
{
    //预处理
    cv::Mat gray, blus, binary;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY); 
    cv::GaussianBlur(gray, blus, cv::Size(9,9), 2, 2); 
    cv::threshold(blus, binary, 170, 255, cv::THRESH_BINARY | cv::THRESH_OTSU); 

    //轮廓检测
    std::vector< std::vector<cv::Point> > contours; 
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(binary, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point());
    
    //绘制多边形
    for(int n=0; n<contours.size(); n++)
    {
        //计算轮廓中心（用最小外接矩形）
        cv::RotatedRect rrect = minAreaRect(contours[n]);
        cv::Point2f center = rrect.center; //最小外接矩形的中心
        circle(img, center, 2, cv::Scalar(0,0,255), 2, 8, 0); 

        //多边形拟合
        cv::Mat result;
        cv::approxPolyDP(contours[n], result, 4, true); 
        // // 在 OpenCV 中，点集可以用两种形式存储：
        // // std::vector<cv::Point>（更常用，直观）；
        // // cv::Mat（矩阵形式，每行存储一个点的坐标）。
        // std::vector<cv::Point> approx;  // 用vector<Point>接收拟合结果
        // double perimeter = cv::arcLength(contours[n], true);  // 计算轮廓周长
        // double epsilon = 0.02 * perimeter;  // 动态设置拟合精度（周长的2%）
        // cv::approxPolyDP(contours[n], approx, epsilon, true);  // 多边形拟合

        drawapp(result, img); //绘制拟合后的多边形
    }

    cv::imshow("Contour_external_matrix", img);
    cv::waitKey(2000);
}

//绘制拟合后的多边形
// void drawapp(const std::vector<cv::Point>& approx, cv::Mat img)
// {
//     int vertexCount = approx.size();  // 多边形顶点数量
//     for(int i = 0; i < vertexCount; i++)
//     {
//         // 连接当前顶点与下一个顶点（最后一个顶点连回第一个，形成闭合多边形）
//         cv::Point p1 = approx[i];
//         cv::Point p2 = approx[(i + 1) % vertexCount];  // 用取模简化逻辑
//         cv::line(img, p1, p2, cv::Scalar(0,0,255), 4, 8, 0);
//     }
// }
void drawapp(cv::Mat result, cv::Mat img)
{
    // for(int i = 0; i< result.rows; i++)
    // {
    //     //最后一个坐标点与第一个坐标点连接
    //     if(i == result.rows - 1)
    //     {
    //         cv::Vec2i point1 = result.at<cv::Vec2i>(i);
    //         cv::Vec2i point2 = result.at<cv::Vec2i>(0);
    //         line(img, point1, point2, cv::Scalar(0,0,255), 2, 8, 0);
    //         break; 
    //     }

    //     cv::Vec2i point1 = result.at<cv::Vec2i>(i);
    //     cv::Vec2i point2 = result.at<cv::Vec2i>(i+1);
    //     line(img, point1, point2, cv::Scalar(0,0,255), 2, 8, 0);
    // }

    //result 是cv::approxPolyDP函数的输出，用于存储多边形拟合后的顶点坐标，本质是一个点集（多边形的所有顶点）
    // 这里的 result 被定义为 cv::Mat，所以它的结构是：
    // 行数 = 多边形的顶点数量（有多少个顶点，就有多少行）；
    // 列数 = 1（每个顶点单独占一行）；
    // 每个元素的类型 = cv::Point（本质是 cv::Vec2i，即包含两个整数的向量，分别表示 x、y 坐标）
    int n = result.rows;
    for(int i = 0; i < n; i++)
    {
        cv::Vec2i point1 = result.at<cv::Vec2i>(i);
        cv::Vec2i point2 = result.at<cv::Vec2i>((i+1)%n); //最后一个连回第一个
        line(img, point1, point2, cv::Scalar(0,0,255), 4, 8, 0);
    }
}





// // 最大外接矩形（boundingRect）：通过 x/y/width/height 手动推导 4 个顶点；
// std::vector<cv::Point> contour; // 输入：轮廓（或点集）
// cv::Rect rect = cv::boundingRect(contour); // 求最大外接矩形
// std::vector<cv::Point2f> boundRectPoints; // 计算4个顶点坐标
// boundRectPoints.push_back(cv::Point2f(rect.x, rect.y)); // 左上 (x, y)
// boundRectPoints.push_back(cv::Point2f(rect.x + rect.width, rect.y)); // 右上 (x+w, y)
// boundRectPoints.push_back(cv::Point2f(rect.x + rect.width, rect.y + rect.height)); // 右下 (x+w, y+h)
// boundRectPoints.push_back(cv::Point2f(rect.x, rect.y + rect.height)); // 左下 (x, y+h)

// // 最小外接矩形（minAreaRect）：调用 points() 方法自动获取 4 个顶点
// std::vector<cv::Point> contour; // 输入：轮廓（或点集）
// cv::RotatedRect minRect = cv::minAreaRect(contour); // 求最小外接矩形
// cv::Point2f minRectPoints[4]; // 直接获取4个顶点坐标（顺序：默认按矩形周长排列，需注意一致性）
// minRect.points(minRectPoints); // 自动填充4个顶点到数组
// std::vector<cv::Point2f> minAreaRectPoints; // 转换为vector方便后续处理
// minAreaRectPoints.assign(minRectPoints, minRectPoints + 4);



// cv::GaussianBlur（高斯滤波函数）
// void cv::GaussianBlur(
//     cv::InputArray src,        // 输入图像（待滤波图像，支持多通道）
//     cv::OutputArray dst,       // 输出图像（滤波后结果，与输入尺寸、类型相同）
//     cv::Size ksize,            // 高斯核大小（宽×高，必须为正奇数，如Size(9,9)）
//     double sigmaX,             // X方向高斯标准差（控制模糊程度，必填）
//     double sigmaY = 0,         // Y方向高斯标准差（默认0，自动等于sigmaX）
//     int borderType = cv::BORDER_DEFAULT  // 边界填充方式（默认BORDER_DEFAULT）
// );



// cv::Rect（轴对齐矩形类 构造函数）
// cv::Rect::Rect(
//     int x,              // 矩形左上角x坐标（水平方向）
//     int y,              // 矩形左上角y坐标（垂直方向）
//     int width,          // 矩形宽度（水平长度）
//     int height          // 矩形高度（垂直长度）
// );
//表示“轴对齐矩形”的类（矩形的边与图像坐标轴平行）

// cv::boundingRect（计算轴对齐外接矩形函数)
// cv::Rect cv::boundingRect(
//     cv::InputArray points  // 输入点集（通常为单个轮廓contours[n]）
// );
// // 作用：计算包围点集的最小轴对齐矩形（边与坐标轴平行），返回cv::Rect对象

//cv::RotatedRect (旋转矩形类 构造函数)
// cv::RotatedRect::RotatedRect(
//     cv::Point2f center,  // 旋转矩形的中心坐标（浮点型，支持亚像素精度）
//     cv::Size2f size,     // 旋转矩形的原始尺寸（宽×高，未旋转时的大小，Size2f(width, height)）
//     float angle          // 旋转角度（单位：度，顺时针方向为正，范围通常为[-90, 0)）
// );
//表示旋转矩形的类（区别于 cv::Rect 的轴对齐矩形）

// cv::RotatedRect::points（旋转矩形顶点提取成员函数）
// void cv::RotatedRect::points(
//     cv::Point2f pt[]  // 输出参数：存储4个顶点的数组（需提前定义为Point2f[4]）
// ) const;
// // 作用：将旋转矩形的4个顶点坐标存入pt数组，顶点按顺时针/逆时针顺序排列

// cv::RotatedRect::center（旋转矩形中心成员变量）
// cv::Point2f cv::RotatedRect::center;
// // 作用：存储旋转矩形的中心坐标（浮点型，可直接读取，如rrect.center.x获取x坐标）

// cv::minAreaRect（计算最小面积外接旋转矩形函数）
// cv::RotatedRect cv::minAreaRect(
//     cv::InputArray points  // 输入点集（通常为单个轮廓contours[n]）
// );
// // 作用：计算包围点集的面积最小矩形（可旋转，贴合轮廓），返回cv::RotatedRect对象

// cv::approxPolyDP —— "Approximate Polygonal Curve"（多边形曲线逼近）
// void cv::approxPolyDP(
//     const cv::InputArray curve,  // 输入曲线（通常是轮廓的点集，类型为vector<Point>）
//     cv::OutputArray approxCurve, // 输出的逼近多边形（简化后的的点集，类型与输入一致）
//     double epsilon,              // 逼近精度（原始曲线与逼近多边形的最大允许距离，单位：像素）
//     bool closed                  // 曲线是否闭合（true表示逼近多边形是闭合的；false表示不闭合）
// );



// cv::line（绘制直线 全局函数）
// void cv::line(
//     cv::InputArray img,          // 目标图像（绘制直线的画布）
//     cv::Point pt1,               // 直线的起点坐标
//     cv::Point pt2,               // 直线的终点坐标
//     const cv::Scalar& color,     // 直线的颜色（BGR格式）
//     int thickness = 1,           // 直线的线宽（默认值：1）
//     int lineType = cv::LINE_8,   // 线条类型（默认值：8连通线）
//     int shift = 0                // 坐标的小数位数（默认值：0）
// );

// cv::rectangle（绘制轴对齐矩形函数）
// void cv::rectangle(
//     cv::InputArray img,          // 目标图像（绘制矩形的画布）
//     cv::Rect rect,               // 要绘制的矩形（cv::Rect对象，轴对齐）
//     const cv::Scalar& color,     // 矩形颜色（BGR格式）
//     int thickness = 1,           // 线宽（默认1，-1表示填充矩形）
//     int lineType = cv::LINE_8,   // 线条类型（默认LINE_8）
//     int shift = 0                // 坐标小数位数（默认0）
// );

// cv::circle（绘制圆形函数）
// void cv::circle(
//     cv::InputArray img,          // 目标图像（绘制圆形的画布）
//     cv::Point center,            // 圆心坐标（Point/Point2f均可）
//     int radius,                  // 圆的半径（像素数）
//     const cv::Scalar& color,     // 圆的颜色（BGR格式，支持Alpha通道）
//     int thickness = 1,           // 线宽（默认1，-1表示填充圆形）
//     int lineType = cv::LINE_8,   // 线条类型（默认LINE_8）
//     int shift = 0                // 坐标小数位数（默认0）
// );