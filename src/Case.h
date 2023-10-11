#ifndef CASE_H
#define CASE_H

#include <vector>
#include <iostream>
#include "Seed.h"

using namespace std;

namespace Game
{
  class Case 
  {
  private:
    vector<Seed *> seeds;

  public:
    Case(int nbBlueSeeds, int nbRedSeeds, int nbTransparentSeeds);
    int getNbSeeds();
    int getNbSeedsByColor(Color color);
    void show();
  };
}

#endif
