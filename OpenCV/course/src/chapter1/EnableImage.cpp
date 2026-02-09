//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

int main()
{
    std::string path = "/home/emmm/Desktop/scnu_rm/OpenCV/course/img/person.png";
    cv::Mat img = cv::imread(path);
    cv::imshow("image", img);
    cv::waitKey(0);

    return 0;
}