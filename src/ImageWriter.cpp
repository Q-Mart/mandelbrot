#include "ImageWriter.hpp"

ImageWriter::ImageWriter() {} ;
ImageWriter::ImageWriter(std::string filename)
{
  this->filename = filename;
}

int ImageWriter::writeSet(std::vector<std::vector<int>> &set)
{
  if (img.empty())
  {
    std::cerr << "ERROR: Cannot load image!" << '\n';
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
      if (set[y][x] > 0)
      {
        img.col(x).row(y) = cv::Scalar(0,0,set[y][x]);
      }
    }
  }

  bool success = cv::imwrite("mandelbrot.jpg", img, compression_params);

  if (!success)
  {
    std::cerr << "ERROR: Failed to save image!" << '\n';
    return -1;
  }
  return 0;
}
