/********************通道分离、合并、混合************************/

#include <opencv2/opencv.hpp>



void split_channels(cv:: Mat bgr_img)
{
    //分离三个通道并显示            
    std::vector<cv::Mat> channels;
    cv::split(bgr_img, channels);
    cv::Mat blue = channels.at(0);
    cv::Mat green = channels.at(1);
    cv::Mat red = channels.at(2);

    cv::resize(bgr_img, bgr_img, {}, 0.5, 0.5);
    cv::resize(blue, blue, {}, 0.5, 0.5);
    cv::resize(green, green, {}, 0.5, 0.5);
    cv::resize(red, red, {}, 0.5, 0.5);

    cv::imshow("bgr_img", bgr_img);
    cv::imshow("blue", blue);
    cv::imshow("green", green);
    cv::imshow("red", red);
}



void split_merge_mix(cv::Mat image)
{
    //通道分离
    cv::Mat bgr[3]; 
	cv::split(image, bgr);	// 通道分离
	cv::namedWindow("B", cv::WINDOW_FREERATIO);
	cv::namedWindow("G", cv::WINDOW_FREERATIO);
	cv::namedWindow("R", cv::WINDOW_FREERATIO);
	cv::imshow("B", bgr[0]);
	cv::imshow("G", bgr[1]);
	cv::imshow("R", bgr[2]);
 
    //通道合并
	cv::Mat dst;
	bgr[1] = 0;			// 将 G 通道置为 0
	bgr[2] = 0;			// 将 R 通道置为 0
	cv::merge(bgr, 3, dst);	// 通道合并
	cv::namedWindow("channel_demo", cv::WINDOW_FREERATIO);
	cv::imshow("channel_demo", dst);

    //混合图像
	cv::Mat src1 = image;
	cv::Mat src2 = dst;
	cv::Mat dst2;
	cv::addWeighted(src1, 0.5, src2, 0.5, 0, dst2);	// 图像混合
	cv::namedWindow("channel_demo2", cv::WINDOW_FREERATIO);
	cv::imshow("channel_demo2", dst2);
}



int main()
{
    cv::Mat bgr_img;
    bgr_img = cv::imread("/home/emmm/Desktop/scnu_rm/OpenCV/digital/img/test.jpg");

    //分离三个通道并显示
    /*注意加&，否则下面合并时修改的是拷贝的通道值*/
    /*cv::Mat& blue = channels.at(0);  // 错误！at()返回的是值，不是引用，这样会导致悬空引用*/
    std::vector<cv::Mat> channels;
    cv::split(bgr_img, channels);
    cv::Mat& blue = channels[0];
    cv::Mat& green = channels[1];
    cv::Mat& red = channels[2];

    // 创建用于显示的缩放版本（不修改原始数据）
    cv::Mat bgr_small, blue_small, green_small, red_small;
    cv::resize(bgr_img, bgr_small, {}, 0.5, 0.5);
    cv::resize(blue, blue_small, {}, 0.5, 0.5);
    cv::resize(green, green_small, {}, 0.5, 0.5);
    cv::resize(red, red_small, {}, 0.5, 0.5);

    cv::imshow("bgr_img", bgr_small);
    cv::imshow("blue", blue_small);
    cv::imshow("green", green_small);
    cv::imshow("red", red_small);

    /*
    void cv::resize(InputArray src, OutputArray dst, 
        Size dsize, double fx = 0, ouble fy = 0, 
            int interpolation = INTER_LINEAR);
    src: bgr_img - 输入图像
    dst: bgr_img - 输出图像（与输入相同，原地操作）
    dsize: {} - 空 Size，表示使用缩放比例
    fx: 0.5 - 水平方向缩放为原来的 50%
    fy: 0.5 - 垂直方向缩放为原来的 50%
    interpolation: 未指定，使用默认值 INTER_LINEAR

    resize(bgr_img,bgr_img) 是原地缩放，改变了原通道的值
    建议创建新变量用于显示缩放版本（不修改原channels）
    cv::Mat bgr_img_small
    cv::resize(bgr_img, bgr_img_small, {}, 0.5, 0.5);
    cv::imshow("bgr_img", bgr_img_small);
    */

    // 修改通道：只保留蓝色
    green = cv::Mat::zeros(green.size(), green.type());  // 绿色通道置零
    red = cv::Mat::zeros(red.size(), red.type());        // 红色通道置零
    // 合并并显示结果
    cv::Mat dst_blue;
    cv::merge(channels, dst_blue);
    /* cv::resize(dst_blue, dst_blue, {}, 0.5, 0.5); 
    若之前cv::resize(bgr_img, bgr_img_small, {}, 0.5, 0.5);把原通道缩小了0.5,要是再缩小0.5就会变成0.25 */
    cv::Mat dst_blue_small;
    cv::resize(dst_blue, dst_blue_small, {}, 0.5, 0.5);
    cv::imshow("dst_blue", dst_blue_small);

    //通道混合: BGR 转 RGB
    cv::Mat dst = cv::Mat::zeros(bgr_img.size(), bgr_img.type());
    int from_to[] = {0, 2, 1, 1, 2, 0};  //BGR->RGB
    /* {0,2}输入矩阵的 0 通道复制到输出矩阵的 2 通道
    {1,1}输入矩阵的 1 通道复制到输出矩阵的 1 通道
    {2,0}输入矩阵的 2 通道复制到输出矩阵的 0 通道 */
    cv::mixChannels(&bgr_img, 1, &dst, 1, from_to, 3);
    /*1张原图bgr_img，1张目标图像dst，3个通道即3对映射*/
    cv::Mat dst_small;
    cv::resize(dst, dst_small, {}, 0.5, 0.5);
    cv::imshow("mix", dst_small);

    cv::waitKey(0);

    return 0;
}





