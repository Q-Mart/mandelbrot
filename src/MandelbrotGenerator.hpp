#include <complex>
#include <vector>
#include "Common.hpp"

#define HORIZON 2.0
#define MAX_ITERATIONS 1000

class MandelbrotGenerator
{
  double xMin;
  double xMax;
  double yMin;
  double yMax;

  bool inMandelbrot(double, double);

  public:
    std::vector<std::vector<bool>> set;

    MandelbrotGenerator(double, double, double, double);
    MandelbrotGenerator();
    void generateSet();
};

std::ostream& operator<<(std::ostream&, const MandelbrotGenerator&);
