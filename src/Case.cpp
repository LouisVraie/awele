#include "Case.h"

using namespace Game;

/**
 * Constructor
 */
Case::Case(int nbBlueSeeds, int nbRedSeeds, int nbTransparentSeeds)
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
 * @return The number of seeds of the current Case
 */
int Case::getNbSeeds()
{
  return this->seeds.size();
}

/**
 * @brief Print the current case
 */
void Case::show()
{
  ConsoleColor consoleColor;

  cout << "[";

  cout << consoleColor.blue << this->getNbSeedsByColor(Color::Blue);
  cout << consoleColor.base << "|";
  cout << consoleColor.red << this->getNbSeedsByColor(Color::Red);
  cout << consoleColor.base << "|";
  cout << consoleColor.transparent  << this->getNbSeedsByColor(Color::Transparent);
  cout << consoleColor.base;
  
  cout << "]";
}

int Case::getNbSeedsByColor(Color color)
{
  int nbSeeds = 0;

  for (int i = 0; i < this->seeds.size(); i++)
  {
    if(this->seeds[i]->getColor() == color)
    {
      nbSeeds++;
    }
  }

  return nbSeeds;
}