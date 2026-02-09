/********************访问摄像头************************/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

int main()
{
    //打开默认摄像头
    cv::VideoCapture cap(0);
    if(!cap.isOpened())
    {
        std::cout << "无法打开摄像头！" << std::endl;
        return -1;
    }

    cv::namedWindow("摄像头", cv::WINDOW_NORMAL);

    while(true)
    {
        cv::Mat frame;
        cap >> frame;

        //显示视频帧
        cv::imshow("摄像头", frame);

        //按下空格键拍照
        if(cv::waitKey(30) == ' ')
        {
            //生成文件名
            /* localtime(&now) 将时间戳转换为本地时间的tm结构体
            tm结构体 包含时间信息
            lim 结构体指针 
            tm_year+1900：tm_year存储的是从1900年开始的年数
            tm_mon+1：tm_mon0-11 */
            time_t now = time(NULL);
            tm *ltm = localtime(&now);
            std::string filename = std::to_string(ltm->tm_year + 1900) + "-"
                + std::to_string(ltm->tm_mon + 1) + "-"
                + std::to_string(ltm->tm_hour) + "-"
                + std::to_string(ltm->tm_min) + "-"
                + std::to_string(ltm->tm_sec) + ".jpg";

            //保存图片
            cv::imwrite(filename, frame);
            std::cout << "已保存照片：" << filename << std::endl;
        }
    }

    return 0;
}





//cv::nameWindow() 创建和管理显示窗口
// void cv::namedWindow(
//     const std::string& winname,  // 窗口名称（唯一标识符，字符串类型）
//     int flags = cv::WINDOW_AUTOSIZE  // 窗口属性（可选参数，默认自动大小）
// );
//flags:
// WINDOW_AUTOSIZE	默认值。窗口大小自动适应图像尺寸，用户不能手动调整窗口大小。
// WINDOW_NORMAL	用户可以自由调整窗口大小。
// WINDOW_OPENGL	窗口创建时会支持 OpenGL。
// WINDOW_FREERATIO	调整窗口大小时，图像会拉伸以填满窗口，不保持原始宽高比。
// WINDOW_KEEPRATIO	调整窗口大小时，会保持图像的原始宽高比。
// WINDOW_GUI_EXPANDED	创建一个带有状态栏和工具栏的增强型图形用户界面窗口。
// WINDOW_FULLSCREEN	将窗口更改为全屏显示。



//time_t 时间数据类型，长整型，从1970.1.1到至今的秒数
//time(NULL) 获取当前时间的时间戳

//std::to_string() 将数值类型转化为字符串类型
//#include<string>
//std::string to_string(type value);