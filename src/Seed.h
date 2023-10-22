#ifndef SEED_H
#define SEED_H

#include "Color.h"

using namespace std;

namespace Game
{
  class Seed
  {
  private:
    Color color;

  public:
    Seed(Color color);
    Seed(const Seed &seed);

    Color getColor();
  };
}

#endif
