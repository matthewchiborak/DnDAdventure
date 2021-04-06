#include "modelabstract.h"

ModelAbstract::ModelAbstract()
{

}

ModelAbstract::~ModelAbstract()
{
    for(int i = 0; i < playerCharacters.size(); i++)
    {
        delete playerCharacters.at(i);
    }
}

void ModelAbstract::addPlayerCharacter(PlayerCharacterStats *character)
{
    playerCharacters.push_back(character);
}


void ModelAbstract::drawBoardModel(std::vector<DrawInformation> * items, float *xOffset, float *yOffset)
{

}
void ModelAbstract::loadBoardModel(std::string loadInfo)
{

}

std::string ModelAbstract::handleBoardCollisionTriggers()
{
    return "None";
}

void ModelAbstract::movePlayer(int x, int y, float t)
{

}

