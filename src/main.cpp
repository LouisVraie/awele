#include "Awele.h"

using namespace Game;
using namespace std;

int main()
{
  cout << "Awele Start" << endl;

  srand(time(NULL));
  Rule rule;
  GameStatus gameStatus;

  rule.setNbHoles(16);

  rule.setNbBlueSeeds(2);
  rule.setNbRedSeeds(2);
  rule.setNbTransparentSeeds(1);

  rule.setWinCondition(41);
  rule.setDrawCondition(40);
  rule.setEndCondition(10);

  rule.setStarving(true);

  rule.setDebug(true);

  rule.setEatWhenNbSeeds({2, 3});

  Awele awele = Awele(&rule);

  do
  {
    awele.play();
    gameStatus = awele.checkGameStatus();
  } while (gameStatus == GameStatus::InProgress);

  cout << "<> Game finished !!!" << endl;
  cout << "<> GameStatus : " << gameStatus << endl;
  cout << "<> Seeds on board : " << awele.getSeedsLeft() << endl;
  awele.show();
  cout << "Awele End" << endl;

  return 0;
}