#include "Awele.h"

using namespace Game;

/**
 * Constructor
 */
Awele::Awele(Rule *rule)
{
  this->rule = rule;

  // Creation of all cases
  for (int iCase = 0; iCase < this->rule->getNbCases(); iCase++)
  {
    Case *hole = new Case();
    this->cases.push_back(hole);
  }
  
}

/**
 * @return The numbers of seeds left on the board
 */
int Awele::getSeedsLeft()
{
  int result = 0;

  for (int i = 0; i < this->cases.size(); i++)
  {
    result += this->cases[i]->getNbSeeds();
  }

  return result;
}

/**
 * Check all endgame conditions
 * @return GameStatus of the game
 */
GameStatus Awele::checkGameStatus()
{
  int result = GameStatus::InProgress;

  // if player1 won
  if (this->player1->getScore() >= this->rule->getWinCondition())
  {
    return GameStatus::Player1Win;
  }

  // if player2 won
  if (this->player2->getScore() >= this->rule->getWinCondition())
  {
    return GameStatus::Player2Win;
  }

  // if draw
  if (this->player2->getScore() == this->rule->getDrawCondition() && this->player2->getScore() == this->rule->getDrawCondition())
  {
    return GameStatus::Draw;
  }

  // if endCondition
  if (this->getSeedsLeft() <= this->rule->getEndCondition())
  {
    return GameStatus::End;
  }

  return GameStatus::InProgress;
}