#ifndef PLAYER_H
#define PLAYER_H

#include <string>

using namespace std;

namespace Game
{
  class Player
  {
  private:
    int score;

  public:
    Player();

    void setScore(int score);
    int getScore();
  };
}

#endif
