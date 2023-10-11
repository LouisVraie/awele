#ifndef HOLE_H
#define HOLE_H

#include <vector>
#include <iostream>
#include "Seed.h"

using namespace std;

namespace Game
{
  class Hole
  {
  private:
    vector<Seed *> seeds;

  public:
    Hole(int nbBlueSeeds, int nbRedSeeds, int nbTransparentSeeds);
    int getNbSeeds();
    int getNbSeedsByColor(Color color);
    void show();
  };
}

#endif
