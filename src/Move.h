#ifndef MOVE_H
#define MOVE_H

#include <string>
#include <limits>
#include <chrono>
#include "Awele.h"

using namespace std;
using namespace chrono;

namespace Game
{
  class Move
  {
  private:
    Awele *awele;

    int hole;
    Color color;
    bool isTransparent;

  public:
    Move(Awele *awele);
    Move(Awele *awele, int hole, Color color, bool isTransparent);

    void showMove();
    void showMoves(vector<Move> moves);

    void setHole(int hole);
    int getHole();
    void setColor(Color color);
    Color getColor();
    void setIsTransparent(bool isTransparent);
    bool getIsTransparent();

    string getNextMove();

    void setRandomMove(Player *player);
    string randomMove(Player *player);
    void askMove(Player *player);
    void makeMove(Player *player);
    void moveBlue(Player *player);
    void moveRed(Player *player);
    bool isMovePossible(Player *player, int chosenMove, Color chosenColor, bool chosenIsTransparent);

    vector<Move> getPossibleMoves(Move currentPos, Player *player);

    int evaluate(Player *player);
    void decisionAlphaBeta(Move currentPos, Player *player, int pmax);
    int alphaBetaValue(Move currentPos, Player *player, int alpha, int beta, bool isMax, int pmax);
  };
}

#endif
