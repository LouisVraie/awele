#ifndef AWELE_H
#define AWELE_H

#include <vector>
#include <string>
#include "Player.h"
#include "Seed.h"
#include "Case.h"
#include "Rule.h"

using namespace std;

namespace Game
{
  class Awele
  {
  private:
    Player *player1;
    Player *player2;

    vector<Case *> cases;
    int turn;

  public:
    Awele(Rule rule);
  };
}

#endif
