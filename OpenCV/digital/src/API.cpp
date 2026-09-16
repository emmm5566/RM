#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;
using namespace std;

int main() {
    // 1. 读取图像
    Mat img = imread("/home/emmm/Desktop/scnu_rm/OpenCV/digital/img/lena.jpeg");
    if (img.empty()) {
        printf("无法读取图像！\n");
        return -1;
    }
    Mat img_copy = img.clone(); // 复制原图用于后续操作


    // 2. 通道分离&通道运算
    vector<Mat> channels;
    split(img, channels); // 分离BGR三通道
    // 示例：对蓝色通道（channels[0]）做亮度提升
    channels[0] += 50;
    merge(channels, img); // 合并通道


    // 3. 灰度图&二值化
    Mat gray, binary;
    cvtColor(img, gray, COLOR_BGR2GRAY); // 转灰度图
    threshold(gray, binary, 127, 255, THRESH_BINARY); // 二值化（127为阈值）


    // 4. 腐蚀&膨胀（形态学操作）
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3)); // 3x3矩形结构元素
    Mat erode_img, dilate_img;
    erode(binary, erode_img, kernel); // 腐蚀
    dilate(binary, dilate_img, kernel); // 膨胀


    // 5. 寻找&绘制轮廓
    vector<vector<Point>> contours;
    findContours(binary, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); // 找外轮廓
    drawContours(img_copy, contours, -1, Scalar(0, 255, 0), 2); // 绘制所有轮廓（绿色，线宽2）


    // 6. 拟合多边形（以第一个轮廓为例）
    if (!contours.empty()) {
        vector<Point> approx;
        approxPolyDP(contours[0], approx, arcLength(contours[0], true)*0.02, true); // 多边形拟合
        polylines(img_copy, approx, true, Scalar(255, 0, 0), 2); // 绘制拟合多边形（蓝色）
    }


    // 7. 矩形&旋转矩形
    if (!contours.empty()) {
        Rect rect = boundingRect(contours[0]); // 外接矩形
        rectangle(img_copy, rect, Scalar(0, 0, 255), 2); // 绘制矩形（红色）

        RotatedRect rrect = minAreaRect(contours[0]); // 最小旋转矩形
        Point2f pts[4];
        rrect.points(pts);
        for (int i=0; i<4; i++) {
            line(img_copy, pts[i], pts[(i+1)%4], Scalar(255, 255, 0), 2); // 绘制旋转矩形（青色）
        }
    }


    // 8. 绘制常见边框（点、线、三角形）
    circle(img_copy, Point(50, 50), 3, Scalar(255, 0, 255), -1); // 绘制点（紫色实心圆）
    line(img_copy, Point(100, 100), Point(200, 200), Scalar(0, 255, 255), 2); // 绘制线（黄色）
    Point triangle_pts[] = {Point(300, 100), Point(250, 200), Point(350, 200)};
    fillPoly(img_copy, std::vector<std::vector<Point>>{{Point(300, 100), Point(250, 200), Point(350, 200)}}, Scalar(128, 128, 128)); // 绘制三角形（灰色填充）


    // 显示结果
    imshow("Result", img_copy);
    waitKey(0);
    destroyAllWindows();
    return 0;
}