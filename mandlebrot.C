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
  double x = 0;
  double y = 0;

  for (x; x < 100000; x++)
  {
    for (y; y < 100000; y++)
    {
      if (inMandleBrot(x, y))
      {
        std::cout << "x: " << x << " y: " << y << '\n';
      }
    }
  }

  return 0;
}
