//图像腐蚀
//用3×3的核（任意形状）去扫描二值图像，仅当核的与前景像素有完全重合区域时，将二值图像中对应的卷积核中心位置（任意重置点）的像素保留，其余情况下，将中心位置的像素置0
//图像膨胀
//用3×3的核（任意形状）去扫描二值图像，当核与图像中的前景像素（值为1的像素）有交集时，则将二值图像中对应的卷积核中心位置（任意重置点）的像素值置为1
//膨胀有交集就变1，腐蚀完全重合区域才保留（不重合变0）

//开：腐蚀再膨胀，去除微小干扰块
//闭：膨胀再腐蚀，填充闭合区域

//形态学梯度
// 基本梯度：膨胀图 - 腐蚀图
// 内梯度：原图 - 腐蚀图
// 外梯度：膨胀图 - 原图
//这里opencv只能直接实现基本梯度，在使用API：morphologyEx 时，调用MORPH_GRADIENT方法即可
//内梯度、外梯度没有直接的API，一般通过已有API间接实现

//顶帽：原图 - 开操作后的图
//黑帽：闭操作后的图 - 原图
//注：顶帽和黑帽操作用于获取图像中的微小细节
//击中击不中： 通过特定模板，仅当输入的图像中，有与模板一模一样的块时，被击中的输入图像区域才会被保留
//使用API：morphologyEx时，分别调用MORPH_TOPHAT 、MORPH_BLACKHAT、MORPH_HITMISS方法即可实现

//API —— Application Programming Interface（应用程序编程接口），不同软件组件、程序或系统之间相互通信的 “桥梁” 或 “规则”

#include <opencv2/opencv.hpp>

void erode_dilate(cv::Mat& image);
void open_close(cv::Mat& image);
void shape_gradient(cv::Mat& image);
void other_method(cv::Mat& image);

int main()
{
    cv::Mat image = cv::imread("/home/emmm/Desktop/scnu_rm/OpenCV/digital/img/lena.jpeg");

    erode_dilate(image);
    open_close(image);
    shape_gradient(image);
    other_method(image);

    cv::waitKey(0);

    return 0;
}

//腐蚀膨胀
void erode_dilate(cv::Mat& image)
{
    //图像灰度化
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    //灰度图像二值化
    cv::Mat binary;
    cv::threshold(gray, binary, 0, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);
    cv::namedWindow("THRESH_OTSU", cv::WINDOW_FREERATIO);
    cv::imshow("THRESH_OTSU", binary);

    cv::Mat dst1, dst2;
    //定义核
    int kernel_size = 5;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(kernel_size, kernel_size), cv::Point(-1, -1));
    
    //腐蚀
    cv::erode(binary, dst1, kernel);
    cv::namedWindow("erode", cv::WINDOW_FREERATIO);
    cv::imshow("erode", dst1);

    //膨胀
    cv::dilate(binary, dst2, kernel);
    cv::namedWindow("dilate", cv::WINDOW_FREERATIO);
    cv::imshow("dilate", dst2);
}

//开闭
void open_close(cv::Mat& image)
{
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    cv::Mat binary;
    cv::threshold(gray, binary, 0, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);
    cv::namedWindow("THRESH_OTSU", cv::WINDOW_FREERATIO);
    cv::imshow("THRESH_OTSU", binary);

    cv::Mat dst1, dst2;
    //定义核
    int kernel_size = 5;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(kernel_size, kernel_size), cv::Point(-1, -1));

    //开
    cv::morphologyEx(binary, dst1, cv::MORPH_OPEN, kernel, cv::Point(-1, -1), 1, 0);
    cv::namedWindow("MORPH_OPEN", cv::WINDOW_FREERATIO);
    cv::imshow("MORPH_OPEN", dst1);

    //闭
    cv::morphologyEx(binary, dst2, cv::MORPH_CLOSE, kernel, cv::Point(-1, -1), 1, 0);
    cv::namedWindow("MORPH_CLOSE", cv::WINDOW_FREERATIO);
    cv::imshow("MORPH_CLOSE", dst2);
}

