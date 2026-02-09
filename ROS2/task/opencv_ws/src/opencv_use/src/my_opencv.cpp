#include <cstdio>
#include <opencv2/opencv.hpp>
using namespace cv;

int main(int argc, char ** argv)
{
  (void) argc;
  (void) argv;

  Mat img = imread("./img/test.jpg");
  if (img.empty()) {
    printf("could not read the image\n");
    return -1;
  }

  resize(img, img, Size(), 0.5, 0.5);
  imshow("display window", img);
  waitKey(0);

  printf("hello world opencv_use package\n");

  return 0;
}



//ros2 pkg create opencv_use --build-type ament_cmake --dependencies rclcpp OpenCV sensor_msgs cv_bridge image_transport --node-name my_opencv