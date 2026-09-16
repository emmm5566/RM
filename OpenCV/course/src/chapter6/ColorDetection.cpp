#include <opencv2/opencv.hpp>

int main()
{
    std::string path = "/home/emmm/Desktop/scnu_rm/OpenCV/course/img/car.png";
    cv::Mat img = cv::imread(path);
    resize(img, img, cv::Size(500, 700));

    cv::Mat imgHSV;
    //将图像转换成hsv，hsv更容易找到颜色
    cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);

    int HueMin = 0, SaturationMin = 110, ValueMin = 153;
    int HueMax = 19, SaturationMax = 240, ValueMax = 255;
    cv::Mat mask; //msk是输出的掩码矩阵，用于存储阈值分割后的二值化结果，类型为单通道灰度图（CV_8U）

    //使用滑块实时调节阈值 ———— 检测颜色(mask图像对应部分变白)
    cv::namedWindow("Trackbars", (640, 200)); //"Trackbars"是窗口唯一标识
    cv::createTrackbar("Hue Min", "Trackbars", &HueMin, 179);
    cv::createTrackbar("Hue Max", "Trackbars", &HueMax, 179);
    cv::createTrackbar("Saturation Min", "Trackbars", &SaturationMin, 255);
    cv::createTrackbar("Saturation Max", "Trackbars", &SaturationMax, 255);
    cv::createTrackbar("Value Min", "Trackbars", &ValueMin, 255);
    cv::createTrackbar("Value Max", "Trackbars", &ValueMax, 255);

    while(true)
    {
        cv::Scalar lower(HueMin, SaturationMin, ValueMin); //定义HSV颜色空间中的阈值
        cv::Scalar upper(HueMax, SaturationMax, ValueMax); 
        cv::inRange(imgHSV, lower, upper, mask); //对HSV图像进行阈值分割，遍历输入的HSV图像的每个像素检查其H、S、V值，满足则生成掩码

        cv::imshow("Image", img);
        cv::imshow("Image HSV", imgHSV);
        cv::imshow("Image Mask", mask);

        cv::waitKey(0);
    }

    return 0;
}