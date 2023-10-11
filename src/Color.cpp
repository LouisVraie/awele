#include "Color.h"

using namespace Game;

Color getColorFromLetter(char letter)
{
  switch (letter)
  {
  case 'B':
    return Color::Blue;
    break;
  case 'R':
    return Color::Red;
    break;
  default:
    return Color::Default;
  }
}