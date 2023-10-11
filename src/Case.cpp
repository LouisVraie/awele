#include "Case.h"

using namespace Game;

/**
 * Constructor
 */
Case::Case()
{
  // Creation of blue seed(s)
  for (int iBlue = 0; iBlue < this->getNbBlueSeeds(); iBlue++)
  {
    Seed *blueSeed = new Seed(Color::Blue);
    this->seeds.push_back(blueSeed);
  }

  // Creation of red seed(s)
  for (int iRed = 0; iRed < this->getNbRedSeeds(); iRed++)
  {
    Seed *redSeed = new Seed(Color::Red);
    this->seeds.push_back(redSeed);
  }

  // Creation of transparent seed(s)
  for (int iTransparent = 0; iTransparent < this->getNbTransparentSeeds(); iTransparent++)
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