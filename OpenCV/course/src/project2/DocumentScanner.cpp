#include <opencv2/opencv.hpp>

cv::Mat imgOriginal, imgGray, imgBlur, imgCanny, imgDil, imgThre, imgWarp, imgCrop;
std::vector<cv::Point> initialPoints, docPoints;

float w = 420, h = 596;

cv::Mat preProcessing(cv::Mat img);
std::vector<cv::Point> getContours(cv::Mat mask);
void drawPoints(std::vector<cv::Point> points, cv::Scalar color);
std::vector<cv::Point> reorder(std::vector<cv::Point> initialPoints);
cv::Mat getWarp(cv::Mat img, std::vector<cv::Point> points, float w, float h);




int main()
{
    std::string path = "/home/emmm/Desktop/scnu_rm/OpenCV/course/img/paper.png";
    imgOriginal = cv::imread(path);
    resize(imgOriginal, imgOriginal, cv::Size(), 0.25, 0.25);

    //预处理
    imgThre = preProcessing(imgOriginal);

    //获取轮廓
    initialPoints = getContours(imgThre);
    //drawPoints(initialPoints, cv::Scalar(0,0,225)); //顺序随意
    docPoints = reorder(initialPoints);
    //drawPoints(docPoints, cv::Scalar(0,255,0)); //顺序固定

    //透视变换
    imgWarp = getWarp(imgOriginal, docPoints, w, h);
    drawPoints(docPoints, cv::Scalar(0,255,0));

    //裁剪
    int cropVal = 10;
    cv::Rect roi(cropVal, cropVal, w-(2*cropVal), h-(2*cropVal));
    imgCrop = imgWarp(roi);

    cv::imshow("Image Original ", imgOriginal);
    cv::imshow("Image Dilation", imgThre);
    cv::imshow("Image Warp", imgWarp);
    cv::imshow("Image Crop", imgCrop);

    cv::waitKey(0);

    return 0;
}





//预处理 - 灰度化，模糊化，边缘检测，膨胀
cv::Mat preProcessing(cv::Mat img)
{
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(imgGray, imgBlur, cv::Size(5,5), 3, 0); 
    cv::Canny(imgBlur, imgCanny, 50, 150); 
    cv::Mat kernel = getStructuringElement(cv::MORPH_RECT, cv::Size(3,3)); 
    cv::dilate(imgCanny, imgDil, kernel);
    //cv::erode(imgDil, imgErode, kernel);

    return imgDil;
}



//获取轮廓 - 得到最大矩形
std::vector<cv::Point> getContours(cv::Mat mask)
{
    std::vector< std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    // 检测轮廓
    cv::findContours(mask, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 为所有轮廓预分配空间(必须放在循环外)
    std::vector< std::vector<cv::Point> > conPoly(contours.size()); 
    std::vector<cv::Rect> boundRect(contours.size()); 

    //最大矩形 - 检测目标纸张 
    std::vector<cv::Point> biggest;
    int maxArea = 0;

    for(int i=0; i<contours.size(); i++)
    {
        //过滤区域
        int area = contourArea(contours[i]);
        std::cout << area << std::endl;

        if(area > 1000)
        {
            // 找多边形近似值
            float peri = cv::arcLength(contours[i], true);
            cv::approxPolyDP(contours[i], conPoly[i], 0.02*peri, true);

            if(area > maxArea && conPoly[i].size() == 4)
            {
                //drawContours(imgOriginal, conPoly, i, cv::Scalar(255,0,255), 5);
                biggest = {conPoly[i][0], conPoly[i][1], conPoly[i][2], conPoly[i][3]};
                maxArea = area;
            }

            // 绘制轮廓
            //cv::drawContours(imgOriginal, conPoly, i, cv::Scalar(255,0,255), 2);
            //rectangle(imgOriginal, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0, 255, 0), 2);
        }
    }

    return biggest;
}



// 画出顶点
void drawPoints(std::vector<cv::Point> points, cv::Scalar color)
{
    for(int i=0; i<points.size(); i++)
    {
        circle(imgOriginal, points[i], 5, color, cv::FILLED);
        putText(imgOriginal, std::to_string(i), points[i], cv::FONT_HERSHEY_PLAIN, 4, color, 2);
    }
}



// 顶点排序
std::vector<cv::Point> reorder(std::vector<cv::Point> points)
{
    std::vector<cv::Point> newPoints;
    std::vector<int> sumPoints, subPoints;

    for(int i=0; i<4; i++)
    {
        sumPoints.push_back(points[i].x + points[i].y);
        subPoints.push_back(points[i].x - points[i].y);
    }

    newPoints.push_back(points[ min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin() ]); //0
    newPoints.push_back(points[ max_element(subPoints.begin(), subPoints.end()) - subPoints.begin() ]); //1
    newPoints.push_back(points[ min_element(subPoints.begin(), subPoints.end()) - subPoints.begin() ]); //2
    newPoints.push_back(points[ max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin() ]); //3
    //min_element/max_element返回容器中最小/大值元素的迭代器，去容器的起始迭代器sumPoints.begin()/subPoints.begin()，得到的最小/大值的索引

    return newPoints;
}



// 透视变换
cv::Mat getWarp(cv::Mat img, std::vector<cv::Point> points, float w, float h)
{
    cv::Point2f src[4] = {points[0], points[1], points[2], points[3]};
    cv::Point2f dst[4] = {{0.0f, 0.0f}, {w, 0.0f}, {0.0f, h}, {w, h}};

    cv::Mat mat;
    mat = cv::getPerspectiveTransform(src, dst); 
    cv::warpPerspective(img, imgWarp, mat, cv::Point(w, h)); 

    return imgWarp;
}





// min_element 在容器（如 vector）的指定范围内查找最小值元素，并返回指向该元素的迭代器（iterator）
//
// #include <algorithm>
// template <class ForwardIterator>
// ForwardIterator min_element(ForwardIterator first, ForwardIterator last);
//
// 参数：first（范围起始迭代器）、last（范围结束迭代器，不包含在范围内），即查找范围为 [first, last)。
// 返回值：指向范围内第一个最小值元素的迭代器（若有多个相同的最小值，返回第一个出现的位置）