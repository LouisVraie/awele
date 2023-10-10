#include "Rule.h"

using namespace Game;

/**
 * Constructor
*/
Rule::Rule()
{

}

void Rule::SetNbCases(int nbCases)
{
  this->nbCases = nbCases;
}

int Rule::GetNbCases()
{
  return this->nbCases;
}

void Rule::SetNbBlueSeeds(int nbBlueSeeds)
{
  this->nbBlueSeeds = nbBlueSeeds;
}
int Rule::GetNbBlueSeeds()
{
  return this->nbBlueSeeds;
}

void Rule::SetNbRedSeeds(int nbRedSeeds)
{
  this->nbRedSeeds = nbRedSeeds;
}
int Rule::GetNbRedSeeds()
{
  return this->nbRedSeeds;
}

void Rule::SetNbTransparentSeeds(int nbTransparentSeeds)
{
  this->nbTransparentSeeds = nbTransparentSeeds;
}
int Rule::GetNbTransparentSeeds()
{
  return this->nbTransparentSeeds;
}

void Rule::SetWinCondition(int winCondition)
{
  this->winCondition = winCondition;
}
int Rule::GetWinCondition()
{
  return this->winCondition;
}

void Rule::SetDrawCondition(int drawCondition)
{
  this->drawCondition = drawCondition;
}
int Rule::GetDrawCondition()
{
  return this->drawCondition;
}

void Rule::SetEndCondition(int endCondition)
{
  this->endCondition = endCondition;
}
int Rule::GetEndCondition()
{
  return this->endCondition;
}

void Rule::SetStarving(bool starving)
{
  this->starving = starving;
}
bool Rule::GetStarving()
{
  return this->starving;
}

void Rule::SetEatWhenNbSeeds(vector<int> eatWhenNbSeeds)
{
  this->eatWhenNbSeeds = eatWhenNbSeeds;
}

vector<int> Rule::GetEatWhenNbSeeds()
{
  return this->eatWhenNbSeeds;
}