//形态学梯度
//在边缘提取应用中，梯度边缘后，会再进行二值化，从而获取更好的边缘图像
void shape_gradient(cv::Mat& image)
{
    //图像灰度化
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    cv::Mat g1, g2, g3;
    cv::Mat dst1, dst2;
    //定义核
    int kernel_size = 7;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(kernel_size, kernel_size), cv::Point(-1, -1));

    //基本梯度
    cv::morphologyEx(gray, g1, cv::MORPH_GRADIENT, kernel, cv::Point(-1, -1), 1, 0);

    //膨胀
    cv::morphologyEx(gray, dst1, cv::MORPH_GRADIENT, kernel, cv::Point(-1, -1), 1, 0);

    //腐蚀
    cv::morphologyEx(gray, dst2, cv::MORPH_GRADIENT, kernel, cv::Point(-1, -1), 1, 0);

    //外梯度
    cv::subtract(dst1, gray, g2);
    //内梯度
    cv::subtract(gray, dst2, g3);

    cv::namedWindow("MORPH_GRADIENT/base_gradient", cv::WINDOW_FREERATIO);
    cv::imshow("MORPH_GRADIENT/base_gradient", g1);
    cv::namedWindow("outter_gradient", cv::WINDOW_FREERATIO);
    cv::imshow("outter_gradient", g2);
    cv::namedWindow("inner_gradient", cv::WINDOW_FREERATIO);
    cv::imshow("inner_gradient", g3);

    cv::Mat binary;
    cv::threshold(g1, binary, 0, 25, cv::THRESH_BINARY | cv::THRESH_OTSU);
    cv::namedWindow("binary", cv::WINDOW_FREERATIO);
    cv::imshow("binary", binary);
}

void other_method(cv::Mat& image)
{
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    cv::Mat binary;
    cv::threshold(gray, binary, 0, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);
    cv::namedWindow("THRESH_OTSU", cv::WINDOW_FREERATIO);
    cv::imshow("THRESH_OTSU", binary);
    
    cv::Mat dst1, dst2, dst3;
    int kernel_size = 5;
    cv::Mat kernel_1 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(kernel_size, kernel_size), cv::Point(-1, -1));

    //顶帽
    cv::morphologyEx(binary, dst1, cv::MORPH_TOPHAT, kernel_1, cv::Point(-1, -1), 1, 0);
    cv::namedWindow("MORPH_TOPHAT", cv::WINDOW_FREERATIO);
    cv::imshow("MORPH_TOPHAT", dst1);

    //黑帽
    cv::morphologyEx(binary, dst2, cv::MORPH_BLACKHAT, kernel_1, cv::Point(-1, -1), 1, 0);
    cv::namedWindow("MORPH_BLACKHAT", cv::WINDOW_FREERATIO);
    cv::imshow("MORPH_BLACKHAT", dst2);

    //击中击不中
    cv::Mat kernel_2 = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(kernel_size, kernel_size), cv::Point(-1, -1));
    cv::morphologyEx(binary, dst3, cv::MORPH_HITMISS, kernel_2, cv::Point(-1, -1), 1, 0);
    cv::namedWindow("MORPH_HITMISS", cv::WINDOW_FREERATIO);
    cv::imshow("MORPH_HITMISS", dst3);
}





//erode 腐蚀，侵蚀
//dilate 膨胀，扩张

//cv::getStructuringElement() 生成形态学操作所需的结构元素Kernel
//Structuring Element，也称为 “核” 或 “模板”
// cv::Mat cv::getStructuringElement(
//     int shape,         // 结构元素的形状（矩形、十字形、椭圆形等）
//     cv::Size ksize,    // 结构元素的大小（宽×高，如3×3、5×5）
//     cv::Point anchor = cv::Point(-1, -1)  // 锚点位置（操作的参考点，默认是中心）
// );
//shape：形状，morph-形，形态，变形
// cv::MORPH_RECT：矩形（所有元素均为1）。——rectangle矩形
// cv::MORPH_CROSS：十字形（中心行列元素为1）。——cross
// cv::MORPH_ELLIPSE：椭圆形（拟合在矩形内的椭圆）。——ellipse椭圆形
//ksize：大小
// cv::Size(width, height)，
// 通常使用正奇数（如3, 5, 7）以确保中心点明确。
//anchor：位置，重置点
// 默认值为 cv::Point(-1, -1) 表示中心点。
// 形状唯一依赖锚点位置的情况是 MORPH_CROSS，其他情况下锚点主要影响形态学运算结果的偏移。

