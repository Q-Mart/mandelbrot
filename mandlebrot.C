#include <iostream>
#include <complex>
#include "mandlebrot.H"

bool inMandleBrot(double x, double y)
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


int main()
{
  double x = -2.0;
  double y = -1.25;

  double xStep = (0.5-x)/50;
  double yStep = (1.25-y)/50;

  for (x; x < 0.5; x=x+xStep)
  {
    for (y; y < 1.25; y=y+yStep)
    {
      /* std::cout << "x: " << x << " y: " << y << '\n'; */
      if (inMandleBrot(x, y))
      {
        /* std::cout << "x: " << x << " y: " << y << '\n'; */
        std::cout << '.';
      }
      std::cout << ' ';
    }
    std::cout << '\n';
    y = -1.25;
  }

  return 0;
}
