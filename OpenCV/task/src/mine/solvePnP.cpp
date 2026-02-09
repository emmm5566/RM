#include <opencv2/opencv.hpp>
#include <vector>

struct TrackbarParams
{
    cv::Mat& image;
    int* Threshold;
};

cv::Mat preProcessing(cv::Mat & img, int Threshold);
std::vector<cv::RotatedRect> getLightBars(cv::Mat & img);
std::vector<cv::Point2f> getArmor(std::vector<cv::RotatedRect> & lightBars);
void pnp(cv::Mat & img, std::vector<cv::Point2f> & armorPoints);
void callBack(int val, void * valName);



int main()
{
    //读取图像
    cv::Mat img = cv::imread("../img/solvepnp.bmp"); //../回到上一级目录task
    if(img.empty())
    {
        std::cout << "Error opening" << std::endl;
        return -1;
    }

    int binaryThreshold = 0;
    // 打包局部数据到结构体（仅用于回调函数访问，无全局共享）
    TrackbarParams params = {
        .image = img,        // 绑定main的局部原图
        .Threshold = &binaryThreshold  // 绑定main的局部阈值
    };
    // 创建窗口和滑块（滑块绑定局部阈值，通过结构体传递数据）
    cv::namedWindow("Trackbars", cv::WINDOW_NORMAL);
    cv::resizeWindow("Trackbars", 400, 100);
    cv::createTrackbar(
        "Binary Threshold",
        "Trackbars",
        &binaryThreshold,  // 滑块初始位置绑定局部阈值
        255,
        callBack,  // 回调函数（全局，但仅访问结构体中的局部数据）
        &params             // 传递结构体指针（回调函数通过这个访问局部数据）
    );
    // 初始化显示（首次执行回调逻辑）
    callBack(binaryThreshold, &params);

    cv::imshow("Image", img);
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}



void callBack(int val, void* valName)
{
    TrackbarParams* params = static_cast<TrackbarParams*>(valName);
    if(!params) return;

    *params->Threshold = val;

    //预处理
    cv::Mat imgPre = preProcessing(params->image, *params->Threshold);

    cv::Mat displayImg = params->image.clone();
    //检测灯条
    std::vector<cv::RotatedRect> lightBars = getLightBars(imgPre);
    for(auto & lightBar : lightBars)
    {
        cv::Point2f vertices[4];
        lightBar.points(vertices);
        for(int i=0; i<4; i++)
        {
            cv::line(displayImg, vertices[i], vertices[(i+1)%4], cv::Scalar(0,255,0), 3);
        }
    }

    //检测装甲板
    std::vector<cv::Point2f> armorPoints = getArmor(lightBars);
    if(!armorPoints.empty())
    {
        cv::RotatedRect armor = cv::minAreaRect(armorPoints);
        for(int i=0; i<4; i++)
        {
            line(displayImg, armorPoints[i], armorPoints[(i+1)%4], cv::Scalar(0,0,255), 2);
        }
    }

    //pnp解算
    pnp(displayImg, armorPoints);

    //实时刷新显示
    resize(displayImg, displayImg, {}, 2, 2);
    cv::imshow("ImagePre", imgPre);
    cv::imshow("displayImg", displayImg);
}



cv::Mat preProcessing(cv::Mat & img, int Threshold)
{
    cv::Mat channels[3];
    cv::split(img, channels);

    //滑动条没有绑定回调函数，且阈值变量是局部变量，拖动滑动条不会触发预处理逻辑重新执行，图像不会更新
    //要实现动态调整阈值，需要调用回调函数

    cv::Mat binary, Gaussian;
    cv::threshold(channels[2], binary, Threshold, 255, 0);
    cv::GaussianBlur(binary, Gaussian, cv::Size(5,5), 0);

    return Gaussian;
}

