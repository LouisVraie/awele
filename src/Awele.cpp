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
    Case *hole = new Case(this->rule->getNbBlueSeeds(), this->rule->getNbRedSeeds(), this->rule->getNbTransparentSeeds());
    this->cases.push_back(hole);
  }
}

/**
 * @brief Print the game board
 */
void Awele::show()
{
  for (int i = 0; i < this->rule->getNbCases(); i++)
  {
    if (i == this->rule->getNbCases() / 2)
    {
      cout << endl;
    }
    this->cases[i]->show();
  }
  cout << endl;
}

/**
 * @brief Ask the player to enter a move
 */
void Awele::askMove()
{
  string position;
  int choice;

  do
  {
    cout << "Choose your move (1 - " << this->rule->getNbCases() << "): ";
    cin >> position;

    try
    {
      choice = stoi(position);
      if (choice < 1 || choice > this->rule->getNbCases())
      {
        cout << "Invalid input. Please enter a number between 1 and " << this->rule->getNbCases() << endl;
      }
    }
    catch (const invalid_argument &)
    {
      cout << "Invalid input. Please enter a valid number." << endl;
    }

  } while (choice < 1 || choice > this->rule->getNbCases());
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
