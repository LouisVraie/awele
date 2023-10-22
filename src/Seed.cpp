#include "Seed.h"

using namespace Game;

/**
 * @brief Constructor
 */
Seed::Seed(Color color)
{
  this->color = color;
}

/**
 * @brief Copy an instance
 */
Seed::Seed(const Seed &seed)
{
  this->color = seed.color;
}

Color Seed::getColor()
{
  return this->color;
}