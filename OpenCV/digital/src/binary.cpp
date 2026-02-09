/********************图像二值化************************/

// 　二值化原理
// 　　二值化核心思想，设阈值，大于阈值的为0（黑色）或 255（白色），使图像称为黑白图。
// 　　阈值可固定，也可以自适应阈值。
// 　　自适应阈值一般为一点像素与这点为中序的区域像素平均值或者高斯分布加权和的比较，其中可以设置一个差值也可以不设置。



#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    cv::Mat img = cv::imread("/home/emmm/Desktop/scnu_rm/OpenCV/digital/img/lena.jpeg");
    if(img.empty())
    {
        std::cout << "请确认图像文件路径是否正确" << std::endl;
        return -1;
    }

    //图像灰度化
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    cv::Mat img_B, img_B_V, gray_B, gray_B_V, gray_T, gray_T_V, gray_TRUNC;

    //彩色图像二值化
    //将每个通道单独阈值化后进行组合
    cv::threshold(img, img_B, 125, 255, cv::THRESH_BINARY);
    cv::threshold(img, img_B_V, 125, 255, cv::THRESH_BINARY_INV);
    cv::imshow("img_B", img_B);
    cv::imshow("img_B_V", img_B_V);

    //灰度图像BINARY二值化
    cv::threshold(gray, gray_B, 125, 255, cv::THRESH_BINARY);
    cv::threshold(gray, gray_B_V, 125, 255, cv::THRESH_BINARY_INV);
    cv::imshow("gray_B", gray_B);
    cv::imshow("gray_B_V", gray_B_V);

    //灰度图像TOZERO二值化
    //一个高于保留一个低于保留，这两种叠加可以恢复原来图像
    cv::threshold(gray, gray_T, 125, 255, cv::THRESH_TOZERO);
    cv::threshold(gray, gray_T_V, 125, 255, cv::THRESH_TOZERO_INV);
    cv::imshow("gray_T", gray_T);
    cv::imshow("gray_T_V", gray_T_V);

    //灰度图像TRUNC二值化
    //有梯度
    cv::threshold(gray, gray_TRUNC, 125, 255, cv::THRESH_TRUNC);
    cv::imshow("gray_TRUNC", gray_TRUNC);

    //灰度图像大津法和三角形法二值化（固定阈值化）
    //对图像自动选取阈值
    //大津法选取整个图像中最佳阈值，所有像素对于最佳阈值的均方差最大，不适用于全局梯度有阴影变化的图片
    //三角形法也是选取固定阈值
    //可以将图像划分为多个较小区域，分别使用大津法或三角形法
    cv::Mat img_Thr = cv::imread("/home/emmm/Desktop/scnu_rm/OpenCV/digital/img/binary.png", cv::IMREAD_GRAYSCALE);
    cv::Mat img_Thr_O, img_Thr_T;
    cv::threshold(img_Thr, img_Thr_O, 100, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);  //HRESH_BINARY | THRESH_OTSU：阈值化类型组合
    cv::threshold(img_Thr, img_Thr_T, 125, 255, cv::THRESH_BINARY | cv::THRESH_TRIANGLE);
    cv::imshow("img_Thr", img_Thr);
    cv::imshow("img_Thr_O", img_Thr_O);
    cv::imshow("img_Thr_T", img_Thr_T);

    //自适应阈值二值化
    cv::Mat adaptive_mean, adaptive_gauss;
    cv::adaptiveThreshold(img_Thr, adaptive_mean, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 55, 0);
    cv::adaptiveThreshold(img_Thr, adaptive_gauss, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 55, 0);
    cv::imshow("adaptive_mean", adaptive_mean);
    cv::imshow("adaptive_gauss", adaptive_gauss);

    cv::waitKey(0);

    return 0;
}





//固定阈值化
//全局使用同一个阈值
//cv::threshold() 阈值化处理
//threshold门槛，阈值  thresh-threshold
//对图像中每个像素的灰度值 src(x,y) 与设定的阈值 thresh 进行比较，根据比较结果将像素值映射为新值（通常是 0 或 maxval）
// double cv::threshold(
//     cv::InputArray src,      // 输入图像（必须是单通道灰度图，如CV_8UC1）
//     cv::OutputArray dst,     // 输出图像（与输入尺寸、类型相同）
//     double thresh,           // 阈值（用于比较的基准值）
//     double maxval,           // 最大值（用于指定阈值化后的输出值）
//     int type                 // 阈值化类型（决定比较后的映射规则）
// );
// 阈值类型（type）
// THRESH_BINARY	0	dst(x,y) = (src(x,y) > thresh) ? maxval : 0
// THRESH_BINARY_INV	1	dst(x,y) = (src(x,y) > thresh) ? 0 : maxval
// THRESH_TRUNC	2	dst(x,y) = (src(x,y) > thresh) ? thresh : src(x,y)
// THRESH_TOZERO	3	dst(x,y) = (src(x,y) > thresh) ? src(x,y) : 0
// THRESH_TOZERO_INV	4	dst(x,y) = (src(x,y) > thresh) ? 0 : src(x,y)
// THRESH_OTSU	8	使用大津算法（OTSU）自动确定阈值
// THRESH_TRIANGLE	16	使用三角算法（TRIANGLE）自动确定阈值
//使用THRESH_OTSU或THRESH_TRIANGLE时，不需要double thresh
//double maxval,不是必须的，取决于type

//自适应阈值化 - 只支持灰度图像
//对每个像素，根据其周围邻域的像素值分布计算一个 “局部阈值”，而不是用一个固定的全局阈值。这样可以在图像明暗变化较大时，依然保持较好的分割效果
//cv::adaptiveThreshold()
// void cv::adaptiveThreshold(
//     cv::InputArray src,          // 输入图像（必须是单通道灰度图，如CV_8UC1）
//     cv::OutputArray dst,         // 输出图像（与输入尺寸、类型相同，二值图）
//     double maxValue,             // 最大值（满足阈值条件时赋予的像素值，如255）
//     int adaptiveMethod,          // 自适应阈值计算方法（局部阈值的计算方式）
//     int thresholdType,           // 阈值化类型（只能是二值化或反二值化）
//     int blockSize,               // 计算局部阈值的邻域大小（必须是奇数，如3、5、7...）
//     double C                     // 从局部均值/加权均值中减去的常数（调整阈值的偏移量）
// );
//
// adaptiveMethod自适应阈值算法类型：
// cv::ADAPTIVE_THRESH_MEAN_C：邻域均值，局部阈值=邻域内所有像素的平均值-C
// cv::ADAPTIVE_THRESH_GAUSSIAN_C：邻域高斯加权求和，局部阈值=邻域内像素的高斯加权平均值(中心像素权重更高)-C
//
// thresholdType 阈值化类型，仅支持两种二值化模式
// cv::THRESH_BINARY : dst(x,y) = (src(x,y) > thresh) ? maxval : 0
// cv::THRESH_BINARY_INV : dst(x,y) = (src(x,y) > thresh) ? 0 : maxval
//
// blockSize 计算阈值时所用邻域大小（像素），必须是大于1的奇数（如3, 5, 7...）
//邻域越小：对局部变化越敏感，但可能保留过多噪声；
//邻域越大：抗噪声能力越强，但可能模糊细节
//
// C	从计算出的平均值或加权平均值中减去的常数，用于微调阈值
// C > 0：阈值降低（更多像素会被判定为 “超过阈值”，即更易被保留为 maxValue）；
// C < 0：阈值升高（更少像素被保留）；
// 通常取 C = 1~5 即可，需根据图像调整。
