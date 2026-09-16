#include <opencv2/opencv.hpp>

int main()
{
    std::string path = "/home/emmm/Desktop/scnu_rm/OpenCV/course/img/person.png";
    cv::Mat img = cv::imread(path);
    resize(img, img, cv::Size(500, 500));

    cv::Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;
    //图像灰度化
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
    //高斯模糊
    cv::GaussianBlur(imgGray, imgBlur, cv::Size(7,7), 5, 0); //数值越小模糊度越低
    //边缘检测
    cv::Canny(imgBlur, imgCanny, 50, 150); //阈值越小检测的边缘越多

    //膨胀
    cv::Mat kernel = getStructuringElement(cv::MORPH_RECT, cv::Size(5,5)); //设置核，size越大膨胀越多,只能用奇数
    cv::dilate(imgCanny, imgDil, kernel);
    //腐蚀
    cv::erode(imgDil, imgErode, kernel);

    cv::imshow("Image", img);
    cv::imshow("Image Gray", imgGray);
    cv::imshow("Image Blur", imgBlur);
    cv::imshow("Image Canny", imgCanny);
    cv::imshow("Image Dilation", imgDil);
    cv::imshow("Image Erode", imgErode);

    cv::waitKey(0);

    return 0;
}





// cv::GaussianBlur（高斯模糊）—— 去噪声
// void GaussianBlur(
//     InputArray src,
//     OutputArray dst,
//     Size ksize,    // 高斯核大小（必须是正的奇数，如3x3,5x5,7x7）
//     double sigmaX, // X方向标准差（控制模糊程度，0则由ksize自动计算）
//     double sigmaY = 0, // Y方向标准差（默认与sigmaX相同）
//     int borderType = BORDER_DEFAULT
// );
//
// ksize（核大小）：
// 噪声少、目标小（如小灯条）：用3x3（最小核，保留更多细节）。
// 噪声多、目标大（如大面积色块）：用5x5或7x7（更强模糊，但可能模糊边缘）。
// 原则：核大小不超过目标最小尺寸的 1/3（避免目标被模糊掉）
//
// sigmaX：
// 通常设为0（自动计算，公式：sigma = 0.3*((ksize-1)*0.5 - 1) + 0.8）。
// 手动调整（0.5~2.0之间，值越大模糊越强）

// cv::Canny（边缘检测）—— 提取关键边缘
// void Canny(
//     InputArray image,
//     OutputArray edges,
//     double threshold1, // 低阈值（控制边缘连接：低阈值→更多弱边缘被保留并连接）
//     double threshold2, // 高阈值（控制强边缘：高阈值→只有明显边缘被保留）
//     int apertureSize = 3, // Sobel算子大小（3,5,7，默认3即可）
//     bool L2gradient = false // 是否用L2范数计算梯度（默认false，用L1范数，速度快）
// );
//
// threshold2 ≈ 2~3 * threshold1（经验值，确保强边缘能连接弱边缘）
// 先固定threshold2，从大到小试：
// 减小threshold2（让更多边缘被保留），增大threshold2（过滤弱噪声边缘）
// 再调整threshold1（约为threshold2的 1/2~1/3）：
// 减小threshold1（让弱边缘参与连接），增大threshold1（过滤噪声边缘）

// cv::erode（腐蚀）与cv::dilate（膨胀）—— 形态学优化，处理轮廓细节
// 腐蚀（erode）：缩小前景区域，消除小噪声、断开连接（如把粘连的两个小目标分开）
// 膨胀（dilate）：扩大前景区域，连接断裂的轮廓、填补小漏洞（如修复边缘的缺口）
// 先腐蚀后膨胀叫 “开运算”，去噪声；先膨胀后腐蚀叫 “闭运算”，补漏洞
// void erode/dilate(
//     InputArray src,
//     OutputArray dst,
//     InputArray kernel, // 结构元素（控制腐蚀/膨胀的范围和形状，如3x3矩形、圆形）
//     Point anchor = Point(-1,-1), // 核的锚点（默认中心）
//     int iterations = 1, // 迭代次数（次数越多，效果越强）
//     int borderType = BORDER_CONSTANT,
//     const Scalar& borderValue = morphologyDefaultBorderValue()
// );
// 小噪声用小核，大噪声用大核（小心把目标侵蚀）；迭代通常1次，噪声过多最多2次