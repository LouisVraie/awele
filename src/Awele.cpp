#include "Awele.h"
#include "Move.h"

using namespace Game;

/**
 * @brief Constructor
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
  Player *currentPlayer = nullptr;

  // Adding a new turn
  this->turn++;

  // Show the board
  this->show();

  // Select the player to play
  if (turn % 2 == 1)
  {
    currentPlayer = this->player1;
  }
  else
  {
    currentPlayer = this->player2;
  }

  Move move = Move(this);

  // Get corresponding depth
  int depth = this->getDynamicDepth(currentPlayer);

  // Ask the player to play
  move.decisionAlphaBeta(currentPlayer, depth);

  move.askMove(currentPlayer);

  // Make the move
  move.makeMove(currentPlayer);

  // Update the score after the move
  this->scoreAfterMove(currentPlayer);

  // Check if the opponent is starved
  this->checkStarving(currentPlayer);
}

/**
 * @brief Print the game board
 */
void Awele::show()
{
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
      cout << opponent->getName() << " is starved !" << endl;

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
    if(this->holes[i]->getNbSeedsByColor(Color::Blue) > 0)
    {
      result++;
    }
    if(this->holes[i]->getNbSeedsByColor(Color::Red) > 0)
    {
      result++;
    }
    if(this->holes[i]->getNbSeedsByColor(Color::Transparent) > 0)
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
  if (this->turn == 1)
  {
    return 1;
  }

  // // Get the number of part of holes with seeds
  // int holesPartWithSeeds = this->getHolesPartWithSeeds();

  // cout << "HOLES PARTS : " << holesPartWithSeeds << endl;
  // Get the number of seeds left
  int seedsLeft = this->getSeedsLeft();

  if (seedsLeft >= 70)
  {
    return 3;
  }
  if (seedsLeft >= 60)
  {
    return 6;
  }
  if (seedsLeft >= 50)
  {
    return 7;
  }
  if (seedsLeft >= 40)
  {
    return 8;
  }
  if (seedsLeft >= 30)
  {
    return 9;
  }
  if (seedsLeft >= 20)
  {
    return 10;
  }
  if (seedsLeft >= 10)
  {
    return 11;
  }

  return 1;
}

/**
 * @brief Get the opponent player from the given player
 * @return The opponent player
 */
Player *Awele::getOpponent(Player *player)
{
  if (player == this->player1)
  {
    return player2;
  }

  return player1;
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
