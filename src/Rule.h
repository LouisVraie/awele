#ifndef RULE_H
#define RULE_H

#include <vector>

using namespace std;

namespace Game
{
  class Rule
  {
  private:
    int nbHoles;

    int nbBlueSeeds;
    int nbRedSeeds;
    int nbTransparentSeeds;

    int winCondition;
    int drawCondition;
    int endCondition;
    bool starving;

    vector<int> eatWhenNbSeeds;

  public:
    Rule();

    void setNbHoles(int nbHoles);
    int getNbHoles();

    void setNbBlueSeeds(int nbBlueSeeds);
    int getNbBlueSeeds();
    void setNbRedSeeds(int nbRedSeeds);
    int getNbRedSeeds();
    void setNbTransparentSeeds(int nbTransparentSeeds);
    int getNbTransparentSeeds();

    void setWinCondition(int winCondition);
    int getWinCondition();
    void setDrawCondition(int drawCondition);
    int getDrawCondition();
    void setEndCondition(int endCondition);
    int getEndCondition();
    void setStarving(bool starving);
    bool getStarving();

    void setEatWhenNbSeeds(vector<int> eatWhenNbSeeds);
    vector<int> getEatWhenNbSeeds();
  };
}

#endif
