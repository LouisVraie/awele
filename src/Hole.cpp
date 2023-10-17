#include "Hole.h"

using namespace Game;

/**
 * Constructor
 */
Hole::Hole(int nbBlueSeeds, int nbRedSeeds, int nbTransparentSeeds)
{
  // Creation of blue seed(s)
  for (int iBlue = 0; iBlue < nbBlueSeeds; iBlue++)
  {
    Seed *blueSeed = new Seed(Color::Blue);
    this->seeds.push_back(blueSeed);
  }

  // Creation of red seed(s)
  for (int iRed = 0; iRed < nbRedSeeds; iRed++)
  {
    Seed *redSeed = new Seed(Color::Red);
    this->seeds.push_back(redSeed);
  }

  // Creation of transparent seed(s)
  for (int iTransparent = 0; iTransparent < nbTransparentSeeds; iTransparent++)
  {
    Seed *transparentSeed = new Seed(Color::Transparent);
    this->seeds.push_back(transparentSeed);
  }
}

/**
 * @return The number of seeds of the current Hole
 */
int Hole::getNbSeeds()
{
  return this->seeds.size();
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
  int nbSeeds = 0;

  for (int i = 0; i < this->seeds.size(); i++)
  {
    if (this->seeds[i]->getColor() == color)
    {
      nbSeeds++;
    }
  }

  return nbSeeds;
}

/**
 * @brief Get the seeds of by the color
 * @return Vector of seeds pointers of the current hole of the given color
 */
vector<Seed *> Hole::getSeedsByColor(Color color)
{
  vector<Seed *> seeds;

  for (Seed *seed : this->seeds)
  {
    if (seed->getColor() == color)
    {
      seeds.push_back(seed);
    }
  }

  return seeds;
}

/**
 * @brief Add the given seed to the hole
 */
void Hole::addSeed(Seed *seed)
{
  this->seeds.push_back(seed);
}

/**
 * @brief Remove the given seed of the hole
 */
void Hole::removeSeed(Seed *seed)
{
  for (auto it = seeds.begin(); it != seeds.end(); ++it)
  {
    if (*it == seed)
    {
      // Remove the seed
      seeds.erase(it);
      break;
    }
  }
}