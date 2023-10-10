#ifndef CASE_H
#define CASE_H

#include <vector>
#include "Seed.h"

using namespace std;

namespace Game
{
  class Case
  {
  private:
    vector<Seed *> seeds;

  public:
    Case();
  };
}

#endif
