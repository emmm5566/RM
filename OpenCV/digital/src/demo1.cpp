/********************访问视频************************/

#include <opencv2/opencv.hpp>

int main()
{
    //打开视频文件
    cv::VideoCapture cap("/home/emmm/Desktop/scnu_rm/OpenCV/digital/img/test.mp4");

    //检查视频是否打开成功
    if(!cap.isOpened())
    {
        std::cout << "Error opening video stream or file" << std::endl;
        return -1;
    }

    //循环读取视频帧
    while(true)
    {
        cv::Mat frame;

        //读取当前帧
        cap >> frame;

        //检查是否成功读取帧
        if(frame.empty())
        {
            break;
        }

        resize(frame, frame, cv::Size(800, 800));
        cv::imshow("Frame", frame);

        //按下 Esc 键退出循环
        if(cv::waitKey(25) == 27)
        {
            break;
        }
    }

    //释放VideoCapture对象和所有窗口
    cap.release();
    cv::destroyAllWindows();

    return 0;
}





//cv::VideoCapture类
//从视频、摄像头或图像序列捕获视频的类
/*
cv::VideoCapture cap(0); 打开默认摄像头
cap.open("video.mp4"); 打开视频文件
cap.open("http://192.168.1.100:8080/video"); 打开网络摄像头
cap.open(1); 打开USB摄像头（摄像头1）
*/

//isOpened() 检查是否成功打开
//bool isOpened() const;
//返回true成功打开，false打开失败

//release() 释放资源
//void release();
//释放VideoCapture占用的所有资源，关闭视频流或摄像头连接