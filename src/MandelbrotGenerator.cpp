#include "MandelbrotGenerator.hpp"
#include <iostream>

MandelbrotGenerator::MandelbrotGenerator(float xMin, float xMax, float yMin, float yMax)
{
  set = std::vector<std::vector<int>> (STEP, std::vector<int> (STEP, 0));
  this->xMin = xMin;
  this->xMax = xMax;
  this->yMin = yMin;
  this->yMax = yMax;
}

MandelbrotGenerator::MandelbrotGenerator()
{ 
  set = std::vector<std::vector<int>> (STEP, std::vector<int> (STEP, false));
  xMin = -2.0;
  xMax = 0.5;
  yMin = -1.25;
  yMax = 1.25;
}

std::ostream& operator<<(std::ostream& strm, const MandelbrotGenerator& gen)
{
  for (auto row : gen.set)
  {
    for (int element: row)
    {
      element  == 0 ? strm << '.' : strm << ' ';
    }
    strm << '\n';
  }
  return strm;
}


bool MandelbrotGenerator::inMandelbrot(float x, float y)
{
  std::complex<float> c (x, y);
  std::complex<float> z = c;

  for (iterationNumber = 0; iterationNumber < MAX_ITERATIONS; iterationNumber++)
  {
    if (std::abs(z) > HORIZON)
    {
      return false;
    }
    z = (z*z) + c;
  }
  return true;
}


void MandelbrotGenerator::generateSet()
{
  float xStep = (this->xMax - this->xMin)/STEP;
  float yStep = (this->yMax - this->yMin)/STEP;

  int xCount = 0;
  int yCount = 0;
  for (float x = this->xMin; x < this->xMax; x=x+xStep)
  {
    yCount = 0;
    for (float y = this->yMin; y < this->yMax; y=y+yStep)
    {
      if (!inMandelbrot(x, y))
      {
        this->set[yCount][xCount] = iterationNumber;
      }
      yCount++;
    }
    xCount++;
  }
}
