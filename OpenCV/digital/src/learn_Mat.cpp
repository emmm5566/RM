#include<opencv2/opencv.hpp>

//cv::Mat 是 OpenCV 中最核心的类，用于存储图像和矩阵数据。它是一个智能指针，自动管理内存

int main()
{   
    //创建空矩阵
    cv::Mat mat; // 创建空矩阵，不分配内存

    //指定尺寸和类型创建
    // 创建 3行4列的单通道浮点矩阵
    cv::Mat mat1(3, 4, CV_32FC1);
    // 创建 480x640 的3通道8位矩阵（彩色图像）
    cv::Mat mat2(480, 640, CV_8UC3);
    // 使用 Size 对象创建
    cv::Mat mat3(cv::Size(640, 480), CV_8UC1);

    //初始化值创建
    // 创建并初始化为全0
    cv::Mat zeros = cv::Mat::zeros(3, 3, CV_8UC1);
    // 创建并初始化为全1
    cv::Mat ones = cv::Mat::ones(3, 3, CV_32FC1);
    // 创建并初始化为特定值
    cv::Mat eye = cv::Mat::eye(3, 3, CV_32FC1); // 单位矩阵
    cv::Mat matrix = (cv::Mat_<float>(2, 2) << 1.0, 2.0, 3.0, 4.0);

    //数据类型
    // CV_8UC1	8位无符号单通道	灰度图像
    // CV_8UC3	8位无符号3通道	BGR彩色图像
    // CV_32FC1	32位浮点单通道	深度数据、矩阵运算
    // CV_64FC1	64位浮点单通道	高精度计算

    return 0;
}
