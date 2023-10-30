#ifndef MOVE_H
#define MOVE_H

#include <string>
#include <vector>
#include "Color.h"
// #include "Player.h"
#include "Rule.h"

using namespace std;

namespace Game
{
  class Move
  {
  private:
    int hole;
    Color color;
    bool isTransparent;

  public:
    Move();
    Move(int hole, Color color, bool isTransparent);
    Move(const Move &move);
    ~Move();

    void showMove();
    void showMoves(vector<Move> moves);

    void setHole(int hole);
    int getHole();
    void setColor(Color color);
    Color getColor();
    void setIsTransparent(bool isTransparent);
    bool getIsTransparent();

    string getString();
  };
}

#endif