//cv::erode() 图像腐蚀Erosion
// void cv::erode(
//     cv::InputArray src,          // 输入图像（单通道或多通道，通常为二值图或灰度图）
//     cv::OutputArray dst,         // 输出图像（与输入尺寸、类型相同）
//     cv::InputArray kernel,       // 结构元素（腐蚀的“工具”，由 getStructuringElement 生成）
//     cv::Point anchor = cv::Point(-1, -1),  // 结构元素的锚点（默认中心Point(-1, -1)）
//     int iterations = 1,          // 腐蚀迭代次数（默认1次，次数越多，腐蚀效果越强）
//     int borderType = cv::BORDER_CONSTANT,  // 边界填充方式（默认常量填充）
//     const cv::Scalar& borderValue = cv::morphologyDefaultBorderValue()  // 边界填充值
// );

//cv::dilate() 图像膨胀
// void cv::dilate(
//     cv::InputArray src,          // 输入图像（单通道或多通道，通常为二值图或灰度图）
//     cv::OutputArray dst,         // 输出图像（与输入尺寸、类型相同）
//     cv::InputArray kernel,       // 结构元素（膨胀的“工具”，由 getStructuringElement 生成）
//     cv::Point anchor = cv::Point(-1, -1),  // 结构元素的锚点（默认中心）
//     int iterations = 1,          // 膨胀迭代次数（默认1次，次数越多，膨胀效果越强）
//     int borderType = cv::BORDER_CONSTANT,  // 边界填充方式（默认常量填充）
//     const cv::Scalar& borderValue = cv::morphologyDefaultBorderValue()  // 边界填充值
// );

//cv::morphologyEx() 组合膨胀腐蚀，高级形态学变换
// void cv::morphologyEx(
//     cv::InputArray src,          // 输入图像（单通道或多通道，通常为二值图或灰度图）
//     cv::OutputArray dst,         // 输出图像（与输入尺寸、类型相同）
//     int op,                      // 形态学操作类型（如开运算、闭运算等）
//     cv::InputArray kernel,       // 结构元素（与 erode/dilate 相同，由 getStructuringElement 生成）
//     cv::Point anchor = cv::Point(-1, -1),  // 结构元素的锚点（默认中心）
//     int iterations = 1,          // 操作迭代次数（次数越多，效果越强）
//     int borderType = cv::BORDER_CONSTANT,  // 边界填充方式
//     const cv::Scalar& borderValue = cv::morphologyDefaultBorderValue()  // 边界填充值
// );
//开运算（cv::MORPH_OPEN），
//  先腐蚀(erode)后膨胀(dilate），去除微小干扰块
//闭运算（cv::MORPH_CLOSE），
//  先膨胀(dilate)后腐蚀(erode），填充闭合区域
//形态学梯度（cv::MORPH_GRADIENT），
//  膨胀结果减去腐蚀结果(dilate(src)-erode(src))，提取边缘轮廓
//顶帽（cv::MORPH_TOPHAT，也叫 “礼帽”），
//  原图减去开运算结果(src-open(src)）,
//  提取图像中比周围区域亮且尺寸小于结构元素的区域开运算会去除这些亮的小区域，原图减去开运算结果即可保留它们）
//黑帽（cv::MORPH_BLACKHAT），
//  闭运算结果减去原图(close(src)-src），
//  提取图像中比周围区域暗且尺寸小于结构元素的区域（闭运算会填充这些暗的小区域，闭运算结果减去原图即可保留它们）

//cv::subtract 是用于图像(或数组)元素级减法运算的函数
//逐像素计算差值：对输入图像src1和src2的每个像素(i,j)，计算dst(i,j)=src1(i,j)-src2(i,j)
//输入的两个数组或图像src1、src2，要求尺寸相同、数据类型相同
// void cv::subtract(
//     cv::InputArray src1,       // 第一个输入数组/图像（被减数）
//     cv::InputArray src2,       // 第二个输入数组/图像（减数）
//     cv::OutputArray dst,       // 输出数组/图像（结果，与输入尺寸、类型相同）
//     cv::InputArray mask = cv::noArray()  // 可选掩码（仅掩码为非0的像素参与运算,默认值cv::noArray()表示无掩码所有像素参与运算）
// );