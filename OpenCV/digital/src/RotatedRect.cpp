#include <opencv2/opencv.hpp>

int main()
{
    cv::Mat img(200, 200, CV_8UC3, cv::Scalar(0)); 
    std::vector<cv::Scalar> colors = { cv::Scalar(0,0,255), cv::Scalar(255,0,255), cv::Scalar(255,0,0), cv::Scalar(0,255,0) }; //定义4种颜色用于绘制矩形的4条边

    for(int angle = 0; angle < 360; angle += 30)
    {
        // 创建一个“旋转矩形”对象
        cv::RotatedRect rRect = cv::RotatedRect(cv::Point2f(100,100), cv::Size2f(50,100), angle);
        
        // 存储旋转矩形的4个顶点坐标
        cv::Point2f vertices[4];
        rRect.points(vertices);
        cv::Mat temp = img.clone();

        // 绘制旋转矩形的4条边：
        // 循环连接顶点（vertices[i] → vertices[(i+1)%4]，%4实现“第4个顶点连回第1个”）
        for(int i=0; i<4; i++)
        {
            line(temp, vertices[i], vertices[(i+1)%4], colors[i], 2);
        }

        std::string text = "angle" + std::to_string(angle);
        cv::putText(temp, text, cv::Point(0,30), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(255,255,255), 1, 8);

        cv::imshow("temp", temp);
        cv::waitKey(500);
    }

    return 0;
}





// cv::Scalar（颜色 / 数值容器 构造函数）
// cv::Scalar::Scalar(
//     double v0,       // 第1个通道的值（BGR格式对应蓝色通道）
//     double v1 = 0,   // 第2个通道的值（BGR格式对应绿色通道）
//     double v2 = 0,   // 第3个通道的值（BGR格式对应红色通道）
//     double v3 = 0    // 第4个通道的值（可选，如Alpha透明通道）
// );

// cv::Point（整数坐标点 构造函数）
// cv::Point::Point(
//     int x,           // 点的水平坐标（像素列序号）
//     int y            // 点的垂直坐标（像素行序号）
// );

// cv::Point2f（浮点坐标点 构造函数）
// cv::Point2f::Point2f(
//     float x,         // 点的水平坐标（浮点型，支持亚像素精度）
//     float y          // 点的垂直坐标（浮点型，支持亚像素精度）
// );

// cv::Size2f（浮点尺寸 构造函数）
// cv::Size2f::Size2f(
//     float width,     // 尺寸的宽度（如矩形的横向长度）
//     float height     // 尺寸的高度（如矩形的纵向长度）
// );

// cv::RotatedRect（旋转矩形 构造函数）
// cv::RotatedRect::RotatedRect(
//     cv::Point2f center,  // 旋转矩形的中心坐标
//     cv::Size2f size,     // 旋转矩形未旋转时的原始尺寸（宽、高）
//     float angle          // 旋转矩形的旋转角度（单位：度，顺时针方向为正）
// );

// cv::Mat::clone（图像深拷贝 成员函数）
// cv::Mat cv::Mat::clone(
//     // 无输入参数
// ) const;
// // 作用：创建当前Mat的深拷贝（新图像与原图像内存独立），返回拷贝后的Mat对象

// cv::putText（绘制文字 全局函数）
// void cv::putText(
//     cv::InputArray img,                  // 目标图像（绘制文字的画布）
//     const cv::String& text,              // 要绘制的文字内容
//     cv::Point org,                       // 文字的左下角起点坐标
//     int fontFace,                        // 字体类型（如cv::FONT_HERSHEY_SIMPLEX）
//     double fontScale,                    // 字体的缩放比例
//     cv::Scalar color,                    // 文字的颜色（BGR格式）
//     int thickness = 1,                   // 文字的线宽（默认值：1）
//     int lineType = cv::LINE_8,           // 线条类型（默认值：8连通线）
//     bool bottomLeftOrigin = false        // 文字原点是否为左下角（默认值：false，即左上角）
// );

// cv::imwrite（保存图像 全局函数）
// bool cv::imwrite(
//     const cv::String& filename,          // 保存路径+文件名（含后缀，如".png"）
//     cv::InputArray img,                  // 要保存的图像
//     const std::vector<int>& params = std::vector<int>()  // 保存参数（可选，如JPG质量、PNG压缩级别）
// );
// // 作用：将图像保存到指定路径，返回true表示保存成功