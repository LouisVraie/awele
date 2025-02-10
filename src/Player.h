#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <iostream>
#include "Move.h"

using namespace std;

namespace Game
{
  class Player
  {
  private:

    int id;
    string name;
    int score;
    Move nextMove;

    bool chosen;
    int lastHoleIndex;
    vector<int> allowedHoles;

  public:
    Player(int id, string name);
    Player(const Player &player);
    ~Player();

    void show();

    void setId(int id);
    int getId();

    void setName(string name);
    string getName();

    void setScore(int score);
    int getScore();
    void addScore(int score);

    void setNextMove(Move nextMove);
    Move getNextMove();

    void setChosen(bool chosen);
    bool getChosen();

    void setLastHoleIndex(int lastHoleIndex);
    int getLastHoleIndex();

    void setAllowedHoles(vector<int> allowedHoles);
    vector<int> getAllowedHoles();
    bool isHoleAllowed(int hole);
  };
}

#endif
