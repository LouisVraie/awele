#include "Move.h"

using namespace Game;

/**
 * @brief Constructor
 */
Move::Move(Awele *awele)
{
  this->awele = awele;
}

/**
 * @brief Constructor
 */
Move::Move(Awele *awele, int hole, Color color, bool isTransparent)
{
  this->awele = awele;
  this->hole = hole;
  this->color = color;
  this->isTransparent = isTransparent;
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
 * @return The best next move for the player
 */
string Move::getNextMove()
{
  return "";
}

/**
 * @brief Get all the possible moves from the current position for the current player
 * @return A vector of Moves
 */
vector<Move> Move::getPossibleMoves(Move currentPos, Player *player)
{
  vector<Move> possibleMoves;

  vector<int> allowedHoles = player->getAllowedHoles();

  // for each allowedHoles
  for(int index : allowedHoles)
  {
    // try blue
    if(this->awele->isMovePossible(player, index, Color::Blue, false))
    {
      possibleMoves.push_back(Move(this->awele, index, Color::Blue, false));
    }

    // try red
    if(this->awele->isMovePossible(player, index, Color::Red, false))
    {
      possibleMoves.push_back(Move(this->awele, index, Color::Red, false));
    }

    // try transparent blue
    if(this->awele->isMovePossible(player, index, Color::Blue, true))
    {
      possibleMoves.push_back(Move(this->awele, index, Color::Blue, true));
    }

    // try transparent red
    if(this->awele->isMovePossible(player, index, Color::Red, true))
    {
      possibleMoves.push_back(Move(this->awele, index, Color::Red, true));
    }
  }

  return possibleMoves;
}

/**
 * @brief Evaluate a move position
 * @return An integer which symbolize the move result
 */
int Move::evaluate(Move position)
{
  return 0;
}

void Move::decisionAlphaBeta(Move currentPos, Player *player, int depth)
{
  // Decide the best move to play for J in the position currentPos
  int alpha = -this->maxValue;
  int beta = this->maxValue;
  for (Move move : getPossibleMoves(currentPos, player))
  {
    int val = alphaBetaValue(move, player, alpha, beta, false, depth);
    if (val > alpha)
    {
      this->hole = move.getHole();
      this->color = move.getColor();
      this->isTransparent = move.getIsTransparent();

      alpha = val;
    }
  }
}

int Move::alphaBetaValue(Move currentPos, Player *player, int alpha, int beta, bool isMax, int depth)
{
  // Compute the value currentPos for the player J depending on currentPos.depth is the maximal depth
  // if (isWinningPosition(currentPos, player))
  // {
  //   return this->maxValue;
  // }
  // if (isLoosingPosition(currentPos, player))
  // {
  //   return (-this->maxValue);
  // }
  // if (isDrawPosition(currentPos, player))
  // {
  //   return 0;
  // }
  if (depth == 0)
  {
    return evaluate(currentPos);
  }

  // Max
  if (isMax)
  {
    for (Move childMove : getPossibleMoves(currentPos, player))
    {
      alpha = max(alpha, alphaBetaValue(childMove, this->awele->getOpponent(player), alpha, beta, !isMax, depth - 1));
      if (alpha >= beta)
      {
        return alpha; /* beta cut */
      }
    }
    return alpha;
  }

  // Min
  for (Move childMove : getPossibleMoves(currentPos, player))
  {
    beta = min(beta, alphaBetaValue(childMove, this->awele->getOpponent(player), alpha, beta, !isMax, depth - 1));
    if (beta <= alpha)
    {
      return beta; /* alpha cut */
    }
  }
  return beta;
}
