#include "Main.hpp"

std::vector<float> parseArgs(int argc, char *argv[])
{
  std::vector<float> result;
  if (argc < 4)
  {
    return result;
  }

  for (int i=0; i<4; i++)
  {
    result.push_back(atof(argv[i]));
  }

  return result;
}

int main(int argc, char *argv[])
{
  auto args = parseArgs(argc, argv);

  auto gen = args.empty() ?
    MandelbrotGenerator() :
    MandelbrotGenerator(args[0], args[1], args[2], args[3]);

  gen.generateSet();

  std::cout << gen;

  auto iw = ImageWriter();
  return iw.writeSet(gen.set);
}
