#include "MandelbrotGenerator.hpp"
#include "ThreadPool.hpp"
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


int MandelbrotGenerator::calcColour(float x, float y)
{
  std::complex<float> c (x, y);
  std::complex<float> z = c;

  for (int iterationNumber = 0; iterationNumber < MAX_ITERATIONS; iterationNumber++)
  {
    if (std::abs(z) > HORIZON)
    {
      //we are not in the Mandelbrot set
      return iterationNumber;
    }
    z = (z*z) + c;
  }
  return 0;
}


void MandelbrotGenerator::generateSet()
{
  ThreadPool pool(NUM_THREADS);
  float xStep = (this->xMax - this->xMin)/STEP;
  float yStep = (this->yMax - this->yMin)/STEP;

  int xCount = 0;
  int yCount = 0;
  for (float x = this->xMin; x < this->xMax; x=x+xStep)
  {
    yCount = 0;
    for (float y = this->yMin; y < this->yMax; y=y+yStep)
    {
      pool.enque( [this, xCount, yCount, x, y] {
        this->set[yCount][xCount] = calcColour(x,y);
      });
      yCount++;
    }
    xCount++;
  }
}
