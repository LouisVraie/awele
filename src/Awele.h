#ifndef AWELE_H
#define AWELE_H

#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <limits>
#include <chrono>
#include "Player.h"
#include "Hole.h"
#include "Rule.h"
#include "Move.h"

using namespace std;
using namespace chrono;

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
    int currentPlayerId;

    vector<Hole *> holes;
    int turn;

    bool isCopied;

  public:
    Awele(Rule *rule);
    Awele(const Awele &awele);
    ~Awele();

    void choosePlayer();

    Rule *getRule();
    Player *getPlayer1();
    Player *getPlayer2();
    vector<Hole *> getHoles();
    int getTurn();
    bool getIsCopied();

    void play();
    void show();
    void performMove();
    void scoreAfterMove(Player *player);
    void checkStarving(Player *player);
    int getSeedsLeft();
    int getSeedsLeft(Player *player);
    int getHolesPartWithSeeds();
    int getDynamicDepth(Player *player);
    void nextPlayer();
    Player *getCurrentPlayer();
    Player *getOpponent(Player *player);
    vector<int> getOpponentHoles(Player *player);

    bool isMovePossible(Player *player, int chosenMove, Color chosenColor, bool chosenIsTransparent);
    vector<Move> getPossibleMoves(Player *player);

    void askMove(Player *player);
    void makeMove(Player *player);
    void moveBlue(Player *player);
    void moveRed(Player *player);

    GameStatus checkGameStatus();

    Move getRandomMove(Player *player);

    int evaluate(Player *player);
    void decisionAlphaBeta(Player *player, int pmax);
    tuple<int, Move> alphaBetaValue(Awele *awele, int alpha, int beta, bool isMax, int pmax);
  };
}

#endif
