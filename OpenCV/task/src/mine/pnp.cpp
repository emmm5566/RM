#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <algorithm>

cv::Mat preProcessing(cv::Mat & img, int minVal, int maxVal);
std::vector<cv::RotatedRect> getLightBars(cv::Mat & img);
std::vector<cv::Point2f> getArmor(std::vector<cv::RotatedRect> & lightBars);
void pnp(cv::Mat & img, std::vector<cv::Point2f> & armorPoints);

// 结构体打包所有局部数据
struct TrackbarParams {
    cv::Mat& srcImg;   // 原图引用（main局部变量）
    int* minVal;       // minVal指针（指向main局部变量）
    int* maxVal;       // maxVal指针（指向main局部变量）
};

// 滑块回调函数（双滑块共用一个回调，滑动任意一个都刷新全流程）
void thresholdCallback(int val, void* userData) {
    TrackbarParams* params = static_cast<TrackbarParams*>(userData);
    if (!params) return;

    // 1. 预处理（传入双阈值）
    cv::Mat imgPre = preProcessing(
        params->srcImg, 
        *params->minVal,  // 从结构体获取最新minVal
        *params->maxVal   // 从结构体获取最新maxVal
    );

    // 2. 检测灯条和装甲板
    std::vector<cv::RotatedRect> lightBars = getLightBars(imgPre);
    std::vector<cv::Point2f> armorPoints = getArmor(lightBars);

    // 3. 绘制结果（克隆原图，避免叠加）
    cv::Mat displayImg = params->srcImg.clone();
    // 绘制灯条
    for (auto& bar : lightBars) {
        cv::Point2f pts[4];
        bar.points(pts);
        for (int i = 0; i < 4; i++) {
            cv::line(displayImg, pts[i], pts[(i+1)%4], cv::Scalar(0,255,0), 3);
        }
    }
    // 绘制装甲板
    if (!armorPoints.empty()) {
        for (int i = 0; i < 4; i++) {
            cv::line(displayImg, armorPoints[i], armorPoints[(i+1)%4], cv::Scalar(0,0,255), 2);
        }
    }

    // 4. PnP解算和文字绘制
    pnp(displayImg, armorPoints);

    // 5. 实时刷新显示
    cv::resize(displayImg, displayImg, {}, 2, 2);
    cv::imshow("Image", displayImg);
    cv::imshow("ImagePre", imgPre);
}

int main()
{
    cv::Mat srcImg = cv::imread("../img/pnp.jpg");
    if (srcImg.empty()) {
        std::cout << "Error opening image!" << std::endl;
        return -1;
    }
    int minVal = 150;   // 初始minVal
    int maxVal = 255;   // 初始maxVal

    // 打包局部数据到结构体
    TrackbarParams params = {
        .srcImg = srcImg,
        .minVal = &minVal,  // 绑定局部minVal
        .maxVal = &maxVal   // 绑定局部maxVal
    };

    // 创建滑块窗口（两个滑块：MinVal + MaxVal）
    cv::namedWindow("Trackbars", cv::WINDOW_NORMAL);
    cv::resizeWindow("Trackbars", 400, 150);  // 扩大窗口容纳两个滑块

    // 滑块1：调节MinVal（绑定局部minVal，范围0-255）
    cv::createTrackbar(
        "MinVal",          // 滑块名称
        "Trackbars",       // 所属窗口
        &minVal,           // 绑定局部minVal（滑块位置同步）
        255,               // 最大值
        thresholdCallback, // 回调函数（共用一个）
        &params            // 传递结构体指针
    );

    // 滑块2：调节MaxVal（绑定局部maxVal，范围0-255）
    cv::createTrackbar(
        "MaxVal",          // 滑块名称
        "Trackbars",       // 所属窗口
        &maxVal,           // 绑定局部maxVal（滑块位置同步）
        255,               // 最大值
        thresholdCallback, // 回调函数（共用一个）
        &params            // 传递结构体指针
    );

    // 初始化显示（首次执行全流程）
    thresholdCallback(minVal, &params);

    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}


cv::Mat preProcessing(cv::Mat & img, int minVal, int maxVal)
{
    cv::Mat channels[3];
    cv::split(img, channels); // 分离通道（用红色通道）

    cv::Mat binary, Gaussian;
    // 二值化：像素值 > minVal → 设为maxVal，否则设为0（THRESH_BINARY）
    cv::threshold(channels[2], binary, minVal, maxVal, cv::THRESH_BINARY);
    cv::GaussianBlur(binary, Gaussian, cv::Size(5,5), 0); // 高斯模糊

    return Gaussian;
}

