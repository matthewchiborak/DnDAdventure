#include "modelconcrete.h"
#include <QDebug>
#include <QBrush>
#include <QPainter>
#include "boardobjectabstract.h"
#include "../display/matrixes.h"
#include "../display/drawinformation.h"

ModelConcrete::ModelConcrete()
    : ModelAbstract()
{

}

void ModelConcrete::drawBoardModel(std::vector<DrawInformation> * items, float *xOffset, float *yOffset)
{
    (*xOffset) = boardModel.getXOffset();
    (*yOffset) = boardModel.getYOffset();

    std::vector<BoardObjectAbstract*> * bobjs = boardModel.getObjects();
    for(int i = 0; i < bobjs->size(); i++)
    {
        DrawInformation info(bobjs->at(i)->getXpos(), bobjs->at(i)->getYpos(), bobjs->at(i)->getWidth(), bobjs->at(i)->getHeight(), bobjs->at(i)->getSpriteName(), true);
        items->push_back(info);
    }

    //Active player character for moving
    DrawInformation charinfo(0, 0, 1, 1, playerCharacters.at(0)->getSpriteKey(), false);
    items->push_back(charinfo);
}

void ModelConcrete::loadBoardModel(std::string loadInfo)
{
    boardModel.load(loadInfo);
}

std::string ModelConcrete::handleBoardCollisionTriggers()
{
    boardModel.checkAndActivateDoor();

    return "None";
}

void ModelConcrete::movePlayer(int x, int y, float t)
{
    boardModel.movePlayer(x, y, t);
}

