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
    Player1WinByScore = 1,
    Player1WinByStarving = 2,
    Player2WinByScore = 3,
    Player2WinByStarving = 4,
    Draw = 5,
    End = 6,
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
    string randomMove(Player *player);
    void askMove(Player *player);
    void makeMove(Player *player);
    void moveBlue(Player *player);
    void moveRed(Player *player);
    void scoreAfterMove(Player *player);
    bool isMovePossible(Player *player, int chosenMove, Color chosenColor, bool chosenIsTransparent);
    int getSeedsLeft();
    int getSeedsLeft(Player *player);
    vector<int> getOpponentHoles(Player *player);
    GameStatus checkGameStatus();
  };
}

#endif
