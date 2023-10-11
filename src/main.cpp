#include "Awele.h"

using namespace Game;
using namespace std;

int main()
{
  cout << "Awele Start" << endl;

  Rule rule;

  rule.setNbHoles(16);

  rule.setNbBlueSeeds(2);
  rule.setNbRedSeeds(2);
  rule.setNbTransparentSeeds(1);

  rule.setWinCondition(41);
  rule.setDrawCondition(40);
  rule.setEndCondition(10);

  rule.setStarving(true);

  rule.setEatWhenNbSeeds({2,3});
  
  Awele awele = Awele(&rule);

  do
  {
    awele.play();
  } while (awele.checkGameStatus() == GameStatus::InProgress);
  
  cout << "Awele End" << endl;

  return 0;
}