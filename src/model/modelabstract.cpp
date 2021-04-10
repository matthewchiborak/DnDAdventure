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

void ModelAbstract::drawPauseMenu(std::vector<DrawInformation> *items)
{

}

void ModelAbstract::moveMenuCursor(int x, int y, std::string key)
{

}

void ModelAbstract::enterMenu(std::string key)
{

}

void ModelAbstract::closeMenu(std::string key)
{

}

bool ModelAbstract::tryToStartABattle()
{
    return false;
}

void ModelAbstract::drawBattleModel(std::vector<DrawInformation> *items)
{

}

void ModelAbstract::passTime(float value)
{

}

bool ModelAbstract::isBattleDone()
{
    return true;
}

bool ModelAbstract::isGameOver()
{
    return false;
}

void ModelAbstract::qrPressed(bool wasQ)
{

}

