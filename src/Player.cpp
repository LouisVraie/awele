#include "Player.h"

using namespace Game;

/**
 * Constructor
 */
Player::Player()
{
  this->score = 0;
  this->nbMoves = 0;
}

void Player::setName(string name)
{
  this->name = name;
}
string Player::getName()
{
return "["+this->name+"]";
}

void Player::setScore(int score)
{
  this->score = score;
}
int Player::getScore()
{
  return this->score;
}

void Player::setNbMoves(int nbMoves)
{
  this->nbMoves = nbMoves;
}
int Player::getNbMoves()
{
  return this->nbMoves;
}

void Player::setAllowedHoles(vector<int> allowedHoles)
{
  this->allowedHoles = allowedHoles;
}
vector<int> Player::getAllowedHoles()
{
  return this->allowedHoles;
}
/**
 * @brief Check if the given hole is allowed for the player
 * @return
 */
bool Player::isHoleAllowed(int hole)
{
  for (int i = 0; i < this->allowedHoles.size(); i++)
  {
    if (hole == this->allowedHoles[i])
    {
      return true;
    }
  }
  return false;
}