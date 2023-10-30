#include "Move.h"

using namespace Game;

/**
 * @brief Constructor
 */
Move::Move()
{
}

/**
 * @brief Constructor
 */
Move::Move(int hole, Color color, bool isTransparent)
{
  this->hole = hole;
  this->color = color;
  this->isTransparent = isTransparent;
}

/**
 * @brief Copy an instance
 */
Move::Move(const Move &move)
{
  this->hole = move.hole;
  this->color = move.color;
  this->isTransparent = move.isTransparent;
}

/**
 * @brief Destructor
 */
Move::~Move()
{
}

/**
 * @brief Show Move info
 */
void Move::showMove()
{
  cout << this->getString();
}

/**
 * @brief Show Moves infos
 */
void Move::showMoves(vector<Move> moves)
{
  for (Move move : moves)
  {
    move.showMove();
    cout << " | ";
  }
  cout << endl;
}

void Move::setHole(int hole)
{
  this->hole = hole;
}
int Move::getHole()
{
  return this->hole;
}

void Move::setColor(Color color)
{
  this->color = color;
}
Color Move::getColor()
{
  return this->color;
}

void Move::setIsTransparent(bool isTransparent)
{
  this->isTransparent = isTransparent;
}
bool Move::getIsTransparent()
{
  return this->isTransparent;
}

/**
 * @brief Get the move
 * @return String representing the move
 */
string Move::getString()
{
  return to_string(this->hole + 1) + (this->isTransparent ? "T" : "") + getLetterFromColor(this->color);
}

/**
 * @brief Set a random input for the given player
 */
void Move::setRandomMove(Player *player, Rule *rule)
{
  // Get a random hole allowed for the player
  int holeIndex = rand() % (rule->getNbHoles() / 2);
  int hole = player->getAllowedHoles()[holeIndex];

  // Get a random isTransparent
  bool isTransparent = rand() % 2;

  // Get a random color
  Color color;

  int randColor = rand() % 2 + 1;

  switch (randColor)
  {
  case 1:
    color = Color::Blue;
    break;
  case 2:
    color = Color::Red;
    break;
  default:
    color = Color::Default;
  }

  // Set all the result values
  this->setHole(hole);
  this->setColor(color);
  this->setIsTransparent(isTransparent);
}

/**
 * @brief Get a random input for the given player
 * @return The string representing the move
 */
string Move::randomMove(Player *player, Rule *rule)
{
  Move move;
  move.setRandomMove(player, rule);

  return move.getString();
}