// 灯条检测
std::vector<cv::RotatedRect> getLightBars(cv::Mat & img)
{
    std::vector< std::vector <cv::Point> > contours;
    std::vector< cv::Vec4i > hierarchy;
    cv::findContours(img, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    std::vector< cv::RotatedRect > lightBars;
    for(auto & contour : contours)
    {
        double area = cv::contourArea(contour);
        if(area < 50.0) continue;

        cv::RotatedRect minRect = cv::minAreaRect(contour);
        float width = minRect.size.width;
        float height = minRect.size.height;
        if(width == 0 || height == 0) continue;
        float aspectRatio = std::max(width, height) / std::min(width, height);
        if(aspectRatio >= 1.3 && std::max(height, width)>36)
        {
            lightBars.push_back(minRect);
        }
    }
    return lightBars;
}

// 装甲板检测
std::vector<cv::Point2f> getArmor(std::vector<cv::RotatedRect> & lightBars)
{
    if(lightBars.size() < 2) 
        return {};

    // 获取两个灯条的中心
    cv::Point2f center1 = lightBars[0].center;
    cv::Point2f center2 = lightBars[1].center;
    // 区分左右灯条（按x坐标）
    cv::Point2f leftCenter = (center1.x < center2.x) ? center1 : center2;  // 左灯条中心
    cv::Point2f rightCenter = (center1.x < center2.x) ? center2 : center1; // 右灯条中心
    // 大矩形x范围 = 左灯条中心x 到 右灯条中心x（基于灯条中点）
    //装甲板顶点（x坐标）
    float minX = leftCenter.x;   // 左边界 = 左灯条中心x
    float maxX = rightCenter.x;  // 右边界 = 右灯条中心x

    std::vector< cv::Point2f > allVertices;
    cv::Point2f pts[4];
    lightBars[0].points(pts);
    for(int i=0; i<4; i++) allVertices.push_back(pts[i]);
    lightBars[1].points(pts);
    for(int i=0; i<4; i++) allVertices.push_back(pts[i]);

    //装甲板顶点（y坐标）
    //float minX = allVertices[0].x, maxX = allVertices[0].x;
    float minY = allVertices[0].y, maxY = allVertices[0].y;
    for(auto & allVertice : allVertices)
    {
        //minX = std::min(minX, allVertice.x);
        //maxX = std::max(maxX, allVertice.x);
        minY = std::min(minY, allVertice.y);
        maxY = std::max(maxY, allVertice.y);
    }

    std::vector< cv::Point2f > rectVertices;
    rectVertices.push_back(cv::Point2f(minX, minY));
    rectVertices.push_back(cv::Point2f(maxX, minY));
    rectVertices.push_back(cv::Point2f(maxX, maxY));
    rectVertices.push_back(cv::Point2f(minX, maxY));
    return rectVertices;
}

// pnp解算
void pnp(cv::Mat & img, std::vector<cv::Point2f> & armorPoints)
{
    if(armorPoints.size() != 4)
    {
        cv::putText(img, "No valid armor!", cv::Point(20, 30), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,0,255), 1);
        return;
    }

    float LIGHTBAR_LENGTH = 0.056;
    float ARMOR_WIDTH = 0.135;
    std::vector< cv::Point3f> objectPoints
    {
        {-ARMOR_WIDTH/2, -LIGHTBAR_LENGTH/2, 0},
        {ARMOR_WIDTH/2, -LIGHTBAR_LENGTH/2, 0},
        {ARMOR_WIDTH/2, LIGHTBAR_LENGTH/2, 0},
        {-ARMOR_WIDTH/2, LIGHTBAR_LENGTH/2, 0}
    };

    cv::Mat cameraMatrix = (cv::Mat_<double>(3, 3) << 
        2422.61547, 0, 706.68406,
        0, 2420.80771, 564.29241,
        0, 0, 1);

    cv::Mat distCoeffs = (cv::Mat_<double>(5,1) << -0.018647, 0.084359, -0.000925, 0.000312, 0.000000);

    cv::Mat rvec, tvec;
    cv::solvePnP(objectPoints, armorPoints, cameraMatrix, distCoeffs, rvec, tvec);

    std::string tvecText = "tvec  X:" + std::to_string(tvec.at<double>(0)).substr(0,6)
        + "  Y:" + std::to_string(tvec.at<double>(1)).substr(0,6)
        + "  Z:" + std::to_string(tvec.at<double>(2)).substr(0,6);
    std::string rvecText = "rvec  X:" + std::to_string(rvec.at<double>(0)).substr(0,6)
        + "  Y:" + std::to_string(rvec.at<double>(1)).substr(0,6)
        + "  Z:" + std::to_string(rvec.at<double>(2)).substr(0,6);
    cv::putText(img, tvecText, cv::Point(20, 30), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,255,255), 1);
    cv::putText(img, rvecText, cv::Point(20, 60), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,255,255), 1);

    cv::Mat rmat;
    cv::Rodrigues(rvec, rmat);
    double pitch = std::atan2(rmat.at<double>(0,2), rmat.at<double>(2,2)) * 180 / CV_PI;
    double roll = - std::asin(rmat.at<double>(1,2)) * 180 / CV_PI;
    double yaw = std::atan2(rmat.at<double>(1,0), rmat.at<double>(1,1)) * 180 / CV_PI;

    std::string eulerText = "euler(deg)  pitch:" + std::to_string(pitch).substr(0,5)
        + "  roll:" + std::to_string(roll).substr(0,5)
        + "  yaw:" + std::to_string(yaw).substr(0,5);
    cv::putText(img, eulerText, cv::Point(20, 90), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,255,255), 1);
}