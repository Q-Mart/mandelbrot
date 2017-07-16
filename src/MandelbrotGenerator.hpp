#include <complex>
#include <vector>
#include "Common.hpp"

#define HORIZON 2.0
#define MAX_ITERATIONS 1000

class MandelbrotGenerator
{
  float xMin;
  float xMax;
  float yMin;
  float yMax;

  int iterationNumber=0;

  bool inMandelbrot(float, float);

  public:
    std::vector<std::vector<int>> set;

    MandelbrotGenerator(float, float, float, float);
    MandelbrotGenerator();
    void generateSet();
};

std::ostream& operator<<(std::ostream&, const MandelbrotGenerator&);
