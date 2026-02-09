/********************访问照片************************/

#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    //读取照片
    cv::Mat image = cv::imread("/home/emmm/Desktop/scnu_rm/OpenCV/digital/img/test.jpg");

    //确认图片读取成功
    if(image.empty())
    {
        std::cerr << "Failed to open image file." << std::endl;
        return -1;
    }

    //控制照片比例
    resize(image, image, cv::Size(500, 500));

    //显示图片
    cv::imshow("Image with Box", image);

    //等待按键
    cv::waitKey(0);

    return 0;
}





//Mat类（矩阵类）
//用于存储图像和矩阵数据的基础类，Matrix（矩阵）

//cv::imread() 读取图像
//Mat imread(const String& filename, int flags);
//filename 图像文件路径（字符串）
//flags 读取模式（可选参数，默认IMREAD_COLOR）
// IMREAD_UNCHANGED：读取原图像，包括alpha通道
// IMREAD_GRAYSCALE：以灰度图像读取
// IMREAD_COLOR：以彩色图像读取
// IMREAD_ANYDEPTH：以原图像深度读取
// IMREAD_ANYCOLOR：以原图像颜色格式读取
// IMREAD_LOAD_GDAL：使用GDAL读取图像
// IMREAD_REDUCED_GRAYSCALE_2：以1/2的灰度图像读取
// IMREAD_REDUCED_COLOR_2：以1/2的彩色图像读取
// IMREAD_REDUCED_GRAYSCALE_4：以1/4的灰度图像读取

//cv::inshow() 图像显示
//void inshow(const String& winname, InputArray mat);
//winname 窗口名称（字符串）
//mat 要显示的图像数据（Mat对象）

//cv::waitKey() 等待键盘输入
//int waitKey(int delay = 0);
//delay <= 0 无限等待
//delay > 0 等待...ms

//cv::destroyAllWindows() 销毁所有窗口
//void destroyAllWindows();

//std::cerr 标准错误流
//输出错误信息

//resize 
//void resize(InputArray src, OutputArray dst, Size dsize,
//            double fx = 0, double fy = 0,
//            int interpolation = INTER_LINEAR);
//src 输入图像
//dst 输出图像
//dsize 目标尺寸 Size(width, height)
//fx 水平放缩比例
//fy 垂直放缩比例
//interpolation 插值方法

//empty() 检查Mat对象是否包含数据
//bool empty() const;
//返回true没有数据，false包含有效数据