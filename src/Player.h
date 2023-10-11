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
    int chosenHole;
    Color chosenColor;
    bool chosenIsTransparent;

    vector<int> allowedHoles;

  public:
    Player();

    void setName(string name);
    string getName();

    void setScore(int score);
    int getScore();

    void setNbMoves(int nbMoves);
    int getNbMoves();

    void setChosenHole(int chosenHole);
    int getChosenHole();
    void setChosenColor(char chosenColor);
    Color getChosenColor();
    void setChosenIsTransparent(bool chosenIsTransparent);
    bool getChosenIsTransparent();

    void setAllowedHoles(vector<int> allowedHoles);
    vector<int> getAllowedHoles();
    bool isHoleAllowed(int hole);
  };
}

#endif
