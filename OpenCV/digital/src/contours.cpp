#include <opencv2/opencv.hpp>

int main()
{
    cv::Mat img, temp;
    img = cv::imread("/home/emmm/Desktop/scnu_rm/OpenCV/digital/img/shapes.png");
    resize(img, img, cv::Size(500,500)); //调整大小
    temp = img.clone(); //克隆图像

    cv::cvtColor(img, img, cv::COLOR_BGR2GRAY); //灰度化
    cv::threshold(img, img, 100, 255, cv::THRESH_BINARY); //二值化

    //存储轮廓的向量，vector<cv::Point>单个轮廓，vector<vector<cv::Point>>轮廓集合
    std::vector< std::vector<cv::Point> > contours; 
    //存储轮廓层级关系的向量容器，每个元素是cv::Vec4i（包含4个整数的向量）
    //hierachy[i]对应contours[i]（第i个轮廓）的层级信息，包含4个值：[next, prev, child, parent]
    std::vector<cv::Vec4i> hierachy; 

    //查找轮廓
    cv::findContours(img, contours, hierachy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
    //绘制轮廓
    cv::drawContours(temp, contours, -1, cv::Scalar(0,255,0), 2, 8);

    cv::imshow("image", img);
    cv::imshow("temp", temp);

    cv::waitKey(0);

    return 0;
}





// cv::findContours（轮廓检测函数）
// void cv::findContours(
//     cv::InputArray src,                // 输入图像（二值图像，黑色背景、白色前景）
//     std::vector<std::vector<cv::Point>>& contours,  // 输出轮廓集合（每个轮廓是Point数组）
//     std::vector<cv::Vec4i>& hierarchy,  // 输出轮廓层级关系（存储父子轮廓索引）
//     int mode,                          // 轮廓检索模式（如RETR_TREE：检索所有轮廓并建立层级）
//     int method,                        // 轮廓逼近方法（如CHAIN_APPROX_SIMPLE：压缩水平/垂直/对角线段）
//     cv::Point offset = cv::Point()     // 轮廓坐标偏移量（默认(0,0)，不偏移）
// );
// 轮廓检索模式（Mode）
// cv::RETR_EXTERNAL：只检索最外层的轮廓，忽略轮廓内部的孔洞。
// cv::RETR_LIST：检索所有的轮廓，但不创建任何父子关系。
// cv::RETR_CCOMP：检索所有的轮廓，并将它们组织为两层：外层轮廓和它们的内层轮廓（孔洞）。
// cv::RETR_TREE：检索所有的轮廓，并重新建立完整的轮廓层次结构
// 轮廓近似方法（Method）
// cv::CHAIN_APPROX_NONE：存储轮廓的每一个点，即轮廓的精确表示。
// cv::CHAIN_APPROX_SIMPLE（或cv::CHAIN_APPROX_TC89_L1, cv::CHAIN_APPROX_TC89_KCOS）：压缩水平、垂直和对角线段，只留下它们的端点。对于大多数应用来说，这种近似是足够的，并且可以显著减少轮廓点的数量。
// cv::CHAIN_APPROX_TC89_LKB：使用Teh-Chin链近似算法的一个变种。

// cv::findContours（轮廓绘制函数）
// void cv::drawContours(
//     cv::InputOutputArray image,                // 目标图像（在该图像上绘制轮廓）
//     const std::vector<std::vector<cv::Point>>& contours,  // 轮廓集合（由findContours输出的contours）
//     int contourIdx,                            // 要绘制的轮廓索引（-1表示绘制所有轮廓；正数表示绘制第contourIdx个轮廓）
//     const cv::Scalar& color,                   // 轮廓颜色（BGR格式，如Scalar(0,255,0)为绿色）
//     int thickness = 1,                         // 轮廓线宽（默认1；若为-1则填充轮廓内部）
//     int lineType = cv::LINE_8,                 // 线条类型（默认LINE_8，8连通线）
//     const std::vector<cv::Vec4i>& hierarchy = cv::noArray(),  // 轮廓层级关系（可选，由findContours输出的hierarchy）
//     int maxLevel = INT_MAX,                    // 绘制的最大层级（默认INT_MAX，绘制所有层级；0表示只绘制当前轮廓，1表示包含子轮廓等）
//     cv::Point offset = cv::Point()             // 轮廓坐标偏移量（默认(0,0)，不偏移；用于调整轮廓位置）
// );