#include <opencv2/opencv.hpp>

int main()
{
    //空白图像
    cv::Mat img(512, 512, CV_8UC3, cv::Scalar(255, 255, 255)); //scalar标量，设置颜色

    //画圆形
    //circle(img, cv::Point(256, 256), 155, cv::Scalar(0, 69, 255), 10);
    circle(img, cv::Point(256, 256), 155, cv::Scalar(0, 69, 255), cv::FILLED);
    //（在圆形中）画矩形
    //rectangle(img, cv::Point(130, 226), cv::Point(382, 286), cv::Scalar(255, 255, 255), 3);
    rectangle(img, cv::Point(130, 226), cv::Point(382, 286), cv::Scalar(255, 255, 255), cv::FILLED);
    //画线条
    line(img, cv::Point(130, 296), cv::Point(382, 296), cv::Scalar(255, 255, 255), 2);    

    //放置文本
    putText(img, "OpenCV", cv::Point(137, 280), cv::FONT_HERSHEY_DUPLEX, 2, cv::Scalar(0, 69, 255), 5);

    cv::imshow("image", img);

    cv::waitKey(0);

    return 0;
}