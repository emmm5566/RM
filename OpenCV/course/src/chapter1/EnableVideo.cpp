#include <opencv2/opencv.hpp>

int main()
{
    std::string path = "/home/emmm/Desktop/scnu_rm/OpenCV/course/img/test.mp4";
    cv::VideoCapture cap(path);
    cv::Mat img;

    while(true)
    {
        cap.read(img);
        cv::imshow("video", img);
        cv::waitKey(20);
    }

    return 0;
}