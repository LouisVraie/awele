#ifndef AWELE_H
#define AWELE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <limits>
#include <chrono>
#include <cmath>
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
    const int maxValue = numeric_limits<int>::max();

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

    bool isWinningMove();
    bool isLoosingMove();
    bool isDrawMove();

    Awele *copyAndMove(Move childMove);
    int evaluate(Awele *awele);
    int evaluate2(Awele *awele, int initialDepth);
    void decisionAlphaBeta(Player *player, int depth);
    void decisionMinimax(Player *player, int depth);
    void decisionChess(Player *player, int depth);
    tuple<int, Move> alphaBetaValue(Awele *awele, int alpha, int beta, bool isMax, int depth, int initialDepth);
    tuple<int, Move> minimaxValue(Awele *awele, bool isMax, int depth, int initialDepth);
    tuple<int, Move> chessValue(Awele *awele, int depth, int initialDepth);
  };
}

#endif
