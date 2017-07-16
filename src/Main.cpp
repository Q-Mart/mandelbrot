#include "Main.hpp"

int main()
{
  auto gen = MandelbrotGenerator();
  gen.generateSet();

  std::cout << gen;

  auto iw = ImageWriter();
  return iw.writeSet(gen.set);
}
