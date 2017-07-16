#include <complex>
#include <vector>

#define HORIZON 2.0
#define MAX_ITERATIONS 1000
#define STEP 1000

class MandelbrotGenerator
{
  double xMin;
  double xMax;
  double yMin;
  double yMax;

  bool inMandelbrot(double, double);

  public:
    MandelbrotGenerator(double, double, double, double);
    MandelbrotGenerator();
    std::vector<std::vector<bool>> generateSet();
};
