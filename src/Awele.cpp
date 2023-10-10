#include "Awele.h"

using namespace Game;

/**
 * Constructor
*/
Awele::Awele(Rule rule)
{
  this->rule = &rule;
}

int Awele::getSeedsLeft()
{
  int result = 0;

  for (int i = 0; i < cases.size(); i++)
  {
    result += this.cases[i].getNbSeeds();
  }
  
  return result;
}

/**
 * Check all endgame conditions
 */
bool Awele::isGameFinished()
{
  // if player1 won
  if(this->player1->getScore() >= this->rule->getWinCondition())
  {
    return true;
  }

  // if player2 won
  if(this->player2->getScore() >= this->rule->getWinCondition())
  {
    return true;
  }

  // if draw
  if(this->player2->getScore() == this->rule->getDrawCondition() && this->player2->getScore() == this->rule->getDrawCondition())
  {
    return true;
  }

  // if endCondition
  if(this->getSeedsLeft() <= this->rule->getEndCondition())
  {
    return true;
  }


  return false;
}