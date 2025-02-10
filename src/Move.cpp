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