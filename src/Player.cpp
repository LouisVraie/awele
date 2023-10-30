#include "Player.h"

using namespace Game;

/**
 * @brief Constructor
 */
Player::Player()
{
  this->score = 0;
  this->nbMoves = 0;
}

/**
 * @brief Copy an instance
 */
Player::Player(const Player &player)
{
  this->name = player.name;
  this->score = player.score;
  this->nbMoves = player.nbMoves;

  this->chosen = player.chosen;

  this->lastHoleIndex = player.lastHoleIndex;

  this->allowedHoles = player.allowedHoles;
}

/**
 * @brief Print player infos
 */
void Player::show()
{
  cout << "[" << this->name << "] ";
  cout << "Score : " << this->score;
  cout << endl;
}

void Player::setName(string name)
{
  this->name = name;
}
string Player::getName()
{
  return "[" + this->name + "]";
}

void Player::setScore(int score)
{
  this->score = score;
}
int Player::getScore()
{
  return this->score;
}
void Player::addScore(int score)
{
  this->score += score;
}

void Player::setNbMoves(int nbMoves)
{
  this->nbMoves = nbMoves;
}
int Player::getNbMoves()
{
  return this->nbMoves;
}

void Player::setNextMove(vector<Move> moves)
{
  this->moves = moves;
}
vector<Move> Player::getNextMove()
{
  return this->moves;
}

void Player::setChosen(bool chosen)
{
  this->chosen = chosen;
}
bool Player::getChosen()
{
  return this->chosen;
}

void Player::setLastHoleIndex(int lastHoleIndex)
{
  this->lastHoleIndex = lastHoleIndex;
}
int Player::getLastHoleIndex()
{
  return this->lastHoleIndex;
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