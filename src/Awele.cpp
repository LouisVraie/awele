#include "Awele.h"

using namespace Game;

/**
 * Constructor
 */
Awele::Awele(Rule *rule)
{
  // Set rules
  this->rule = rule;

  // Players initialization
  this->player1 = new Player();
  this->player2 = new Player();

  this->player1->setName("Player1");
  this->player2->setName("Player2");

  vector<int> player1Holes, player2Holes;

  for (int i = 0; i < this->rule->getNbHoles(); i++)
  {
    if(i%2 == 0)
    {
      // Assigning odd holes
      player1Holes.push_back(i);
    } else {
      // Assigning even holes
      player2Holes.push_back(i);
    }
  }
  
  this->player1->setAllowedHoles(player1Holes);
  this->player2->setAllowedHoles(player2Holes);

  this->turn = 0;

  // Creation of all holes
  for (int iHole = 0; iHole < this->rule->getNbHoles(); iHole++)
  {
    Hole *hole = new Hole(this->rule->getNbBlueSeeds(), this->rule->getNbRedSeeds(), this->rule->getNbTransparentSeeds());
    this->holes.push_back(hole);
  }
}

/**
 * @brief Run the game
 */
void Awele::play()
{
  // Adding a new turn
  this->turn++;

  // Show the board
  this->show();

  // Ask the player to play
  if(turn%2 == 1)
  {
    this->askMove(this->player1);
  } else {
    this->askMove(this->player2);
  }

  // Make the move

}

/**
 * @brief Print the game board
 */
void Awele::show()
{
  for (int i = 0; i < this->rule->getNbHoles(); i++)
  {
    if (i == this->rule->getNbHoles() / 2)
    {
      cout << endl;
    }
    this->holes[i]->show();
  }
  cout << endl;
}

/**
 * @brief Ask the player to enter a move
 */
void Awele::askMove(Player *player)
{
  string input;
  int move;

  do
  {
    cout << player->getName() <<" Choose your move : ";
    cin >> input;

    try
    {
      move = stoi(input);
      move--;
      
      if (!this->isMovePossible(player, move))
      {
        cout  << player->getName() << " Invalid move. Please enter a valid move." << endl;
      }
    }
    catch (const exception &)
    {
      move = -1;
      cout << player->getName() << " Invalid input. Please enter a valid move." << endl;
    }

  } while (!this->isMovePossible(player, move));

  // Increment the number of move of the current player
  player->setNbMoves(player->getNbMoves() + 1);
}

/**
 * @brief Check if the given move is possible for the given player
 * @return
*/
bool Awele::isMovePossible(Player * player, int move)
{
  return move >= 0 && move < this->rule->getNbHoles()-1 && player->isHoleAllowed(move);
}

/**
 * @return The numbers of seeds left on the board
 */
int Awele::getSeedsLeft()
{
  int result = 0;

  for (int i = 0; i < this->holes.size(); i++)
  {
    result += this->holes[i]->getNbSeeds();
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
