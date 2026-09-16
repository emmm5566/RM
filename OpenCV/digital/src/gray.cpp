/********************图像灰度化************************/

// 灰度化原理
// 灰度化处理就是将一幅色彩图像转化为灰度图像的过程。彩色图像分为R，G，B三个分量，分别显示出红绿蓝等各种颜色，灰度化就是使彩色的R，G，B分量相等的过程。灰度值大的像素点比较亮（像素值最大为255，为白色），反之比较暗（像素最下为0，为黑色）。
// 	图像灰度化核心思想是 R = G = B ，这个值也叫灰度值。
// 图像灰度化的算法：
// 　　1)最大值法：使转化后的R，G，B得值等于转化前3个值中最大的一个，即：R=G=B=max（R，G，B）。这种方法转换的灰度图亮度很高。
// 　　2)平均值法：是转化后R，G，B的值为转化前R,G,B的平均值。即：R=G=B=(R+G+B)/3。这种方法产生的灰度图像比较柔和。
// # Y = 0.299R + 0.587G + 0.114B
// 　3)加权平均值法：按照一定权值，对R，G，B的值加权平均，即：Y = 0.299R + 0.587G + 0.114B,分别为R，G，B的权值，取不同的值形成不同的灰度图像。由于人眼对绿色最为敏感，红色次之，对蓝色的敏感性最低，因此使将得到较易识别的灰度图像。一般时，得到的灰度图像效果最好。

#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    //直接读取灰度图像
    //图像本身就是灰度图像，直接使用imread()读取图像
    cv::Mat img = cv::imread("/home/emmm/Desktop/scnu_rm/OpenCV/digital/img/lena.bmp");
    std::cout << "图片通道数：" << img.channels() << std::endl;
    std::cout << "图片行数：" << img.rows << " 图片列数：" << img.cols << std::endl;
    std::cout << img << std::endl;  //cout<<img输出的是图像的原始像素数值矩阵
    cv::imshow("img", img);

    //图像读取时使用0或者IMREAD_GRAYSCALE，以灰度方式读取图图像
    //在调用imread时传入参数0或者IMREAD_GRAYSCALE
    cv::Mat img1 = cv::imread("/home/emmm/Desktop/scnu_rm/OpenCV/digital/img/lena.jpeg", 0);
    cv::Mat img2 = cv::imread("/home/emmm/Desktop/scnu_rm/OpenCV/digital/img/lena.jpeg", cv::IMREAD_GRAYSCALE);
    cv::imshow("img1", img1);
    cv::imshow("img2", img2);

    //使用cvtColor()函数转换为灰度图像
    cv::Mat img3 = cv::imread("/home/emmm/Desktop/scnu_rm/OpenCV/digital/img/lena.jpeg");
    cvtColor(img3, img3, cv::COLOR_BGR2GRAY);
    cv::imshow("img3", img3);

    //通道取均值
    //将3通道图像的单个像素的3通道均值赋给另一个矩阵，得到灰度图像
    cv::Mat img4 = cv::imread("/home/emmm/Desktop/scnu_rm/OpenCV/digital/img/lena.jpeg");
    cv::Mat grayImg(img4.rows, img4.cols, CV_8UC1, cv::Scalar(0));  
    for(int i=0; i<img4.rows; i++)
    {
        for(int j=0; j<img4.cols; j++)
        {
            grayImg.at<uchar>(i,j) = 
                (img4.at<cv::Vec3b>(i,j)[0] 
                + img4.at<cv::Vec3b>(i,j)[1] 
                + img4.at<cv::Vec3b>(i,j)[2]) / 3;
            
            //at<>()模板方法 访问和修改矩阵中特定位置的元素
            //uchar数据类型 unsigned-char 0-255 表示灰度图像的单通道像素值
            //cv::Vec3b数据类型 OpenCV的3元素向量，每个元素是uchar类型 [B,G,R]-蓝色[0]、绿色[1]、红色[2]通道
            //(i,j)[]索引访问

            //更准确的亮度公式：grayValue = 0.299 * red + 0.587 * green + 0.114 * blue;
            //
            // cv::Vec3b pixel = img4.at<cv::Vec3b>(i,j);
            // grayImg.at<uchar>(i,j) = 0.299 * pixel[2] + 0.587 * pixel[1] + 0.114 * pixel[0];
        }
    }
    cv::imshow("lena", img4);
    cv::imshow("lena-gray", grayImg);

    cv::waitKey(0);

    return 0;
}





//cv::cvtColor() 颜色空间转换 cvt-convert
//能够进行转换的条件是图像是3通道，而不是图像必须是彩色
// void cv::cvtColor(
//     cv::InputArray src,      // 输入图像（可以是多通道，如3通道BGR）
//     cv::OutputArray dst,     // 输出图像（与输入尺寸相同，通道数由转换类型决定）
//     int code                 // 转换代码（指定从哪种颜色空间转到哪种，如COLOR_BGR2GRAY）
// );
// cv::COLOR_BGR2GRAY	BGR 彩色图 → 灰度图（单通道）	3	1
// cv::COLOR_BGR2RGB	BGR → RGB（交换蓝、红通道）	3	3
// cv::COLOR_BGR2HSV	BGR → HSV（色调、饱和度、明度）	3	3
// cv::COLOR_BGR2HLS	BGR → HLS（色调、明度、饱和度）	3	3
// cv::COLOR_RGB2BGR	RGB → BGR（与 COLOR_BGR2RGB 相反）	3	3
// cv::COLOR_GRAY2BGR	灰度图 → 3 通道 BGR（每个通道值相同）	1	3

//cv::Scalar 是一个轻量级的模板类，用于表示像素值（尤其是多通道图像的像素值），可以存储 1~4 个元素（对应图像的 1~4 个通道）
//Scalar(0)表示所有像素的初始值为0（对于8位单通道图像，0对应黑色）