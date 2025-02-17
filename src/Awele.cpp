#include "Awele.h"

using namespace Game;

/**
 * @brief Constructor
 */
Awele::Awele(Rule *rule)
{
  // Set rules
  this->rule = rule;

  // Players initialization
  this->player1 = new Player(1, "Player1");
  this->player2 = new Player(2, "Player2");

  this->currentPlayerId = 1;

  // Choose a player
  this->choosePlayer();

  vector<int> player1Holes, player2Holes;

  for (int i = 0; i < this->rule->getNbHoles(); i++)
  {
    if (i % 2 == 0)
    {
      // Assigning odd holes
      player1Holes.push_back(i);
    }
    else
    {
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

  this->isCopied = false;
}

/**
 * @brief Copy an instance
 */
Awele::Awele(const Awele &awele)
{
  this->rule = awele.rule;

  this->player1 = new Player(*(awele.player1));
  this->player2 = new Player(*(awele.player2));

  this->currentPlayerId = awele.currentPlayerId;

  // Make a copy of Holes
  for (Hole *hole : awele.holes)
  {
    Hole *clonedHole = new Hole(*hole);
    this->holes.push_back(clonedHole);
  }

  this->turn = awele.turn;

  this->isCopied = true;
}

/**
 * @brief Destructor
 */
Awele::~Awele()
{
  delete this->player1;
  delete this->player2;

  for (Hole *hole : this->holes)
  {
    delete hole;
  }
}

/**
 * @brief Ask to choose a player
 */
void Awele::choosePlayer()
{
  string input;
  do
  {
    cout << "Choose your players [1] or [2] : ";

    getline(cin, input);
    if (input == "1")
    {
      this->player1->setChosen(true);
      this->player2->setChosen(false);

      cout << this->player1->getName() << " has been chosen." << endl;
    }
    else if (input == "2")
    {
      this->player1->setChosen(false);
      this->player2->setChosen(true);

      cout << this->player2->getName() << " has been chosen." << endl;
    }
    else
    {
      cout << "You must chose one of the given players [1] or [2] !" << endl;
    }
  } while (input != "1" && input != "2");
}

/**
 * @brief Get Awele rules
 * @return A Rule pointer
 */
Rule *Awele::getRule()
{
  return this->rule;
}

/**
 * @brief Get Player1
 * @return The player1 pointer
 */
Player *Awele::getPlayer1()
{
  return this->player1;
}

/**
 * @brief Get Player2
 * @return The player2 pointer
 */
Player *Awele::getPlayer2()
{
  return this->player2;
}

/**
 * @brief Get Awele holes
 * @return A vector of Hole pointers
 */
vector<Hole *> Awele::getHoles()
{
  return this->holes;
}

/**
 * @brief Get Awele turn
 * @return An integer of turn
 */
int Awele::getTurn()
{
  return this->turn;
}

/**
 * @brief Get Awele isCopied property
 * @return A bool to know if it's a copy or not
 */
bool Awele::getIsCopied()
{
  return this->isCopied;
}

/**
 * @brief Run the game
 */
void Awele::play()
{
  Player *currentPlayer = this->getCurrentPlayer();

  // Adding a new turn
  this->turn++;

  // Show the board
  this->show();

  // Get corresponding depth
  int depth = this->getDynamicDepth(currentPlayer);

  // If the currentPlayer is the chosen one
  if (currentPlayer->getChosen())
  {
    // Ask the player to play
    this->decisionAlgo("AlphaBeta", currentPlayer, depth);
  }

  this->askMove(currentPlayer);

  // Perform the chosen move
  this->performMove();

  // Swap to next player
  this->nextPlayer();
}

/**
 * @brief Print the game board
 */
void Awele::show()
{
  ConsoleColor consoleColor;
  cout << endl;
  cout << consoleColor.green << "[TURN " << this->turn << "]" << consoleColor.base << endl;
  this->player1->show();
  this->player2->show();
  cout << "Seeds left : " << this->getSeedsLeft() << endl;

  for (int i = 0; i < this->rule->getNbHoles() / 2; i++)
  {
    this->holes[i]->show();
    cout << " ";
  }
  cout << endl;
  for (int i = this->rule->getNbHoles() - 1; i >= this->rule->getNbHoles() / 2; i--)
  {
    this->holes[i]->show();
    cout << " ";
  }
  cout << endl;
}

/**
 * @brief Print the informations of the current function
*/
void Awele::showAlgoInfos(string function, int durationInMs, int depth, Player *player, int eval)
{
  cout << endl;
  cout << function <<" execution time : " << durationInMs << "ms";
  cout << " | Depth : " << depth;
  cout << " | Player : " << player->getName();
  cout << " | Eval : " << eval << endl;

  cout << player->getName() << " Best next move : " << player->getNextMove().getString() << endl;
}

/**
 * @brief Perform all the actions on a move
 */
void Awele::performMove()
{
  Player *currentPlayer = this->getCurrentPlayer();
  // Make the move
  this->makeMove(currentPlayer);

  // Update the score after the move
  this->scoreAfterMove(currentPlayer);

  // Check if the opponent is starved
  this->checkStarving(currentPlayer);
}

/**
 * @brief Update the board and the score after a player move
 */
void Awele::scoreAfterMove(Player *player)
{
  bool continueCheck;
  vector<int> scoringPossibility = this->rule->getEatWhenNbSeeds();
  int targetIndex, nbSeeds, increment = 0;

  do
  {
    continueCheck = false;
    targetIndex = (this->rule->getNbHoles() + player->getLastHoleIndex() - increment) % this->rule->getNbHoles();

    // foreach scoringPossibility
    for (int i = 0; i < scoringPossibility.size(); i++)
    {
      nbSeeds = this->holes[targetIndex]->getNbSeeds();

      // if we got the same amount of seeds
      if (scoringPossibility[i] == nbSeeds)
      {
        continueCheck = true;
        player->addScore(nbSeeds);

        this->holes[targetIndex]->removeAllSeeds();
      }
    }

    increment++;

  } while (continueCheck);
}

/**
 * @brief Check if there is starving and add score to the given player
 */
void Awele::checkStarving(Player *player)
{
  if (this->rule->getStarving())
  {
    // Get the opponent player
    Player *opponent = this->getOpponent(player);

    // Get the number of seeds left of the opponent
    int opponentNbSeeds = this->getSeedsLeft(opponent);

    // If the opponent is starved
    if (opponentNbSeeds == 0)
    {
      // cout << opponent->getName() << " is starved !" << endl;

      // We give all the seeds left to the given player
      player->addScore(this->getSeedsLeft(player));

      // We remove all seeds from their holes
      for (int i = 0; i < this->rule->getNbHoles(); i++)
      {
        this->holes[i]->removeAllSeeds();
      }
    }
  }
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
 * @brief Get numbers of seeds left for the given player
 * @return
 */
int Awele::getSeedsLeft(Player *player)
{
  int result = 0;
  vector<int> allowedHoles = player->getAllowedHoles();

  for (int i = 0; i < allowedHoles.size(); i++)
  {
    result += this->holes[allowedHoles[i]]->getNbSeeds();
  }

  return result;
}

/**
 * @brief Get the numbers of holes part with seeds
 * @return An integer
 */
int Awele::getHolesPartWithSeeds()
{
  int result = 0;

  for (int i = 0; i < this->rule->getNbHoles(); i++)
  {
    if (this->holes[i]->getNbSeedsByColor(Color::Blue) > 0)
    {
      result++;
    }
    if (this->holes[i]->getNbSeedsByColor(Color::Red) > 0)
    {
      result++;
    }
    if (this->holes[i]->getNbSeedsByColor(Color::Transparent) > 0)
    {
      result++;
    }
  }

  return result;
}

/**
 * @brief Get the optimal depth for the current turn
 * @return An integer which represent the depth
 */
int Awele::getDynamicDepth(Player *player)
{
  if (this->turn <= 1)
  {
    return 1;
  }

  // Get the number of part of holes with seeds
  int holesPartWithSeeds = this->getHolesPartWithSeeds();

  // Get the number of seeds left
  int seedsLeft = this->getSeedsLeft();

  double ratio = ((double)holesPartWithSeeds / (double)seedsLeft) * 100;

  // double expRatio = exp(-1.5 * ratio);
  // return 10 * exp(-1.5 * ratio);

  if (ratio >= 40)
  {
    return 3;
  }

  if (ratio >= 20)
  {
    return 4;
  }

  if (ratio >= 15)
  {
    return 5;
  }

  return 6;
}

/**
 * @brief Swap to the next player
 */
void Awele::nextPlayer()
{
  this->currentPlayerId = (this->currentPlayerId == 1) ? 2 : 1;
}

/**
 * @brief Get the current player from the given player
 * @return The current player
 */
Player *Awele::getCurrentPlayer()
{
  if (this->currentPlayerId == 1)
  {
    return this->player1;
  }

  return this->player2;
}

/**
 * @brief Get the opponent player from the given player
 * @return The opponent player
 */
Player *Awele::getOpponent(Player *player)
{
  if (this->currentPlayerId == 1)
  {
    return this->player2;
  }

  return this->player1;
}

/**
 * @brief Get the opponent holes indexs
 * @return Pointer of the allowedHoles of the opponent player
 */
vector<int> Awele::getOpponentHoles(Player *player)
{
  return this->getOpponent(player)->getAllowedHoles();
}

/**
 * @brief Check if the given move is possible for the given player
 * @return
 */
bool Awele::isMovePossible(Player *player, int chosenHole, Color chosenColor, bool chosenIsTransparent)
{
  if (chosenIsTransparent)
  {
    chosenColor = Color::Transparent;
  }

  return chosenColor != Color::Default && this->getHoles()[chosenHole]->getNbSeedsByColor(chosenColor) > 0 && chosenHole >= 0 && chosenHole <= this->getRule()->getNbHoles() - 1 && player->isHoleAllowed(chosenHole);
}

/**
 * @brief Get all the possible moves from the current position for the current player
 * @return A vector of Moves
 */
vector<Move> Awele::getPossibleMoves(Player *player)
{
  vector<Move> possibleMoves;

  vector<int> allowedHoles = player->getAllowedHoles();

  // for each allowedHoles
  for (int index : allowedHoles)
  {
    // try blue
    if (this->isMovePossible(player, index, Color::Blue, false))
    {
      possibleMoves.push_back(Move(index, Color::Blue, false));
    }

    // try red
    if (this->isMovePossible(player, index, Color::Red, false))
    {
      possibleMoves.push_back(Move(index, Color::Red, false));
    }

    // try transparent blue
    if (this->isMovePossible(player, index, Color::Blue, true))
    {
      possibleMoves.push_back(Move(index, Color::Blue, true));
    }

    // try transparent red
    if (this->isMovePossible(player, index, Color::Red, true))
    {
      possibleMoves.push_back(Move(index, Color::Red, true));
    }
  }

  return possibleMoves;
}

/**
 * @brief Ask the player to enter a move
 */
void Awele::askMove(Player *player)
{
  string input;
  Color chosenColor = Color::Default;
  bool chosenIsTransparent;
  int chosenHole;
  int errorCounter = 0;
  bool endAskCondition = true;

  do
  {
    chosenIsTransparent = false;

    if (rule->getDebug())
    {
      cout << player->getName() << " Choose your move : ";
    }

    // Ask input following the player
    if (player->getChosen())
    {
      input = player->getNextMove().getString();
      // getline(cin, input);
    }
    else
    {
      // input = player->getNextMove().getString();
      // input = this->getRandomMove(player).getString();
      getline(cin, input);
    }

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
          if (rule->getDebug())
          {
            cout << player->getName() << " Invalid move. Please enter a valid move." << endl;
          }
          errorCounter++;
          if (errorCounter > 100)
          {
            exit(1);
          }
        }
      }
    }
    catch (const exception &)
    {
      chosenHole = -1;
      if (rule->getDebug())
      {
        cout << player->getName() << " Invalid input. Please enter a valid move.." << endl;
      }
    }

  } while (endAskCondition);

  cout << input << endl;

  // Set the chosen move infos for the player
  player->setNextMove(Move(chosenHole, chosenColor, chosenIsTransparent));
}

