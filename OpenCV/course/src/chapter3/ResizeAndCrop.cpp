#include <opencv2/opencv.hpp>

int main()
{
    std::string path = "/home/emmm/Desktop/scnu_rm/OpenCV/course/img/person.png";
    cv::Mat img = cv::imread(path);
    
    cv::Mat imgResize, imgCrop;
    //调整大小
    std::cout << img.size() << std::endl; //查看图像大小
    resize(img, imgResize, cv::Size(), 0.5, 0.5);

    //裁减图像
    cv::Rect roi(800, 700, 900, 1000); //相对于(0,0,0,0)移动量，定义一个矩形区域roi(x,y,width,height)
    imgCrop = img(roi); //cv::Mat类对operator()运算符的重载，快速提取图像的感兴趣区域（ROI，Region of Interest）
    
    cv::imshow("Image", img);
    cv::imshow("Image Resize", imgResize);
    cv::imshow("Image Crop", imgCrop);

    cv::waitKey(0);

    return 0;
}