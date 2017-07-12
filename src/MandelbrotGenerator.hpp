#include <complex>

#define HORIZON 2.0
#define MAX_ITERATIONS 1000
#define STEP 50

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
    void generateSet(std::string *);
};
