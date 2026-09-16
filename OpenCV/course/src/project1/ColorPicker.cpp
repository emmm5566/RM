#include <opencv2/opencv.hpp>

int main()
{
    cv::VideoCapture cap(0);
    cv::Mat img;

    cv::Mat imgHSV, mask, imgColor;
    int HueMin = 0, SaturationMin = 0, ValueMin = 0;
    int HueMax = 179, SaturationMax = 255, ValueMax = 255;

    cv::namedWindow("Trackbars", (640, 200)); 
    cv::createTrackbar("Hue Min", "Trackbars", &HueMin, 179);
    cv::createTrackbar("Hue Max", "Trackbars", &HueMax, 179);
    cv::createTrackbar("Saturation Min", "Trackbars", &SaturationMin, 255);
    cv::createTrackbar("Saturation Max", "Trackbars", &SaturationMax, 255);
    cv::createTrackbar("Value Min", "Trackbars", &ValueMin, 255);
    cv::createTrackbar("Value Max", "Trackbars", &ValueMax, 255);

    while(true)
    {
        cap.read(img);

        //将图像转换成hsv
        cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);

        //HSV 的三个核心要素是：Hue（色相）、Saturation（饱和度）、Value（明度）
        cv::Scalar lower(HueMin, SaturationMin, ValueMin); 
        cv::Scalar upper(HueMax, SaturationMax, ValueMax); 
        cv::inRange(imgHSV, lower, upper, mask); 
        cv::bitwise_and(img, img, imgColor, mask = mask);//位与运算函数，根据掩码mask从原图中提取符合条件的颜色区域

        std::cout << HueMin << "," << HueMax
            << "," << SaturationMin << "," << SaturationMax
            << "," << ValueMin << "," << ValueMax << std::endl;
        //HueMin,HueMax,SaturationMin,SaturationMax,ValueMin,ValueMax

        cv::imshow("Image", img);
        cv::imshow("Image HSV", imgHSV);
        cv::imshow("Image Mask", mask);//mask是黑白二值图（白色=符合阈值，黑色=不符合），还没调整滑块时全白
        cv::imshow("Image Color", imgColor); //彩色图（保留符合阈值区域的原始颜色，其他区域黑色）


        cv::waitKey(1);
    }

    return 0;
}





// cv::inRange 颜色/数值范围筛选
// 根据设定的下界（lowerb） 和上界（upperb），筛选图像中所有像素值在 [lowerb, upperb] 范围内的区域
// void inRange(
//     InputArray src,       // 输入图像（多通道或单通道，如BGR、HSV、灰度图）
//     InputArray lowerb,    // 下界（与src同通道数，每个通道的最小值）
//     InputArray upperb,    // 上界（与src同通道数，每个通道的最大值）
//     OutputArray dst       // 输出二值图像（单通道，符合条件的像素为255，否则0）
// );

// cv::bitwise_and 图像按位与运算
// 按位与：两个像素值都为非零时（如 255），结果为非零；只要有一个为零，结果为零
// “用掩码（Mask）提取原图中的特定区域”—— 掩码中白色区域（255）对应的原图部分会被保留，黑色区域（0）对应的部分会被过滤掉
// void bitwise_and(
//     InputArray src1,       // 输入图像1（单通道或多通道，如BGR图、二值图）
//     InputArray src2,       // 输入图像2（需与src1大小、通道数相同）
//     OutputArray dst,       // 输出图像（与输入大小、通道数相同，存储运算结果）
//     InputArray mask = noArray()  // 可选掩码：仅对掩码中非零像素的位置进行运算
// );

// cv::createTrackbar 创建滑动条（Trackbar） ，动态调整参数
// int createTrackbar(
//     const String& trackbarname,  // 滑动条的名称（显示在滑动条旁）
//     const String& winname,       // 滑动条所属的窗口名称（必须先创建该窗口）
//     int* value,                  // 与滑动条绑定的变量指针（滑动条位置对应的值）
//     int count,                   // 滑动条的最大值（最小值固定为0）
//     TrackbarCallback onChange = 0, // 回调函数（滑动条变动时触发，可选）
//     void* userdata = 0           // 传给回调函数的用户数据（可选）
// );