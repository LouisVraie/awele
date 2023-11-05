#include "Player.h"

using namespace Game;

/**
 * @brief Constructor
 */
Player::Player(int id, string name)
{
  this->id = id;
  this->name = name;
  this->score = 0;
}

/**
 * @brief Copy an instance
 */
Player::Player(const Player &player)
{
  this->id = player.id;
  this->name = player.name;
  this->score = player.score;

  this->chosen = player.chosen;

  this->lastHoleIndex = player.lastHoleIndex;

  this->allowedHoles = player.allowedHoles;
}

/**
 * @brief Destructor
 */
Player::~Player()
{
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

void Player::setNextMove(Move nextMove)
{
  this->nextMove = nextMove;
}
Move Player::getNextMove()
{
  return this->nextMove;
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