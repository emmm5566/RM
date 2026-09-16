#include <opencv2/opencv.hpp>



int main()
{
    cv::VideoCapture cap(0);
    cv::Mat img;

    //加载车牌检测模型
    cv::CascadeClassifier plateCascade;
    plateCascade.load("/usr/share/opencv4/haarcascades/haarcascade_russian_plate_number.xml");
    if(plateCascade.empty())
    {
        std::cout << "file not found" << std::endl;
        return -1;
    }

    std::vector<cv::Rect> plates;

    while(true)
    {
        cap.read(img);

        //检测车牌并绘制标记框
        //scaleFactor（推荐 1.1~1.3）越小，检测越精确但速度慢
        //minNeighbors（推荐 3~6）越大，过滤假阳性越多但可能漏检
        plateCascade.detectMultiScale(img, plates, 1.1, 5); 
        for(int i=0; i<plates.size(); i++)
        {
            //裁剪并保存车牌
            cv::Mat imgCrop = img(plates[i]);
            //cv::imshow(std::to_string(i), imgCrop);
            cv::imwrite("/home/emmm/Desktop/scnu_rm/OpenCV/course/img/plates" + std::to_string(i) + ".png", imgCrop); //保存到文件夹

            rectangle(img, plates[i].tl(), plates[i].br(), cv::Scalar(255, 0, 255), 3);
        }

        cv::imshow("camera", img);
        cv::waitKey(1);
    }

    return 0;
}