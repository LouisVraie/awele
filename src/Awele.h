#ifndef AWELE_H
#define AWELE_H

#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
#include "Seed.h"
#include "Case.h"
#include "Rule.h"

using namespace std;

namespace Game
{
  enum GameStatus
  {
    InProgress = 0,
    Player1Win = 1,
    Player2Win = 2,
    Draw = 3,
    End = 4,
  };

  class Awele
  {
  private:
    Rule *rule;

    Player *player1;
    Player *player2;

    vector<Case *> cases;
    int turn;

  public:
    Awele(Rule *rule);
    void show();
    void askMove();
    int getSeedsLeft();
    GameStatus checkGameStatus();
  };
}

#endif
