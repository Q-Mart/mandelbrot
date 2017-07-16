#include "Main.hpp"

int main()
{
  MandelbrotGenerator gen = MandelbrotGenerator();
  auto set = gen.generateSet();

  for (auto row : set)
  {
    for (bool element: row)
    {
      element ? std::cout << '.' : std::cout << ' ';
    }
    std::cout << '\n';
  }

  //create an image ( 3 channels, 16 bit image depth, 650 high, 600 wide, (0, 50000, 50000) assigned for Blue, Green and Red plane respectively. )
  cv::Mat img(1000, 1000, CV_16UC3, BLACK);

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

  for (int y=0; y<1000; y++)
  {
    for (int x=0; x<1000; x++)
    {
      if (set[y][x] == true)
      {
        img.col(x).row(y) = WHITE;
      }
    }
  }

  bool success = cv::imwrite("mandelbrot.jpg", img, compression_params);

  if (!success)
  {
    std::cout << "ERROR: Failed to save image!" << '\n';
    return -1;
  }

  return 0;
}
