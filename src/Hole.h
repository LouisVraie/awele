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
    Hole(const Hole &hole);

    int getNbSeeds();
    int getNbSeedsByColor(Color color);
    vector<Seed *> getSeedsByColor(Color color);
    void addSeed(Seed *seed);
    void removeSeed(Seed *seed);
    void removeAllSeeds();
    void show();
  };
}

#endif
