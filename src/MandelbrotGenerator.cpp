#include "MandelbrotGenerator.hpp"

MandelbrotGenerator::MandelbrotGenerator(double xMin, double xMax, double yMin, double yMax)
{
  this->xMin = xMin;
  this->xMax = xMax;
  this->yMin = yMin;
  this->yMax = yMax;
}

MandelbrotGenerator::MandelbrotGenerator()
{
  xMin = -2.0;
  xMax = 0.5;
  yMin = -1.25;
  yMax = 1.25;
}


bool MandelbrotGenerator::inMandelbrot(double x, double y)
{
  std::complex<double> c (x, y);
  std::complex<double> z = c;

  for (int n = 0; n < MAX_ITERATIONS; n++)
  {
    if (std::abs(z) > HORIZON)
    {
      return false;
    }
    z = (z*z) + c;
  }
  return true;
}


void MandelbrotGenerator::generateSet(std::string *str)
{
  double xStep = (this->xMax - this->xMin)/STEP;
  double yStep = (this->yMax - this->yMin)/STEP;

  for (double x = this->xMin; x < this->xMax; x=x+xStep)
  {
    for (double y = this->yMin; y < this->yMax; y=y+yStep)
    {
      if (inMandelbrot(x, y))
      {
        str->append(".");
      }
        str->append(" ");
    }
    str->append("\n");
  }
}
