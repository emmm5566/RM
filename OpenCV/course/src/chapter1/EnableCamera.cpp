#include <opencv2/opencv.hpp>

int main()
{
    cv::VideoCapture cap(0);
    cv::Mat img;
    
    while(true)
    {
        cap.read(img);
        cv::imshow("camera", img);
        cv::waitKey(1); //摄像头不能用0否则卡顿，图片用0保持静止
    }

    return 0;
}