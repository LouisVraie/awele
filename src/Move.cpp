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
  this->awele = new Awele(*(awele));
  this->hole = hole;
  this->color = color;
  this->isTransparent = isTransparent;
}

/**
 * @brief Copy an instance
 */
Move::Move(const Move &move)
{
  this->awele = new Awele(*(move.awele));
  this->hole = move.hole;
  this->color = move.color;
  this->isTransparent = move.isTransparent;
}

/**
 * @brief Destructor
 */
Move::~Move()
{
  if (this->awele->getIsCopied())
  {
    delete this->awele;
  }
}

/**
 * @brief Show Move info
 */
void Move::showMove()
{
  cout << this->getNextMove();
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
 * @brief Get the best next move
 * @return String representing the move
 */
string Move::getNextMove()
{
  return to_string(this->hole + 1) + (this->isTransparent ? "T" : "") + getLetterFromColor(this->color);
}

/**
 * @brief Set a random input for the given player
 */
void Move::setRandomMove(Player *player)
{
  // Get a random hole allowed for the player
  int holeIndex = rand() % (this->awele->getRule()->getNbHoles() / 2);
  int hole = player->getAllowedHoles()[holeIndex];

  // Get a random isTransparent
  bool isTransparent = rand() % 1;

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
string Move::randomMove(Player *player)
{
  this->setRandomMove(player);

  return this->getNextMove();
}

/**
 * @brief Ask the player to enter a move
 */
void Move::askMove(Player *player)
{
  string input;
  Color chosenColor = Color::Default;
  bool chosenIsTransparent;
  int chosenHole;

  bool endAskCondition = true;

  do
  {
    chosenIsTransparent = false;

    if (this->awele->getRule()->getDebug())
    {
      cout << player->getName() << " Choose your move : ";
    }

    // Ask input following the player
    // if (player == this->awele->getPlayer1())
    // {
    //   getline(cin, input);
    // }
    // else
    // {
    //   input = this->randomMove(player);
    //   cout << input << endl;
    // }
    getline(cin, input);

    try
    {
      int inputLength = input.length();
      // Cut the number and the string
      if (inputLength >= 2)
      {
        // Put the string toupper
        transform(input.begin(), input.end(), input.begin(), ::toupper);

        string lastTwoChars = input.substr(inputLength - 2);

        if (lastTwoChars[0] == 'T')
        {
          chosenIsTransparent = true;
          chosenHole = stoi(input.substr(0, inputLength - 2));
        }
        else
        {
          chosenHole = stoi(input.substr(0, inputLength - 1));
        }
        // get the chosen color
        chosenColor = getColorFromLetter(lastTwoChars[1]);

        chosenHole--;

        if (endAskCondition = !this->isMovePossible(player, chosenHole, chosenColor, chosenIsTransparent))
        {
          if (this->awele->getRule()->getDebug())
          {
            cout << player->getName() << " Invalid move. Please enter a valid move." << endl;
          }
        }
      }
    }
    catch (const exception &)
    {
      chosenHole = -1;
      if (this->awele->getRule()->getDebug())
      {
        cout << player->getName() << " Invalid input. Please enter a valid move.." << endl;
      }
    }

  } while (endAskCondition);

  // Increment the number of move of the current player
  player->setNbMoves(player->getNbMoves() + 1);

  // Set the chosen move infos
  this->setHole(chosenHole);
  this->setColor(chosenColor);
  this->setIsTransparent(chosenIsTransparent);
}

/**
 * @brief Perform the move chosen by the player
 */
void Move::makeMove(Player *player)
{
  // if blue
  if (this->getColor() == Color::Blue)
  {
    this->moveBlue(player);
  }
  // if red
  if (this->getColor() == Color::Red)
  {
    this->moveRed(player);
  }
}

/**
 * @brief Perform a blue move
 */
void Move::moveBlue(Player *player)
{
  int nbSeeds;
  int targetHole = 0;

  // get opponent holes
  vector<int> opponentHoles = this->awele->getOpponentHoles(player);

  // if transparent
  if (this->getIsTransparent())
  {
    color = Color::Transparent;
  }
  else
  {
    color = Color::Blue;
  }

  // get seeds of the chosen hole
  nbSeeds = this->awele->getHoles()[this->getHole()]->getNbSeedsByColor(color);

  // foreach seed
  for (int i = 0; i < nbSeeds; i++)
  {
    int chosenHole = this->getHole() % 2 == 1 ? this->getHole() + 1 : this->getHole();

    int targetHoleIndex = (chosenHole / 2 + i) % opponentHoles.size();
    targetHole = opponentHoles[targetHoleIndex];

    // We add the seed to the new hole
    this->awele->getHoles()[targetHole]->addSeed(1, color);

    // We remove the seed of the origin hole
    this->awele->getHoles()[this->getHole()]->removeSeed(1, color);
  }

  player->setLastHoleIndex(targetHole);
}

/**
 * @brief Perform a red move
 */
void Move::moveRed(Player *player)
{
  int nbSeeds;
  int targetHole = this->getHole();
  int i = 0;
  Color color;

  // if transparent
  if (this->getIsTransparent())
  {
    color = Color::Transparent;
  }
  else
  {
    color = Color::Red;
  }

  // get seeds of the chosen hole
  nbSeeds = this->awele->getHoles()[this->getHole()]->getNbSeedsByColor(color);

  // while the hole got seeds
  while (this->awele->getHoles()[this->getHole()]->getNbSeedsByColor(color) != 0)
  {
    targetHole = (targetHole + 1) % this->awele->getRule()->getNbHoles();

    // we skip the chosen hole if the player did more than one turn of the board
    if (targetHole != this->getHole())
    {
      // Check if i is a valid index for seeds
      if (i < nbSeeds)
      {
        // We add the seed to the new hole
        this->awele->getHoles()[targetHole]->addSeed(1, color);

        // We remove the seed of the origin hole
        this->awele->getHoles()[this->getHole()]->removeSeed(1, color);

        i++;
      }
      else
      {
        break;
      }
    }
  }

  player->setLastHoleIndex(targetHole);
}

/**
 * @brief Check if the given move is possible for the given player
 * @return
 */
bool Move::isMovePossible(Player *player, int chosenHole, Color chosenColor, bool chosenIsTransparent)
{
  if (chosenIsTransparent)
  {
    chosenColor = Color::Transparent;
  }

  return chosenColor != Color::Default && this->awele->getHoles()[chosenHole]->getNbSeedsByColor(chosenColor) > 0 && chosenHole >= 0 && chosenHole <= this->awele->getRule()->getNbHoles() - 1 && player->isHoleAllowed(chosenHole);
}

/**
 * @brief Get all the possible moves from the current position for the current player
 * @return A vector of Moves
 */
vector<Move> Move::getPossibleMoves(Player *player)
{
  vector<Move> possibleMoves;

  vector<int> allowedHoles = player->getAllowedHoles();

  // for each allowedHoles
  for (int index : allowedHoles)
  {
    // try blue
    if (this->isMovePossible(player, index, Color::Blue, false))
    {
      possibleMoves.push_back(Move(this->awele, index, Color::Blue, false));
    }

    // try red
    if (this->isMovePossible(player, index, Color::Red, false))
    {
      possibleMoves.push_back(Move(this->awele, index, Color::Red, false));
    }

    // try transparent blue
    if (this->isMovePossible(player, index, Color::Blue, true))
    {
      possibleMoves.push_back(Move(this->awele, index, Color::Blue, true));
    }

    // try transparent red
    if (this->isMovePossible(player, index, Color::Red, true))
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
int Move::evaluate(Player *player)
{
  // if it is the first turn
  if (this->awele->getTurn() == 1)
  {
    return rand() % numeric_limits<int>::max();
  }
  else
  {
    // check how many points the move can give

    // Make a copy of move to perform the move without affecting the real board
    Move *move = new Move(*this);
    Player *copiedPlayer;

    if (player == this->awele->getPlayer1())
    {
      copiedPlayer = this->awele->getPlayer1();
    }
    else
    {
      copiedPlayer = this->awele->getPlayer2();
    }

    // Perform the move
    move->makeMove(copiedPlayer);
    // Do the scoring
    move->awele->scoreAfterMove(copiedPlayer);

    int player1NewScore = move->awele->getPlayer1()->getScore();
    int player2NewScore = move->awele->getPlayer2()->getScore();

    int player1OldScore = this->awele->getPlayer1()->getScore();
    int player2OldScore = this->awele->getPlayer2()->getScore();

    // if the player1 gain points
    if (player1NewScore > player1OldScore)
    {
      return player1NewScore - player1OldScore;
    }
    // if the player2 gain points
    if (player2NewScore > player2OldScore)
    {
      return -(player2NewScore - player2OldScore);
    }

    // If nothing as changed
    return 0;
  }
}

void Move::decisionAlphaBeta(Player *player, int depth)
{
  // Get starting time
  auto startTime = high_resolution_clock::now();

  // Decide the best move to play for J in the position currentPos
  int val, alpha = -numeric_limits<int>::max();
  int beta = numeric_limits<int>::max();
  vector<Move> possibleMoves = this->getPossibleMoves(player);

  for (Move move : possibleMoves)
  {
    val = this->alphaBetaValue(player, alpha, beta, false, depth);
    if (val > alpha)
    {
      this->hole = move.getHole();
      this->color = move.getColor();
      this->isTransparent = move.getIsTransparent();

      alpha = val;
    }
  }

  // Get ending time
  auto endTime = high_resolution_clock::now();

  auto duration = duration_cast<milliseconds>(endTime - startTime);

  cout << "AlphaBeta execution time : " << duration.count() << "ms" << endl;
  cout << player->getName() << " Best next move : " << this->getNextMove() << endl;
}

int Move::alphaBetaValue(Player *player, int alpha, int beta, bool isMax, int depth)
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
    return this->evaluate(player);
  }

  vector<Move> possibleMoves = this->getPossibleMoves(player);

  // Max
  if (isMax)
  {
    for (Move childMove : possibleMoves)
    {
      alpha = max(alpha, childMove.alphaBetaValue(this->awele->getOpponent(player), alpha, beta, !isMax, depth - 1));
      if (alpha >= beta)
      {
        return alpha; /* beta cut */
      }
    }
    return alpha;
  }

  // Min
  for (int i = 0; i < possibleMoves.size(); i++)
  {
    beta = min(beta, possibleMoves[i].alphaBetaValue(this->awele->getOpponent(player), alpha, beta, !isMax, depth - 1));
    if (beta <= alpha)
    {
      return beta; /* alpha cut */
    }
  }
  return beta;
}
