#include "Seed.h"

using namespace Game;

/**
 * Constructor
 */
Seed::Seed(Color color)
{
  this->color = color;
}

Color Seed::getColor()
{
  return this->color;
}