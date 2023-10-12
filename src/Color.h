#ifndef COLOR_H
#define COLOR_H

#include <string>
#include <iostream>

using namespace std;

namespace Game
{
  struct ConsoleColor
  {
    const string base = "\033[0m";
    const string blue = "\033[34m";
    const string red = "\033[31m";
    const string transparent = "\033[37m";
  };

  enum Color
  {
    Default = 0,
    Blue = 1,
    Red = 2,
    Transparent = 3
  };

  inline Color getColorFromLetter(char letter)
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
}

#endif
