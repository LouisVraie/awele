#ifndef MOVE_H
#define MOVE_H

#include <string>
#include <limits>
#include "Awele.h"

using namespace std;

namespace Game
{
  class Move
  {
  private:
    const int maxValue = numeric_limits<int>::infinity();

    Awele *awele;

    int hole;
    Color color;
    bool isTransparent;

  public:
    Move(Awele *awele);
    Move(Awele *awele, int hole, Color color, bool isTransparent);

    void setHole(int hole);
    int getHole();
    void setColor(Color color);
    Color getColor();
    void setIsTransparent(bool isTransparent);
    bool getIsTransparent();

    string getNextMove();

    string randomMove(Player *player);
    void askMove(Player *player);
    void makeMove(Player *player);
    void moveBlue(Player *player);
    void moveRed(Player *player);
    bool isMovePossible(Player *player, int chosenMove, Color chosenColor, bool chosenIsTransparent);

    vector<Move> getPossibleMoves(Move currentPos, Player *player);

    int evaluate(Move position);
    void decisionAlphaBeta(Move currentPos, Player *player, int pmax);
    int alphaBetaValue(Move currentPos, Player *player, int alpha, int beta, bool isMax, int pmax);
  };
}

#endif
