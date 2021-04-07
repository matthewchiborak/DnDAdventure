#include "modelconcrete.h"
#include <QDebug>
#include <QBrush>
#include <QPainter>
#include "boardobjectabstract.h"
#include "../display/matrixes.h"
#include "../display/drawinformation.h"
#include "../controller/pausemenustatemain.h"
#include "battlemodel.h"

ModelConcrete::ModelConcrete()
    : ModelAbstract()
{
    currentMenuState = new PauseMenuStateMain(this);
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
    DrawInformation charinfo(0, 0, 100, 100, playerCharacters.at(0)->getSpriteKey(), false);
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

void ModelConcrete::drawPauseMenu(std::vector<DrawInformation> *items)
{
    //Background first
    DrawInformation info(-800, -400, 1700, 900, "PauseMenuBG", false);
    items->push_back(info);

    currentMenuState->drawPauseMenu(items);
}

void ModelConcrete::moveMenuCursor(int x, int y)
{
    currentMenuState->moveMenuCursor(x, y);
}

void ModelConcrete::enterMenu()
{
    PauseMenuDrawState * temp = currentMenuState;
    currentMenuState = currentMenuState->enterMenu();

    if(temp != currentMenuState)
        delete temp;
}

void ModelConcrete::closeMenu()
{
    currentMenuState = currentMenuState->closeMenu();
}

bool ModelConcrete::tryToStartABattle()
{
    //qDebug() << "Trying to start a fight";

    std::string encounterKey;
    bool isStartBattle = boardModel.tryToGetAnEnounter(&encounterKey);

    if(!isStartBattle)
        return false;

    //Load the enoucter in the battle model
    //Reset values

    //Set the render and input states
    return true;
}

void ModelConcrete::drawBattleModel(std::vector<DrawInformation> *items)
{
    battleModel.draw(items);
}

