#include "Main.hpp"

int main()
{
  std::string str;
  MandelbrotGenerator gen = MandelbrotGenerator();
  gen.generateSet(&str);
  std::cout << str;

  //create an image ( 3 channels, 16 bit image depth, 650 high, 600 wide, (0, 50000, 50000) assigned for Blue, Green and Red plane respectively. )
  cv::Mat img(650, 600, CV_16UC3, cv::Scalar(0,50000, 50000));

  //check whether image has loaded
  if (img.empty())
  {
    std::cout << "ERROR: Cannot load image!" << '\n';
    return -1;
  }

  //vector that stores compression params for image
  std::vector<int> compression_params;
  compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
  compression_params.push_back(98);

  bool success = cv::imwrite("mandelbrot.jpg", img, compression_params);

  if (!success)
  {
    std::cout << "ERROR: Failed to save image!" << '\n';
    return -1;
  }

  return 0;
}
