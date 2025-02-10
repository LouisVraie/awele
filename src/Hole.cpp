#include "Hole.h"

using namespace Game;

/**
 * @brief Constructor
 */
Hole::Hole(int nbBlueSeeds, int nbRedSeeds, int nbTransparentSeeds)
{
  // Creation of blue seed(s)
  this->nbBlueSeeds = nbBlueSeeds;

  // Creation of red seed(s)
  this->nbRedSeeds = nbRedSeeds;

  // Creation of transparent seed(s)
  this->nbTransparentSeeds = nbTransparentSeeds;
}

/**
 * @brief Copy an instance
 */
Hole::Hole(const Hole &hole)
{
  this->nbBlueSeeds = hole.nbBlueSeeds;
  this->nbRedSeeds = hole.nbRedSeeds;
  this->nbTransparentSeeds = hole.nbTransparentSeeds;
}

/**
 * @brief Destructor
 */
Hole::~Hole()
{
}

/**
 * @return The number of seeds of the current Hole
 */
int Hole::getNbSeeds()
{
  return this->nbBlueSeeds + this->nbRedSeeds + this->nbTransparentSeeds;
}

/**
 * @brief Print the current hole
 */
void Hole::show()
{
  ConsoleColor consoleColor;

  cout << "[";

  cout << consoleColor.blue << this->getNbSeedsByColor(Color::Blue);
  cout << consoleColor.base << "|";
  cout << consoleColor.red << this->getNbSeedsByColor(Color::Red);
  cout << consoleColor.base << "|";
  cout << consoleColor.transparent << this->getNbSeedsByColor(Color::Transparent);
  cout << consoleColor.base;

  cout << "]";
}

int Hole::getNbSeedsByColor(Color color)
{
  switch (color)
  {
  case Color::Blue:
    return this->nbBlueSeeds;
  case Color::Red:
    return this->nbRedSeeds;
  case Color::Transparent:
    return this->nbTransparentSeeds;
  default:
    return 0;
  }
}

/**
 * @brief Add the given seed to the hole
 */
void Hole::addSeed(int nbSeeds, Color color)
{
  switch (color)
  {
  case Color::Blue:
    this->nbBlueSeeds += nbSeeds;
    break;
  case Color::Red:
    this->nbRedSeeds += nbSeeds;
    break;
  case Color::Transparent:
    this->nbTransparentSeeds += nbSeeds;
    break;
  default:
    break;
  }
}

/**
 * @brief Remove the given seed of the hole
 */
void Hole::removeSeed(int nbSeeds, Color color)
{
  switch (color)
  {
  case Color::Blue:
    this->nbBlueSeeds -= nbSeeds;
    break;
  case Color::Red:
    this->nbRedSeeds -= nbSeeds;
    break;
  case Color::Transparent:
    this->nbTransparentSeeds -= nbSeeds;
    break;
  default:
    break;
  }
}

/**
 * @brief Remove all seeds of the hole
 */
void Hole::removeAllSeeds()
{
  this->nbBlueSeeds = 0;
  this->nbRedSeeds = 0;
  this->nbTransparentSeeds = 0;
}