/**
 * @brief Perform the move chosen by the player
 */
void Awele::makeMove(Player *player)
{
  // if blue
  if (player->getNextMove().getColor() == Color::Blue)
  {
    this->moveBlue(player);
  }
  // if red
  if (player->getNextMove().getColor() == Color::Red)
  {
    this->moveRed(player);
  }
}

/**
 * @brief Perform a blue move
 */
void Awele::moveBlue(Player *player)
{
  int nbSeeds;
  int targetHole = 0;
  Color color;
  Move playerMove = player->getNextMove();

  // get opponent holes
  vector<int> opponentHoles = this->getOpponentHoles(player);

  // if transparent
  if (playerMove.getIsTransparent())
  {
    color = Color::Transparent;
  }
  else
  {
    color = Color::Blue;
  }

  // get seeds of the chosen hole
  nbSeeds = this->getHoles()[playerMove.getHole()]->getNbSeedsByColor(color);

  // foreach seed
  for (int i = 0; i < nbSeeds; i++)
  {
    int chosenHole = playerMove.getHole() % 2 == 1 ? playerMove.getHole() + 1 : playerMove.getHole();

    int targetHoleIndex = (chosenHole / 2 + i) % opponentHoles.size();
    targetHole = opponentHoles[targetHoleIndex];

    // We add the seed to the new hole
    this->getHoles()[targetHole]->addSeed(1, color);

    // We remove the seed of the origin hole
    this->getHoles()[playerMove.getHole()]->removeSeed(1, color);
  }

  player->setLastHoleIndex(targetHole);
}

