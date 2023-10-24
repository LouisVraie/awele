#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <iostream>
#include "Color.h"

using namespace std;

namespace Game
{
  class Player
  {
  private:
    string name;
    int score;
    int nbMoves;

    int chosen;

    int lastHoleIndex;

    vector<int> allowedHoles;

  public:
    Player();
    Player(const Player &player);

    void show();

    void setName(string name);
    string getName();

    void setScore(int score);
    int getScore();
    void addScore(int score);

    void setNbMoves(int nbMoves);
    int getNbMoves();

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
