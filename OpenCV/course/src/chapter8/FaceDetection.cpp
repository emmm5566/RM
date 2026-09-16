//#include <opencv2/objdetect.hpp>
#include <opencv2/opencv.hpp>

//Viola-Jones 级联方法（Viola-Jones Cascade Method）

int main()
{
    std::string path = "/home/emmm/Desktop/scnu_rm/OpenCV/course/img/test.png";
    cv::Mat img = cv::imread(path);
    resize(img, img, cv::Size(), 0.5, 0.5);

    //加载人脸检测模型
    cv::CascadeClassifier faceCascade;
    faceCascade.load("/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml");
    if(faceCascade.empty())
    {
        std::cout << "file not found" << std::endl;
        return -1;
    }

    //人脸检测并绘制标记框
    // 定义容器存储检测到的人脸区域
    std::vector<cv::Rect> faces;
    // 调用级联分类器检测人脸
    faceCascade.detectMultiScale(img, faces, 1.1, 10);
    // 遍历所有检测到的人脸，绘制紫色矩形框标记
    for(int i=0; i<faces.size(); i++)
    {
        rectangle(img, faces[i].tl(), faces[i].br(), cv::Scalar(255, 0, 255), 3);
    }

    cv::imshow("image", img);
    cv::waitKey(0);

    return 0;
}