/**
 * @brief Perform a red move
 */
void Awele::moveRed(Player *player)
{
  Move playerMove = player->getNextMove();
  int nbSeeds;
  int targetHole = playerMove.getHole();
  int i = 0;
  Color color;

  // if transparent
  if (playerMove.getIsTransparent())
  {
    color = Color::Transparent;
  }
  else
  {
    color = Color::Red;
  }

  // get seeds of the chosen hole
  nbSeeds = this->getHoles()[playerMove.getHole()]->getNbSeedsByColor(color);

  // while the hole got seeds
  while (this->getHoles()[playerMove.getHole()]->getNbSeedsByColor(color) != 0)
  {
    targetHole = (targetHole + 1) % this->getRule()->getNbHoles();

    // we skip the chosen hole if the player did more than one turn of the board
    if (targetHole != playerMove.getHole())
    {
      // Check if i is a valid index for seeds
      if (i < nbSeeds)
      {
        // We add the seed to the new hole
        this->getHoles()[targetHole]->addSeed(1, color);

        // We remove the seed of the origin hole
        this->getHoles()[playerMove.getHole()]->removeSeed(1, color);

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
 * Check all endgame conditions
 * @return GameStatus of the game
 */
GameStatus Awele::checkGameStatus()
{
  // if player1 won by score
  if (this->player1->getScore() >= this->rule->getWinCondition())
  {
    return GameStatus::Player1Won;
  }

  // if player2 won by score
  if (this->player2->getScore() >= this->rule->getWinCondition())
  {
    return GameStatus::Player2Won;
  }

  // if draw
  if (this->player1->getScore() == this->rule->getDrawCondition() && this->player2->getScore() == this->rule->getDrawCondition())
  {
    return GameStatus::Draw;
  }

  // if end
  if (this->getSeedsLeft() < this->rule->getEndCondition())
  {
    cout << "<> Less than " << this->rule->getEndCondition() << " seed(s) left on the board !" << endl;
    // if player1 won by score
    if (this->player1->getScore() > this->player2->getScore())
    {
      return GameStatus::Player1Won;
    }

    // if player2 won by score
    if (this->player2->getScore() > this->player1->getScore())
    {
      return GameStatus::Player2Won;
    }

    // if player1 and player2 got the same score
    if (this->player1->getScore() == this->player2->getScore())
    {
      return GameStatus::Draw;
    }
  }

  return GameStatus::InProgress;
}

/**
 * @brief Get a random move for the given player
 * @return A random Move
 */
Move Awele::getRandomMove(Player *player)
{
  // Get a random hole allowed for the player
  int holeIndex = rand() % (this->rule->getNbHoles() / 2);
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

  return Move(hole, color, isTransparent);
}

/**
 * @brief Check if it's a winning move for the chosen player
 * @return A boolean
 */
bool Awele::isWinningMove()
{
  Player *player = this->getCurrentPlayer();

  // if it's the chosen player and he will win
  return player->getChosen() && player->getScore() >= this->rule->getWinCondition();
}

/**
 * @brief Check if it's a loosing move for the chosen player
 * @return A boolean
 */
bool Awele::isLoosingMove()
{
  Player *player = this->getCurrentPlayer();

  // if it's the chosen player and the opponent win
  return player->getChosen() && this->getOpponent(player)->getScore() >= this->rule->getWinCondition();
}

/**
 * @brief Check if it's a draw move for the chosen player
 * @return A boolean
 */
bool Awele::isDrawMove()
{
  Player *player = this->getCurrentPlayer();

  // if it's the chosen player and the opponent win
  return player->getScore() == this->rule->getDrawCondition() && this->getOpponent(player)->getScore() == this->rule->getDrawCondition();
}

/**
 * @brief Make a copy from the given awele and perform the move
 * @return A copied Awele pointer of the given awele
 */
Awele *Awele::copyAndMove(Move childMove)
{
  Awele *aweleCopy = new Awele(*(this));
  aweleCopy->getCurrentPlayer()->setNextMove(childMove);
  aweleCopy->performMove();
  aweleCopy->nextPlayer();

  return aweleCopy;
}

/**
 * @brief Evaluate a move position
 * @return An integer which symbolize the move result
 */
int Awele::evaluate(Awele *awele)
{
  int colorWeight = 0;
  // if it is the first turn
  if (this->getTurn() <= 1)
  {
    return rand() % this->maxValue;
  }
  else
  {
    // check how many points the move can give

    Player *currentPlayer = awele->getCurrentPlayer();
    Player *opponentPlayer = awele->getOpponent(currentPlayer);

    Move playerMove = opponentPlayer->getNextMove();

    int currentPlayerNewScore = currentPlayer->getScore();
    int opponentPlayerNewScore = opponentPlayer->getScore();

    // Give the color weight
    Color currentColor = currentPlayer->getNextMove().getColor();
    bool currentIsTransparent = currentPlayer->getNextMove().getIsTransparent();

    // Blue
    if (currentColor == Color::Blue && !currentIsTransparent)
    {
      colorWeight = 1;
    }
    // Red
    else if (currentColor == Color::Red && !currentIsTransparent)
    {
      colorWeight = 5;
    }

    // Transparent Blue
    else if (currentColor == Color::Blue && currentIsTransparent)
    {
      colorWeight = 2;
    }
    // Transparent Red
    else if (currentColor == Color::Red && currentIsTransparent)
    {
      colorWeight = 4;
    }

    int nbSeeds = awele->getHoles()[playerMove.getHole()]->getNbSeeds();

    int nbSeedsWeight = nbSeeds * colorWeight;

    int result = 0;
    int deltaScore = 0;
    int deltaWeight = 50;

    deltaScore += (currentPlayerNewScore - opponentPlayerNewScore) * deltaWeight;

    result = (deltaScore) + nbSeedsWeight;

    return result;
  }
}

/**
 * @brief Evaluate a move position
 * @return An integer which symbolize the move result
 */
int Awele::evaluate2(Awele *awele, int initialDepth)
{
  int colorWeight = 0;
  // if it is the first turn
  if (this->getTurn() <= 1)
  {
    return rand() % this->maxValue;
  }
  else
  {
    // check how many points the move can give
    Player *oldCurrentPlayer = this->getCurrentPlayer(); 
    Player *oldOpponentPlayer = this->getOpponent(oldCurrentPlayer);
    Player *newCurrentPlayer;
    Player *newOpponentPlayer;

    // if the depth is even
    if(initialDepth % 2 == 0)
    {
      newCurrentPlayer = awele->getOpponent(awele->getCurrentPlayer());
      newOpponentPlayer = awele->getCurrentPlayer();
    } else 
    {
      newCurrentPlayer = awele->getCurrentPlayer();
      newOpponentPlayer = awele->getOpponent(awele->getCurrentPlayer());
    }

    int newCurrentPlayerHoleNbSeeds = 0;
    int newOpponentPlayerHoleNbSeeds = 0;

    int newCurrentPlayerTotalSeeds = 0;
    int newOpponentPlayerTotalSeeds = 0;

    int newCurrentPlayerNbPossibleHoles = 0;
    int newOpponentPlayerNbPossibleHoles = 0;

    int opponentNbNextMoves = awele->getPossibleMoves(newOpponentPlayer).size();

    // The sum of the 3 following variables must be equal to 100
    int scoreWeight = 50;
    int deltaScoreWeight = 10;
    int nbPossibleHolesWeight = 25;
    int totalSeedsWeight = 10;
    int nbNextMovesWeight = 5;

    // foreach hole of the given player
    for (int i : newCurrentPlayer->getAllowedHoles())
    {
      newCurrentPlayerHoleNbSeeds = awele->getHoles()[i]->getNbSeeds();
      newCurrentPlayerTotalSeeds += newCurrentPlayerHoleNbSeeds;

      // If they are seeds in this hole
      if (newCurrentPlayerHoleNbSeeds > 0)
      {
        // Adding 1 to the number of cases
        newCurrentPlayerNbPossibleHoles += 1;
      }
    }

    // foreach hole of the given player
    for (int i : newOpponentPlayer->getAllowedHoles())
    {
      newOpponentPlayerHoleNbSeeds = awele->getHoles()[i]->getNbSeeds();

      newOpponentPlayerTotalSeeds += newOpponentPlayerHoleNbSeeds;

      // If they are seeds in this hole
      if (newOpponentPlayerHoleNbSeeds > 0)
      {
        // Adding 1 to the number of cases
        newOpponentPlayerNbPossibleHoles += 1;
      }
    }
    
    return (((double)(((newCurrentPlayer->getScore()) - (newOpponentPlayer->getScore())) * scoreWeight) / 100) 
    + ((double)(((newCurrentPlayer->getScore() - oldCurrentPlayer->getScore()) - (newOpponentPlayer->getScore() - oldOpponentPlayer->getScore())) * deltaScoreWeight) / 100) 
    + ((double)((newCurrentPlayerNbPossibleHoles - newOpponentPlayerNbPossibleHoles) * nbPossibleHolesWeight) / 100)
    + ((double)((newCurrentPlayerTotalSeeds - newOpponentPlayerTotalSeeds) * totalSeedsWeight) / 100)
    + ((double)((32 - opponentNbNextMoves) * nbNextMovesWeight) / 100)
    ) * 10000;
  }
}

/**
 * @brief Obtain the best next move for the given player and the algorithm
 */
void Awele::decisionAlgo(string algoName, Player *player, int depth)
{
  // Get starting time
  auto startTime = high_resolution_clock::now();

  int val, alpha = -this->maxValue;
  int beta = this->maxValue;
  vector<Move> possibleMoves = this->getPossibleMoves(player);

  // Decide the best move to play for the player
  for (Move childMove : possibleMoves)
  {
    if (algoName == "AlphaBeta")
    {
      val = get<0>(this->alphaBetaValue(this->copyAndMove(childMove), alpha, beta, depth % 2 == 1, depth, depth));
    } 
    else if (algoName == "Minimax")
    {
      val = get<0>(this->minimaxValue(this->copyAndMove(childMove), depth % 2 == 1, depth, depth));
    }
    else if (algoName == "Chess")
    {
      val = get<0>(this->chessValue(this->copyAndMove(childMove), depth, depth));
    }
    else {
      cerr << "Algorithm : '" << algoName << "' was not found !" << endl;
      exit(1);
    }

    if(this->rule->getDebug())
    {
      cout << childMove.getString() << " : " << val << " | ";
    }

    if (val > alpha)
    {
      // We set the next move if it's a good one
      player->setNextMove(childMove);

      alpha = val;
    }
  }
  cout << endl;

  if (alpha == -this->maxValue)
  {
    player->setNextMove(possibleMoves[0]);
  }

  // Get duration
  auto duration = duration_cast<milliseconds>(high_resolution_clock::now() - startTime);

  // Print the data
  this->showAlgoInfos(algoName, duration.count(), depth, player, alpha);
}

tuple<int, Move> Awele::alphaBetaValue(Awele *awele, int alpha, int beta, bool isMax, int depth, int initialDepth)
{
  Move lastMove;
  Move unusedMove = Move(16, Color::Blue, false);
  int value;

  // Check if it is an end position
  if (awele->isWinningMove())
  {
    delete awele;
    return make_tuple(this->maxValue, unusedMove);
  }
  if (awele->isLoosingMove())
  {
    delete awele;
    return make_tuple(-this->maxValue, unusedMove);
  }
  if (awele->isDrawMove())
  {
    delete awele;
    return make_tuple(0, unusedMove);
  }

  // If we reach the final depth
  if (depth == 0)
  {
    // We compute the evalution score for this state
    int eval = this->evaluate2(awele, initialDepth);

    delete awele;
    return make_tuple(eval, unusedMove);
  }

  // Get all possible moves for the given player on the current board state
  vector<Move> possibleMoves = this->getPossibleMoves(awele->getCurrentPlayer());

  // Max
  if (isMax)
  {
    value = -this->maxValue;
    for (Move childMove : possibleMoves)
    {
      value = max(value, get<0>(this->alphaBetaValue(awele->copyAndMove(childMove), alpha, beta, !isMax, depth - 1, initialDepth)));

      if (value >= beta)
      {
        delete awele;
        return make_tuple(value, childMove); /* beta cut */
      }
      alpha = max(alpha, value);
      lastMove = childMove;
    }
    delete awele;
    return make_tuple(value, lastMove);
  }

  // Min
  value = this->maxValue;
  for (Move childMove : possibleMoves)
  {
    value = min(value, get<0>(this->alphaBetaValue(awele->copyAndMove(childMove), alpha, beta, !isMax, depth - 1, initialDepth)));
    
    if (value <= alpha)
    {
      delete awele;
      return make_tuple(value, childMove); /* alpha cut */
    }
    beta = min(beta, value);
    lastMove = childMove;
  }
  delete awele;
  return make_tuple(value, lastMove);
}

/**
 * @brief Perform the minimax algorithm
 * @return A tuple<int, Move> with the evaluation and the corresponding Move
 */
tuple<int, Move> Awele::minimaxValue(Awele *awele, bool isMax, int depth, int initialDepth)
{
  int temp;
  int index = 0;
  tuple<int, Move> result;
  Move unusedMove = Move(16, Color::Blue, false);

  // Check if it is an end position
  if (awele->isWinningMove())
  {
    delete awele;
    return make_tuple(this->maxValue, unusedMove);
  }
  if (awele->isLoosingMove())
  {
    delete awele;
    return make_tuple(-this->maxValue, unusedMove);
  }
  if (awele->isDrawMove())
  {
    delete awele;
    return make_tuple(0, unusedMove);
  }

  // If we reach the final depth
  if (depth == 0)
  {
    // We compute the evalution score for this state
    int eval = this->evaluate2(awele, initialDepth);

    delete awele;
    return make_tuple(eval, unusedMove);
  }

  // Get all possible moves for the given player on the current board state
  vector<Move> possibleMoves = awele->getPossibleMoves(awele->getCurrentPlayer());

  vector<tuple<int, Move>> evals;

  for (Move childMove : possibleMoves)
  {
    evals.push_back(this->minimaxValue(awele->copyAndMove(childMove), !isMax, depth - 1, initialDepth));
  }
  delete awele;

  // Max
  if (isMax)
  {
    temp = -this->maxValue;
    // Get the maximum value
    for (int i = 0; i < evals.size(); i++)
    {
      if (get<0>(evals[i]) > temp)
      {
        temp = get<0>(evals[i]);
        index = i;
      }
    }
  }
  else
  {
    temp = this->maxValue;
    // Get the minimum value
    for (int i = 0; i < evals.size(); i++)
    {
      if (get<0>(evals[i]) < temp)
      {
        temp = get<0>(evals[i]);
        index = i;
      }
    }
  }

  return evals[index];
}

tuple<int, Move> Awele::chessValue(Awele *awele, int depth, int initialDepth)
{
  Move lastMove;
  Move unusedMove = Move(16, Color::Blue, false);
  int score, tempScore;

  // Check if it is an end position
  if (awele->isWinningMove())
  {
    delete awele;
    return make_tuple(this->maxValue, unusedMove);
  }
  if (awele->isLoosingMove())
  {
    delete awele;
    return make_tuple(-this->maxValue, unusedMove);
  }
  if (awele->isDrawMove())
  {
    delete awele;
    return make_tuple(0, unusedMove);
  }

  // If we reach the final depth
  if (depth == 0)
  {
    // We compute the evalution score for this state
    int eval = this->evaluate2(awele, initialDepth);
    
    delete awele;
    return make_tuple(eval, unusedMove);
  }

  // Get all possible moves for the given player on the current board state
  vector<Move> possibleMoves = this->getPossibleMoves(awele->getCurrentPlayer());

  score = -this->maxValue;
  lastMove = possibleMoves[0];
  for (Move childMove : possibleMoves)
  {
    tempScore = -get<0>(this->chessValue(awele->copyAndMove(childMove), depth - 1, initialDepth));

    if (tempScore >= score){
      score = tempScore;
      lastMove = childMove;
    }
  }

  delete awele;
  return make_tuple(score, lastMove);
}