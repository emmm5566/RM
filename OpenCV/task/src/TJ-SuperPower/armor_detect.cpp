#include <opencv2/opencv.hpp>

class tools
{
public:
    //绘制轮廓点
    static void draw_points(cv::Mat& img, const std::vector<cv::Point> & contour_points)
    {
        for(const auto & point : contour_points)
        {
            cv::circle(img, point, 3, cv::Scalar(0,255,255), -1);
        }
    }

    //绘制外接矩形
    static void draw_points(cv::Mat& img, const std::vector<cv::Point2f> & rect_vertices)
    {
        for(int i=0; i<4; i++)
        {
            cv::Point ver1 = cv::Point((int)rect_vertices[i].x, (int)rect_vertices[i].y);
            cv::Point ver2 = cv::Point((int)rect_vertices[(i+1)%4].x, (int)rect_vertices[(i+1)%4].y);
            cv::line(img, ver1, ver2, cv::Scalar(0,255,0), 5);
        }
    }

};

// class Detector
// {
// public:
//     std::list<Armor> detect(const cv::Mat & bgr_img); //输入图片得到装甲板

// private:
//     bool check_geometry(const lightbar & lightbar);
//     bool check_geometry(const Armor & armor);
//     bool check_name(const Armor & armor);

//     Color get_color(const cv::Mat & bgr_img, const std::vector<cv::Point> & contour);
//     cv::Mat get_pattern(const cv::Mat & bgr_img, const Armor & armor);

//     void classify(Arrmor & Arrmor);
// }

int main()
{
    cv::VideoCapture cap("/home/emmm/Desktop/scnu_rm/OpenCV/task/img/task2_video.mp4");
    if(!cap.isOpened())
    {
        std::cout << "Error opening video stream or file" << std::endl;
        return -1;
    }

    while(true)
    {
        cv::Mat bgr_img;
        cap >> bgr_img;
        if(bgr_img.empty())
        {
            return 0;
        }

        //预处理
        //彩色图像转灰度图
        cv::Mat gray_img, binary_img;
        cv::cvtColor(bgr_img, gray_img, cv::COLOR_BGR2GRAY);
        // cv::resize(gray_img, gray_img, {}, 0.5, 0.5);
        // cv::imshow("gray_img", gray_img);
        // cv::resize(gray_img, gray_img, {}, 2, 2);
        //二值化
        cv::threshold(gray_img, binary_img, 200, 255, cv::THRESH_BINARY);
        // cv::resize(binary_img, binary_img, {}, 0.5, 0.5);
        // cv::imshow("binary_img", binary_img);
        // cv::resize(binary_img, binary_img, {}, 2, 2);

        //获取轮廓点
        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(binary_img, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);

        // //（调式）显示轮廓点
        // cv::Mat drawcontours = bgr_img.clone();
        // for(const auto & contour : contours)
        // {
        //     tools::draw_points(drawcontours, contour); 
        // }
        // cv::resize(drawcontours, drawcontours, {}, 0.5, 0.5);
        // cv::imshow("drawcontours", drawcontours);

        //最小外接矩形
        //获取旋转矩形并显示
        std::vector<cv::RotatedRect> rotated_rects;
        for(const auto & contour : contours)
        {
            auto rotated_rect = cv::minAreaRect(contour);
            rotated_rects.emplace_back(rotated_rect);
        }
        cv::Mat drawrect = bgr_img.clone();
        for(const auto & rotated_rect : rotated_rects)
        {
            std::vector<cv::Point2f> points(4);
            rotated_rect.points(&points[0]);
            tools::draw_points(drawrect, points); 
        }
        cv::resize(drawrect, drawrect, {}, 0.5, 0.5);
        cv::imshow("drawrect", drawrect);

        cv::imshow("Frame", bgr_img);
        if(cv::waitKey(100) == 27)
        {
            break;
        }
    }

    return 0;
}





//Mat img2 = img1 浅拷贝
//Mat img2 = img1.clone() 深拷贝