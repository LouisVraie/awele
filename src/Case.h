#ifndef CASE_H
#define CASE_H

#include <vector>
#include "Rule.h"
#include "Seed.h"

using namespace std;

namespace Game
{
  class Case : public Rule
  {
  private:
    vector<Seed *> seeds;

  public:
    Case();
    int getNbSeeds();
  };
}

#endif
