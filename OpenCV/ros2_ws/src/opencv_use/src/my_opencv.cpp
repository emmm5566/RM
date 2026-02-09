#include <cstdio>
#include <opencv2/opencv.hpp>
using namespace cv;

int main(int argc, char ** argv)
{
  (void) argc;
  (void) argv;

  Mat scr = imread("/home/emmm/Desktop/scnu_rm/OpenCV/images/test01.jpg");
  imshow("scr", scr);
  waitKey(0);

  printf("hello world opencv_use package\n");
  return 0;
}
