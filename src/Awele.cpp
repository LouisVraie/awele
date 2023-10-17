#include "Awele.h"

using namespace Game;

/**
 * Constructor
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

  // Ask the player to play
  this->askMove(currentPlayer);

  // Make the move
  this->makeMove(currentPlayer);
}

/**
 * @brief Print the game board
 */
void Awele::show()
{
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
 * @brief Ask the player to enter a move
 */
void Awele::askMove(Player *player)
{
  string input;
  Color chosenColor = Color::Default;
  bool chosenIsTransparent = false;
  int chosenHole;

  bool endAskCondition = true;

  do
  {
    cout << player->getName() << " Choose your move : ";
    cin >> input;

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
          cout << player->getName() << " Invalid move. Please enter a valid move." << endl;
        }
      }
    }
    catch (const exception &)
    {
      chosenHole = -1;
      cout << player->getName() << " Invalid input. Please enter a valid move." << endl;
    }

  } while (endAskCondition);

  // Increment the number of move of the current player
  player->setNbMoves(player->getNbMoves() + 1);

  // Set the chosen move infos
  player->setChosenHole(chosenHole);
  player->setChosenColor(chosenColor);
  player->setChosenIsTransparent(chosenIsTransparent);
}

/**
 * @brief Perform the move chosen by the player
 */
void Awele::makeMove(Player *player)
{
  // if blue
  if (player->getChosenColor() == Color::Blue)
  {
    this->moveBlue(player);
  }
  // if red
  if (player->getChosenColor() == Color::Red)
  {
    this->moveRed(player);
  }
}

/**
 * @brief Perform a blue move
 */
void Awele::moveBlue(Player *player)
{
  vector<Seed *> seeds;

  // get opponent holes
  vector<int> opponentHoles = this->getOpponentHoles(player);

  // if transparent
  if (player->getChosenIsTransparent())
  {
    // get transparent seeds of the chosen hole like blue seeds
    seeds = this->holes[player->getChosenHole()]->getSeedsByColor(Color::Transparent);
  }
  else
  {
    // get blue seeds of the chosen hole
    seeds = this->holes[player->getChosenHole()]->getSeedsByColor(Color::Blue);
  }

  // foreach seed
  for (int i = 0; i < seeds.size(); i++)
  {
    int chosenHole = player->getChosenHole() % 2 == 1 ? player->getChosenHole() + 1 : player->getChosenHole();

    int targetHoleIndex = (chosenHole / 2 + i) % opponentHoles.size();
    int targetHole = opponentHoles[targetHoleIndex];

    // We add the seed to the new hole
    this->holes[targetHole]->addSeed(seeds[i]);

    // We remove the seed of the origin hole
    this->holes[player->getChosenHole()]->removeSeed(seeds[i]);
  }
}

/**
 * @brief Perform a red move
 */
void Awele::moveRed(Player *player)
{
  vector<Seed *> seeds;

  // if transparent
  if (player->getChosenIsTransparent())
  {
    // get transparent seeds of the chosen hole like red seeds
    seeds = this->holes[player->getChosenHole()]->getSeedsByColor(Color::Transparent);
  }
  else
  {
    // get red seeds of the chosen hole
    seeds = this->holes[player->getChosenHole()]->getSeedsByColor(Color::Red);
  }

  // foreach seed
  for (int i = 0; i < seeds.size(); i++)
  {
    int targetHole = (player->getChosenHole() + 1 + i) % this->rule->getNbHoles();

    // We add the seed to the new hole
    this->holes[targetHole]->addSeed(seeds[i]);

    // We remove the seed of the origin hole
    this->holes[player->getChosenHole()]->removeSeed(seeds[i]);
  }
}

/**
 * @brief Check if the given move is possible for the given player
 * @return
 */
bool Awele::isMovePossible(Player *player, int chosenHole, Color chosenColor, bool chosenIsTransparent)
{
  return chosenColor != Color::Default && this->holes[chosenHole]->getNbSeedsByColor(chosenColor) > 0 && chosenHole >= 0 && chosenHole <= this->rule->getNbHoles() - 1 && player->isHoleAllowed(chosenHole);
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
 * @brief Get the opponent holes indexs
 * @return Pointer of the allowedHoles of the opponent player
 */
vector<int> Awele::getOpponentHoles(Player *player)
{
  if (player == this->player1)
  {
    return player2->getAllowedHoles();
  }

  return player1->getAllowedHoles();
}

/**
 * Check all endgame conditions
 * @return GameStatus of the game
 */
GameStatus Awele::checkGameStatus()
{
  int result = GameStatus::InProgress;

  // if player1 won
  if (this->player1->getScore() >= this->rule->getWinCondition())
  {
    return GameStatus::Player1Win;
  }

  // if player2 won
  if (this->player2->getScore() >= this->rule->getWinCondition())
  {
    return GameStatus::Player2Win;
  }

  // if draw
  if (this->player2->getScore() == this->rule->getDrawCondition() && this->player2->getScore() == this->rule->getDrawCondition())
  {
    return GameStatus::Draw;
  }

  // if endCondition
  if (this->getSeedsLeft() <= this->rule->getEndCondition())
  {
    return GameStatus::End;
  }

  return GameStatus::InProgress;
}
