#include <opencv2/opencv.hpp>



// HSV颜色阈值：{HueMin, HueMax, SaturationMin, SaturationMax, ValueMin, ValueMax}
std::vector< std::vector<int> > myColors {
    {144,179,106,255,71,255}, //red
    {124,48,117,143,170,255}, //Purple
    {68,72,156,102,126,255} //Green 
};

// 对应颜色的BGR值（用于绘制）
std::vector<cv::Scalar> myColorValues{ 
    {0, 0, 255}, //red
    {255, 0, 255}, //Purple
    {0, 255, 0} //Green
};

cv::Point myPoint(0, 0);

std::vector< std::vector<int> > newPoints; // 存储检测到的点：{x, y, 颜色索引}

std::vector<std::vector<int>> findColor(cv::Mat img);
cv::Point getContours(cv::Mat mask, cv::Mat img);
//void getContours(cv::Mat mask, cv::Mat img, std::vector<std::vector<int>>& points, int colorIdx);
void drawOnCanvas(std::vector< std::vector<int> > newPoints, std::vector<cv::Scalar> myColorValues, cv::Mat img);



int main()
{
    cv::VideoCapture cap(0);
    cv::Mat img;
    
    while(true)
    {
        cap.read(img);

        newPoints = findColor(img); // 获取所有检测到的特定颜色的点
        drawOnCanvas(newPoints, myColorValues, img); // 在图像上绘制

        cv::imshow("camera", img);
        cv::waitKey(1);
    }

    return 0;
}





//颜色检测
// 颜色检测：遍历所有颜色，提取轮廓并记录点
std::vector<std::vector<int>> findColor(cv::Mat img)
{
    cv::Mat imgHSV;
    cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);

    //std::vector<std::vector<int>> points; // 局部变量存储当前帧的点

    for(int i=0; i<myColors.size(); i++)
    {
        cv::Mat mask;
        // 提取当前颜色的掩码
        cv::Scalar lower(myColors[i][0], myColors[i][2], myColors[i][4]); 
        cv::Scalar upper(myColors[i][1], myColors[i][3], myColors[i][5]); 
        cv::inRange(imgHSV, lower, upper, mask); 
        //cv::imshow(std::to_string(i), mask);

        cv::Point myPoint = getContours(mask, img); 
        if(myPoint.x != 0 && myPoint.y != 0)
        {
            newPoints.push_back({myPoint.x, myPoint.y, i}); 
        }

        // 调用轮廓检测，将点存入points，传递当前颜色索引i
        //getContours(mask, img, points, i);
    }

    return newPoints;
    //return points;
}



//获取轮廓
// 获取轮廓：为每个符合条件的轮廓记录上边框中点，存入points
//void getContours(cv::Mat mask, cv::Mat img, std::vector<std::vector<int>>& points, int colorIdx)
cv::Point getContours(cv::Mat mask, cv::Mat img)
{
    std::vector< std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    // 检测轮廓
    cv::findContours(mask, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 为所有轮廓预分配空间(必须放在循环外)
    std::vector< std::vector<cv::Point> > conPoly(contours.size()); 
    std::vector<cv::Rect> boundRect(contours.size()); 

    for(int i=0; i<contours.size(); i++)
    {
        //过滤区域
        double area = contourArea(contours[i]);
        std::cout << area << std::endl;

        if(area > 1000)
        {
            // 找多边形近似值
            float peri = cv::arcLength(contours[i], true);
            cv::approxPolyDP(contours[i], conPoly[i], 0.02*peri, true);

            // 边界矩形
            std::cout << conPoly[i].size() << std::endl;
            boundRect[i] = cv::boundingRect(conPoly[i]);
            
            // 计算上边框中点
            //cv::Point myPoint;
            myPoint.x = boundRect[i].x + boundRect[i].width / 2;
            myPoint.y = boundRect[i].y;

            // 将点（x, y, 颜色索引）存入容器
            //points.push_back({myPoint.x, myPoint.y, colorIdx});

            // 绘制轮廓和矩形
            //cv::drawContours(img, conPoly, i, cv::Scalar(255,0,255), 2);
            //rectangle(img, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0, 255, 0), 2);
        }
    }

    return myPoint;
}



//绘制
void drawOnCanvas(std::vector< std::vector<int> > newPoints, std::vector<cv::Scalar> myColorValues, cv::Mat img)
{
    for(int i=0; i<newPoints.size(); i++)
    {
        circle(img, cv::Point(newPoints[i][0], newPoints[i][1]), 
            10, myColorValues[newPoints[i][2]], cv::FILLED);
    }
}