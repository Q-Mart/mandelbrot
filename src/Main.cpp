#include "Main.hpp"

int main()
{
  std::string str;
  MandelbrotGenerator gen = MandelbrotGenerator();
  gen.generateSet(&str);
  std::cout << str;
  return 0;
}
