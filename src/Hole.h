#ifndef HOLE_H
#define HOLE_H

#include <vector>
#include <iostream>
#include "Color.h"

using namespace std;

namespace Game
{
  class Hole
  {
  private:
    int nbBlueSeeds;
    int nbRedSeeds;
    int nbTransparentSeeds;

  public:
    Hole(int nbBlueSeeds, int nbRedSeeds, int nbTransparentSeeds);
    Hole(const Hole &hole);
    ~Hole();

    int getNbSeeds();
    int getNbSeedsByColor(Color color);
    void addSeed(int nbSeeds, Color color);
    void removeSeed(int nbSeeds, Color color);
    void removeAllSeeds();
    void show();
  };
}

#endif
