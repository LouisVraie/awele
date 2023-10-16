#ifndef AWELE_H
#define AWELE_H

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include "Player.h"
#include "Seed.h"
#include "Hole.h"
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

    vector<Hole *> holes;
    int turn;

  public:
    Awele(Rule *rule);
    void play();
    void show();
    void askMove(Player *player);
    void makeMove(Player *player);
    void moveBlue(Player *player);
    void moveRed(Player *player);
    bool isMovePossible(Player *player, int chosenMove, Color chosenColor, bool chosenIsTransparent);
    int getSeedsLeft();
    vector<int> getOpponentHoles(Player *player);
    GameStatus checkGameStatus();
  };
}

#endif
