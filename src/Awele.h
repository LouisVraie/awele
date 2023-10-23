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
    Player1Won = 1,
    Player2Won = 2,
    Draw = 3,
  };

  class Awele
  {
  private:
    Rule *rule;

    Player *player1;
    Player *player2;

    vector<Hole *> holes;
    int turn;

    bool isCopied;

  public:
    Awele(Rule *rule);
    Awele(const Awele &awele);
    ~Awele();

    Rule *getRule();
    Player *getPlayer1();
    Player *getPlayer2();
    vector<Hole *> getHoles();
    int getTurn();
    bool getIsCopied();

    void play();
    void show();
    void scoreAfterMove(Player *player);
    void checkStarving(Player *player);
    int getSeedsLeft();
    int getSeedsLeft(Player *player);
    int getHolesPartWithSeeds();
    int getDynamicDepth(Player *player);
    Player *getOpponent(Player *player);
    vector<int> getOpponentHoles(Player *player);
    GameStatus checkGameStatus();
  };
}

#endif