std::vector<cv::RotatedRect> getLightBars(cv::Mat & img)
{
    //轮廓检测
    std::vector< std::vector <cv::Point> > contours;
    std::vector< cv::Vec4i > hierarchy;
    cv::findContours(img, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    std::vector< cv::RotatedRect > lightBars;

    //最小外接矩形
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

std::vector<cv::Point2f> getArmor(std::vector<cv::RotatedRect> & lightBars)
{
    if(lightBars.size() < 2) 
        return {}; //返回一个空向量

    // // 获取两个灯条的中心
    // cv::Point2f center1 = lightBars[0].center;
    // cv::Point2f center2 = lightBars[1].center;
    // // 区分左右灯条（按x坐标）
    // cv::Point2f leftCenter = (center1.x < center2.x) ? center1 : center2;  // 左灯条中心
    // cv::Point2f rightCenter = (center1.x < center2.x) ? center2 : center1; // 右灯条中心
    // // 大矩形x范围 = 左灯条中心x 到 右灯条中心x（基于灯条中点）
    // //装甲板顶点（x坐标）
    // float minX = leftCenter.x;   // 左边界 = 左灯条中心x
    // float maxX = rightCenter.x;  // 右边界 = 右灯条中心x

    //收集所有顶点
    std::vector< cv::Point2f > allVertices;
    cv::Point2f pts[4];
    lightBars[0].points(pts);
    for(int i=0; i<4; i++)
    {
        allVertices.push_back(pts[i]);
    } 
    lightBars[1].points(pts);
    for(int i=0; i<4; i++)
    {
        allVertices.push_back(pts[i]);
    }

    //装甲板顶点
    float minX = allVertices[0].x, maxX = allVertices[0].x;
    float minY = allVertices[0].y, maxY = allVertices[0].y;
    for(auto & allVertice : allVertices)
    {
        minX = std::min(minX, allVertice.x);
        maxX = std::max(maxX, allVertice.x);
        minY = std::min(minY, allVertice.y);
        maxY = std::max(maxY, allVertice.y);
    }

    // 构建大矩形顶点
    std::vector< cv::Point2f > rectVertices; 
    rectVertices.push_back(cv::Point2f(minX, minY));
    rectVertices.push_back(cv::Point2f(maxX, minY));
    rectVertices.push_back(cv::Point2f(maxX, maxY));
    rectVertices.push_back(cv::Point2f(minX, maxY));   

    return rectVertices;
}

void pnp(cv::Mat & img, std::vector<cv::Point2f> & armorPoints)
{
    // 确保装甲板顶点数为4（与世界点数量一致）
    if(armorPoints.size() != 4)
    {
        std::cout << "Armor points size is not 4!" << std::endl;
        return;
    }

    //世界坐标系中三维点
    float LIGHTBAR_LENGTH = 0.056; //灯条长度m
    float ARMOR_WIDTH = 0.135; //装甲板宽度m
    std::vector< cv::Point3f> objectPoints
    {
        {-ARMOR_WIDTH/2, -LIGHTBAR_LENGTH/2, 0},
        {ARMOR_WIDTH/2, -LIGHTBAR_LENGTH/2, 0},
        {ARMOR_WIDTH/2, LIGHTBAR_LENGTH/2, 0},
        {-ARMOR_WIDTH/2, LIGHTBAR_LENGTH/2, 0}
    };

    //相机内参
    //cv::Mat camera_matrix = (cv::Mat_<double>(3,3) << fx, 0, cx, 0, fy, cy, 0, 0, 1);  
    //cv::Mat_<double>(3,3)
    cv::Mat cameraMatrix = (cv::Mat_<double>(3, 3) << 
        2422.61547, 0, 706.68406,
        0, 2420.80771, 564.29241,
        0, 0, 1);

    //畸变系数
    //cv::Mat distort_coeffs = (cv::Mat_<double>(1,5) << k1, k2, p1, p2, k3);
    //cv::Mat_<double>(1,5)
    cv::Mat distCoeffs = (cv::Mat_<double>(5,1) << -0.018647, 0.084359, -0.000925, 0.000312, 0.000000);

    //解算PnP
    cv::Mat rvec, tvec;
    cv::solvePnP(objectPoints, armorPoints, cameraMatrix, distCoeffs, rvec, tvec);

    std::cout << "tvec: " << tvec.at<double>(0) << ", " << tvec.at<double>(1) << ", " << tvec.at<double>(2) << std::endl;
    std::cout << "rvec: " << rvec.at<double>(0) << ", " << rvec.at<double>(1) << ", " << rvec.at<double>(2) << std::endl;
    std::string tvecText = "tvec  X:" + std::to_string(tvec.at<double>(0)) 
        + "  Y:" + std::to_string(tvec.at<double>(1))
        + "  Z:" + std::to_string(tvec.at<double>(2));
    std::string rvecText = "rvec  X:" + std::to_string(rvec.at<double>(0)) 
        + "  Y:" + std::to_string(rvec.at<double>(1))
        + "  Z:" + std::to_string(rvec.at<double>(2));
    cv::putText(img, tvecText, cv::Point(20, 30), cv::FONT_HERSHEY_SIMPLEX, 0.35, cv::Scalar(0,255,255), 1);
    cv::putText(img, rvecText, cv::Point(20, 50), cv::FONT_HERSHEY_SIMPLEX, 0.35, cv::Scalar(0,255,255), 1);
    // tvec.at<double>(0) 得到一个double变量，它是tvec中首个元素的值

    //计算欧拉角（YXZ顺序，单位：弧度→角度）
    cv::Mat rmat; //旋转矩阵
    cv::Rodrigues(rvec, rmat);
    //INT_YXZ pitch=arctan2(m13,m33) roll=-arcsin(m33) yaw=arctan2(m21,m22)
    // 1. pitch（俯仰角，绕Y轴）：θ₁ = atan2(R[0][2], R[2][2])
    // double pitch = std::atan2(rmat.at<double>(0, 2), rmat.at<double>(2, 2)) * 180 / CV_PI;
    // 乘以180 / CV_PI将弧度转为角度
    double pitch = std::atan2(rmat.at<double>(0,2), rmat.at<double>(2,2));
    // 2. roll（滚转角，绕X轴）：θ₂ = -arcsin(R[1][2])
    double roll = - std::asin(rmat.at<double>(1,2));
    // 3. yaw（偏航角，绕Z轴）：θ₃ = atan2(R[1][0], R[1][1])
    double yaw = std::atan2(rmat.at<double>(1,0), rmat.at<double>(1,1));
    std::cout << "euler angles  pitch:" << pitch << ", roll:" << roll << ", yaw:" << yaw << std::endl;
    //std::to_string((int)(pitch*10)/10.0):  (int)(angle*10)/10.0保留 1 位小数，避免文本过长
    std::string eulerText = "euler angles  pitch:" + std::to_string(pitch) 
        + "  roll:" + std::to_string(roll)
        + "  yaw:" + std::to_string(yaw);    
    cv::putText(img, eulerText, cv::Point(20, 70), cv::FONT_HERSHEY_SIMPLEX, 0.35, cv::Scalar(0,255,255), 1);
}



// void cv::Rodrigues(
//     InputArray src,  // 输入：旋转向量（3×1 或 1×3）或旋转矩阵（3×3）
//     OutputArray dst, // 输出：转换后的旋转矩阵（3×3）或旋转向量（3×1 或 1×3）
//     OutputArray jacobian = noArray()  // 可选：雅可比矩阵（一般不用）
// );

//INT_YXZ pitch=arctan2(m13,m33) roll=-arcsin(m33) yaw=arctan2(m21,m22)

//atan2 计算两个参数的反正切值
//<cmath>
//double atan2(double y, double x);  // 计算 y/x 的反正切，返回值范围：[-π, π] 弧度


//旋转向量rvec  通过 罗德里格斯公式cv::Rodrigues  变为 旋转矩阵rmat
//旋转矩阵rmat  通过 反三角函数  变为 欧拉角
//欧拉角  变为 四元数

//欧拉角 
//pitch：俯仰角，表示物体绕x轴旋转
//yaw：偏航角，表示物体绕y轴旋转
//roll：翻滚角，表示物体绕z轴旋转
//Z-Y-X，即 偏航角yaw-俯仰角pitch-滚转角roll
// Z 轴：相机光轴方向（指向拍摄物体，向前为正），yaw；
// Y 轴：相机竖直方向（向上为正，与 Z 轴垂直），pitch；
// X 轴：相机水平方向（向右为正，与 Z、Y 轴构成右手坐标系），roll

// bool solvePnP(
//     InputArray objectPoints,   // 3D世界点集合（vector<Point3f>）
//     InputArray imagePoints,    // 对应的2D图像点集合（vector<Point2f>）
//     InputArray cameraMatrix,   // 相机内参矩阵（标定得到）
//     InputArray distCoeffs,     // 相机畸变系数（标定得到，无畸变时可传Mat::zeros）
//     OutputArray rvec,          // 输出旋转向量（Rodrigues向量，可转换为旋转矩阵）
//     OutputArray tvec,          // 输出平移向量（相机坐标系下物体的位置）
//     bool useExtrinsicGuess = false,  // 是否使用外部位姿初值（一般为false）
//     int flags = SOLVEPNP_ITERATIVE   // 求解方法（如迭代法、P3P法等）
// );
//
// cameraMatrix：相机内参矩阵，通过cv::calibrateCamera标定得到(fx/fy是焦距，cx/cy是图像中心) 
// cv::Mat_<double>(3,3)
// [fx,  0,  cx;
//  0,  fy, cy;
//  0,   0,  1]
// cv::Mat camera_matrix = (cv::Mat_<double>(3,3) << fx, 0, cx, 0, fy, cy, 0, 0, 1); 
//
// distCoeffs：相机畸变系数，标定后得到（如[k1, k2, p1, p2, k3]）
// cv::Mat distort_coeffs = (cv::Mat_<double>(1,5) << k1, k2, p1, p2, k3);
//
// flags：
// SOLVEPNP_ITERATIVE：迭代法（鲁棒性强，需至少 4 个点）
// SOLVEPNP_P3P：P3P 法（仅需 3 个点，对噪声敏感）

//解算pnp步骤
// 1. 世界坐标系中的三维点
//    std::vector<cv::Point3f> object_points
// 2. 图像上的二维点
//    std::vector<cv::Point2f> img_points
// 3. 自定义的物体世界坐标系（mm）
//    std::vector<cv::Point3f> obj = std::vector<cv::Point3f>
// 4. 创建相机内参数矩阵
//    cv::Mat camera_matrix = (cv::Mat_<double>(3,3) << fx, 0, cx, 0, fy, cy, 0, 0, 1);  
// 5. 创建相机畸变系数矩阵
//    cv::Mat distort_coeffs = (cv::Mat_<double>(1,5) << k1, k2, p1, p2, k3);
