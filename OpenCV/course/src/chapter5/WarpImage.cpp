#include <opencv2/opencv.hpp>

int main()
{
    std::string path = "/home/emmm/Desktop/scnu_rm/OpenCV/course/img/cards.png";
    cv::Mat img = cv::imread(path);
    
    //截取点像素坐标
    float weight = 250, height = 350;
    cv::Point2f src[4] = {{714,726}, {1017,798}, {567,1053}, {891,1140}};
    cv::Point2f dst[4] = {{0.0f,0.0f}, {weight,0.0f}, {0.0f,height}, {weight,height}}; //注意点的顺序对应

    //透视变换（Perspective Transformation）
    cv::Mat mat, imgWarp;
    mat = cv::getPerspectiveTransform(src, dst); //计算透视变换矩阵：根据源图像和目标图像中的对应点，计算透视变换矩阵mat
    cv::warpPerspective(img, imgWarp, mat, cv::Point(weight, height)); // 应用透视变换：根据透视变换矩阵mat，将原图像img透视变换输出imgWarp
    
    //在四个坐标点上画小圆圈
    for(int i=0; i<4; i++)
    {
        circle(img, src[i], 10, cv::Scalar(0, 0, 255), cv::FILLED);
    }

    cv::imshow("Image", img);
    cv::imshow("Image Warp", imgWarp);

    cv::waitKey(0);

    return 0;
}





// cv::getPerspectiveTransform —— 计算透视变换矩阵
// cv::Mat getPerspectiveTransform(
//     const cv::InputArray src,  // 原始图像中的4个顶点（vector<Point2f>，非共线）
//     const cv::InputArray dst   // 目标图像中对应的4个顶点（vector<Point2f>，非共线）
// );

// cv::warpPerspective —— 应用透视变换
// void warpPerspective(
//     cv::InputArray src,        // 输入图像（原始图像）
//     cv::OutputArray dst,       // 输出图像（变换后的图像）
//     cv::InputArray M,          // 透视变换矩阵（3x3，由getPerspectiveTransform得到）
//     cv::Size dsize,            // 输出图像的尺寸（宽x高）
//     int flags = cv::INTER_LINEAR,  // 插值方法（影响变换后图像的平滑度）
//     int borderMode = cv::BORDER_CONSTANT,  // 边界填充模式
//     const cv::Scalar& borderValue = cv::Scalar()  // 边界填充颜色
// );
//
// flags：插值方法（常用选项）：
// cv::INTER_LINEAR：双线性插值（默认，平衡速度和质量）；
// cv::INTER_NEAREST：最近邻插值（速度快，但质量低，有锯齿）；
// cv::INTER_CUBIC：双三次插值（质量高，适合细节丰富的图像，但速度慢）