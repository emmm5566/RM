#include <opencv2/opencv.hpp>

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
        cv::Mat frame;
        cap >> frame;
        if(frame.empty())
        {
            break;
        }

        //预处理
        cv::Mat channels[3];
        cv::Mat binary, Gaussian;
        int Threshold = 220;
        int MaxVal = 255;
        cv::Size GaussianBlurKernel = cv::Size(5,5);
        cv::split(frame, channels);
        cv::threshold(channels[2], binary, Threshold, MaxVal, 0);
        cv::GaussianBlur(binary, Gaussian, GaussianBlurKernel, 0);

        //轮廓检测
        std::vector< std::vector <cv::Point> > contours;
        std::vector< cv::Vec4i > hierarchy;
        cv::findContours(Gaussian, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

        //最小外接矩形
        std::vector< cv::Point2f > vertices(4);
        for(size_t i=0; i<contours.size(); i++)
        {
            double area = contourArea(contours[i]);
            if(area < 50.0) continue;

            cv::RotatedRect minRect = cv::minAreaRect(contours[i]);
            minRect.points(vertices.data());

            //灯条筛选：最小外接矩形的长宽比
            float width = minRect.size.width;
            float height = minRect.size.height;
            if(width == 0 || height == 0) continue; //防止除零
            float aspectRatio = std::max(width, height) / std::min(width, height);
            if(aspectRatio >= 1.3 && std::max(height, width)>36)
            {
                //绘制最小外接矩形
                for(int j=0; j<4; j++)
                {
                    line(frame, vertices[j], vertices[(j+1)%4], cv::Scalar(0,255,0), 2);
                }
            }
        }

        cv::imshow("Frame", frame);
        if(cv::waitKey(30) == 27)
        {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}