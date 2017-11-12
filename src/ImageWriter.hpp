#include "opencv2/highgui/highgui.hpp"
#include "Common.hpp"

#define BLACK cv::Scalar(0,0,0)
#define WHITE cv::Scalar(65536,65536,65536)

class ImageWriter
{
  std::string filename = "mandelbrot";
  cv::Mat img = cv::Mat(STEP, STEP, CV_16UC3, BLACK);
  
  public:
    ImageWriter();
    ImageWriter(std::string);
    int writeSet(std::vector<std::vector<int>> &set);
};
