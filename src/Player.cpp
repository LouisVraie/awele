#include "Player.h"

using namespace Game;

/**
 * Constructor
*/
Player::Player()
{
  this->score = 0;
}

void Player::setScore(int score)
{
  this->score = score;
}
int Player::getScore()
{
  return this->score;
}