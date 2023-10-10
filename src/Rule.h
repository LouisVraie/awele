#ifndef RULE_H
#define RULE_H

#include <vector>

using namespace std;

namespace Game
{
  class Rule
  {
  private:
    int nbCases;

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

    void SetNbCases(int nbCases);
    int GetNbCases();

    void SetNbBlueSeeds(int nbBlueSeeds);
    int GetNbBlueSeeds();
    void SetNbRedSeeds(int nbRedSeeds);
    int GetNbRedSeeds();
    void SetNbTransparentSeeds(int nbTransparentSeeds);
    int GetNbTransparentSeeds();

    void SetWinCondition(int winCondition);
    int GetWinCondition();
    void SetDrawCondition(int drawCondition);
    int GetDrawCondition();
    void SetEndCondition(int endCondition);
    int GetEndCondition();
    void SetStarving(bool starving);
    bool GetStarving();

    void SetEatWhenNbSeeds(vector<int> eatWhenNbSeeds);
    vector<int> GetEatWhenNbSeeds();
  };
}

#endif