//OpenCV默认使用BGR顺序，不是RGB
//0蓝色，1绿色，2红色

//cv::split() 多通道分离
//void cv::split(const Mat & src, Mat * mvbegin)
//void cv::split(InputArray m, OutputArrayOfArrays mv)
//m 输入图像，多通道矩阵
//mv 输出容器，存储分离后单通道图像，分离后的每个通道都是单通道的灰度图
// void cv::split(const Mat& src, std::vector<Mat>& mv);

//std::vector::at(index)
//std::vector的成员函数，返回指定索引位置的元素应用，会进行边界检查
// 以下几种方式是等价的：
// cv::Mat blue1 = channels[0];        // 使用操作符[]，不进行边界检查
// cv::Mat blue2 = channels.at(0);     // 使用at()，有边界检查
// cv::Mat blue3 = channels.front();   // 获取第一个元素

//cv::merge() 多通道合并
//void cv::merge(const Mat * mv, size_t  count, OutputArray dst) 
//void cv::merge(InputArrayOfArrays mv, OutputArray dst)
//mv: 输入的单通道矩阵数组或向量
//count: 矩阵的数量（第一个重载）
//dst: 输出的多通道矩阵

//cv::Mat::zeros() 创建一个指定大小和类型的矩阵，并将其所有元素初始化为 0
// MatExpr zeros(int rows, int cols, int type);
// MatExpr zeros(Size size, int type);
// MatExpr zeros(int ndims, const int* sz, int type);
//type 参数指定了矩阵的数据类型和通道数，例如:CV_8UC1——8位无符号单通道矩阵(灰度图)，CV_8UC3——RGB彩色图像，CV_32FC3——32位浮点三通道矩阵(彩色图)

//cv::mixChannels()
//使用矩阵数组
// void cv::mixChannels(
//     const Mat* src,  // 输入矩阵数组
//     size_t nsrcs,    // 输入矩阵的数量
//     Mat* dst,        // 输出矩阵数组
//     size_t ndsts,    // 输出矩阵的数量
//     const int* fromTo, // 通道映射数组
//     size_t npairs    // 映射对的数量  )
//使用矩阵向量
// void cv::mixChannels(
//     InputArrayOfArrays src,  // 输入矩阵向量
//     InputOutputArrayOfArrays dst, // 输出矩阵向量
//     const std::vector<int>& fromTo // 通道映射向量
// )
// src：输入矩阵，可以是多个矩阵组成的数组或向量
// nsrcs：输入矩阵的数量
// dst：输出矩阵，需要预先分配好内存，大小和深度与 src[0] 相同
// ndsts：输出矩阵的数量
// fromTo：通道映射数组，指定源通道和目标通道的对应关系，格式为 [源1, 目标1, 源2, 目标2, ...]
// npairs：fromTo 中映射对的数量
/* fromTo 参数是 mixChannels 的核心，它决定了通道如何复制。通道编号规则如下：
第一个输入图像的通道索引从 0 到 src[0].channels()-1
第二个输入图像的通道索引从 src[0].channels() 到 src[0].channels() + src[1].channels() - 1，依此类推
输出图像的通道索引采用相同的方案 */

//cv::addWeighted() 把两张图像按照权重混合
// void cv::addWeighted(
//     InputArray src1,     // 第一个输入数组
//     double alpha,        // 第一个数组的权重
//     InputArray src2,     // 第二个输入数组  
//     double beta,         // 第二个数组的权重
//     double gamma,        // 添加到每个和的标量
//     OutputArray dst,     // 输出数组
//     int dtype = -1       // 输出数组的深度（可选）
// );
//dst = src1 × alpha + src2 × beta + gamma