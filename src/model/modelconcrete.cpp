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

    if(hasBoardDialogRemaining())
    {
        //Draw the dialog
        DrawInformation topTextBox(-700, -375, 1500, 140, "BattleMenuBG", false);
        items->push_back(topTextBox);

        DrawInformation dialogDesc(0, 730, 1500, 140, "",
                                false, boardModelDialog.front());
        items->push_back(dialogDesc);
    }
}

void ModelConcrete::loadBoardModel(std::string loadInfo)
{
    boardModel.load(loadInfo, &boardObjectsInteratctedWith);
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

void ModelConcrete::moveMenuCursor(int x, int y, std::string key)
{
    if(key == "Pause")
        currentMenuState->moveMenuCursor(x, y);
    else if(key == "Battle")
        battleModel.moveMenuCursor(x, y);
}

void ModelConcrete::enterMenu(std::string key)
{
    if(key == "Pause")
    {
        PauseMenuDrawState * temp = currentMenuState;
        currentMenuState = currentMenuState->enterMenu();

        if(temp != currentMenuState)
            delete temp;
    }
    else if(key == "Battle")
    {
        battleModel.enterMenu();
    }
    else if(key == "Cutscene")
    {
        cutsceneModel.advance();
    }
}

void ModelConcrete::closeMenu(std::string key)
{
    if(key == "Pause")
    {
        this->pauseIsDone = currentMenuState->isMain();
        PauseMenuDrawState * temp = currentMenuState;
        currentMenuState = currentMenuState->closeMenu();
        //if(temp != currentMenuState)
            //delete temp;
    }
    else if(key == "Battle")
        battleModel.closeMenu();
}

bool ModelConcrete::tryToStartABattle()
{
    std::string encounterKey;
    bool isStartBattle = boardModel.tryToGetAnEnounter(&encounterKey);

    if(!isStartBattle)
        return false;

    //Load the enoucter in the battle model
    battleModel.load(encounterKey, &playerCharacters, &partyGaugeValue,
                     &numberOfPotions, &numberOfRemedies, &numberOfEthers, &numberOfPickleJars, &gold, &monsterManual);

    //Set the render and input states
    return true;
}

void ModelConcrete::drawBattleModel(std::vector<DrawInformation> *items)
{
    //Background first
    DrawInformation info(-750, -120, 1600, 620, boardModel.getBattleBackgroundKey(), false);
    items->push_back(info);

    battleModel.draw(items);
}

void ModelConcrete::passTime(float value)
{
    battleModel.passTime(value);
}

bool ModelConcrete::isBattleDone()
{
    return battleModel.isTheBattleDone();
}

bool ModelConcrete::isGameOver()
{
    return battleModel.isGameOver();
}

void ModelConcrete::qrPressed(bool wasQ)
{
    battleModel.qrPressed(wasQ);
}

void ModelConcrete::specialMessage(std::string message, std::string key)
{
    if(key == "Pause")
    {
        currentMenuState->speicalMessage(message);
    }
}

std::string ModelConcrete::interact()
{
    int potId;
    std::string toReturn = boardModel.interact(&potId);

    if(toReturn.at(0) == 'C'
            && toReturn.at(1) == 'h'
            && toReturn.at(2) == 'e'
            && toReturn.at(3) == 's'
            && toReturn.at(4) == 't'
            )
        boardObjectsInteratctedWith.push_back(potId);

    return toReturn;
}

std::string ModelConcrete::standOnInteract()
{
    return boardModel.standOnInteract();
}

void ModelConcrete::loadCutscene(std::string filepath)
{
    cutsceneModel.load(filepath);
}

void ModelConcrete::drawCutscene(std::vector<DrawInformation> *items)
{
    cutsceneModel.draw(items);
}

bool ModelConcrete::cutsceneIsDone()
{
    return cutsceneModel.isDone();
}

void ModelConcrete::loadBoardBasedOnLoadedCutscene()
{
    boardModel.load(cutsceneModel.getNextBoardFilePath(), &boardObjectsInteratctedWith);
    boardModel.setPlayerPos(cutsceneModel.getXPosBoard(), cutsceneModel.getYPosBoard());
}

