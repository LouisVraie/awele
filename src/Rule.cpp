#include "Rule.h"

using namespace Game;

/**
 * Constructor
 */
Rule::Rule()
{
}

void Rule::setNbHoles(int nbHoles)
{
  this->nbHoles = nbHoles;
}

int Rule::getNbHoles()
{
  return this->nbHoles;
}

void Rule::setNbBlueSeeds(int nbBlueSeeds)
{
  this->nbBlueSeeds = nbBlueSeeds;
}
int Rule::getNbBlueSeeds()
{
  return this->nbBlueSeeds;
}

void Rule::setNbRedSeeds(int nbRedSeeds)
{
  this->nbRedSeeds = nbRedSeeds;
}
int Rule::getNbRedSeeds()
{
  return this->nbRedSeeds;
}

void Rule::setNbTransparentSeeds(int nbTransparentSeeds)
{
  this->nbTransparentSeeds = nbTransparentSeeds;
}
int Rule::getNbTransparentSeeds()
{
  return this->nbTransparentSeeds;
}

void Rule::setWinCondition(int winCondition)
{
  this->winCondition = winCondition;
}
int Rule::getWinCondition()
{
  return this->winCondition;
}

void Rule::setDrawCondition(int drawCondition)
{
  this->drawCondition = drawCondition;
}
int Rule::getDrawCondition()
{
  return this->drawCondition;
}

void Rule::setEndCondition(int endCondition)
{
  this->endCondition = endCondition;
}
int Rule::getEndCondition()
{
  return this->endCondition;
}

void Rule::setStarving(bool starving)
{
  this->starving = starving;
}
bool Rule::getStarving()
{
  return this->starving;
}

void Rule::setEatWhenNbSeeds(vector<int> eatWhenNbSeeds)
{
  this->eatWhenNbSeeds = eatWhenNbSeeds;
}

vector<int> Rule::getEatWhenNbSeeds()
{
  return this->eatWhenNbSeeds;
}