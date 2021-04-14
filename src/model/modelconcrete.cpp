#include "modelconcrete.h"
#include <QDebug>
#include <QBrush>
#include <QPainter>
#include "boardobjectabstract.h"
#include "../display/matrixes.h"
#include "../display/drawinformation.h"
#include "../controller/pausemenustatemain.h"
#include "battlemodel.h"
#include "../filemanagment/filewriter.h"
#include "monstermanualentry.h"
#include "../model/attackmodel.h"
#include "../filemanagment/fileReader.h"
#include <QDir>

ModelConcrete::ModelConcrete(MusicControllerAbstract *musicController)
    : ModelAbstract(musicController)
{
    currentMenuState = new PauseMenuStateMain(this);

    battleModel.setMusicController(musicController);
    boardModel.setMusicController(musicController);
    cutsceneModel.setMusicController(musicController);
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
    if(key == "Board")
    {
        if(message == "PlayMusic")
            boardModel.playBGMusic();
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

bool ModelConcrete::loadBoardBasedOnLoadedCutscene()
{
    if(cutsceneModel.getNextBoardFilePath() != "None")
    {
        boardModel.load(cutsceneModel.getNextBoardFilePath(), &boardObjectsInteratctedWith);
        boardModel.setPlayerPos(cutsceneModel.getXPosBoard(), cutsceneModel.getYPosBoard());
    }
    if(cutsceneModel.getNextEncounter() != "None")
    {
        battleModel.load(cutsceneModel.getNextEncounter(), &playerCharacters, &partyGaugeValue,
                         &numberOfPotions, &numberOfRemedies, &numberOfEthers, &numberOfPickleJars, &gold, &monsterManual, false);

        return true;
    }

    return false;
}

void ModelConcrete::loadSaveGame()
{
    int focusPartyMember = 0;

    QDir dir(QDir::current());
    dir.cdUp();
    std::string theFilePath = dir.path().toStdString()+ "/DnDAdventure/src/test/Saves/Save.txt";

    FileReader fr(theFilePath);

    while(fr.hasNext())
    {
        std::vector<std::string> info = fr.splitString(fr.next(), ',');

        if(info.at(0) == "ObjInteracted")
            boardObjectsInteratctedWith.push_back(std::stoi(info.at(1)));
        if(info.at(0) == "Board")
            boardModel.load(info.at(1), &boardObjectsInteratctedWith);
        if(info.at(0) == "XPos")
            boardModel.setPlayerPos(std::stoi(info.at(1)), boardModel.getYPos());
        if(info.at(0) == "YPos")
            boardModel.setPlayerPos(boardModel.getXPos(), std::stoi(info.at(1)));
        if(info.at(0) == "Gold")
            gold = std::stoi(info.at(1));
        if(info.at(0) == "Potion")
            numberOfPotions = std::stoi(info.at(1));
        if(info.at(0) == "Remedy")
            numberOfRemedies = std::stoi(info.at(1));
        if(info.at(0) == "Ether")
            numberOfEthers = std::stoi(info.at(1));
        if(info.at(0) == "Jar")
            numberOfPickleJars = std::stoi(info.at(1));
        if(info.at(0) == "PartyGauge")
            partyGaugeValue = std::stoi(info.at(1));
        if(info.at(0) == "Equip")
        {
            std::string cretStr = "";
            for(int i = 1; i < info.size(); i++)
                cretStr += (info.at(i) + ",");
            addEquipment(cretStr);
        }
        if(info.at(0) == "Defeated")
            monsterManual.at(std::stoi(info.at(1))).defeat();

        if(info.at(0) == "Character")
        {
            for(int i = 0; i < playerCharacters.size(); i++)
            {
                if(playerCharacters.at(i)->getName() == info.at(1))
                {
                    focusPartyMember = i;
                    break;
                }
            }

            playerCharacters.at(focusPartyMember)->setLevel(std::stoi(info.at(2)));
            playerCharacters.at(focusPartyMember)->setXP(std::stoi(info.at(3)));
            playerCharacters.at(focusPartyMember)->setAP(std::stoi(info.at(4)));
            playerCharacters.at(focusPartyMember)->setIsActive(std::stoi(info.at(5)));
        }
        if(info.at(0) == "Weapon")
            playerCharacters.at(focusPartyMember)->setWeapon(&equipment.at(std::stoi(info.at(1))));
        if(info.at(0) == "Armor")
            playerCharacters.at(focusPartyMember)->setArmor(&equipment.at(std::stoi(info.at(1))));
        if(info.at(0) == "Accessory1")
            playerCharacters.at(focusPartyMember)->setAccessory1(&equipment.at(std::stoi(info.at(1))));
        if(info.at(0) == "Accessory2")
            playerCharacters.at(focusPartyMember)->setAccessory2(&equipment.at(std::stoi(info.at(1))));
        if(info.at(0) == "MoveUnlocked")
            playerCharacters.at(focusPartyMember)->getAttacks()->at(std::stoi(info.at(1)))->unlock();
    }

    //Restore health and mp
    for(int i = 0; i < playerCharacters.size(); i++)
    {
        playerCharacters.at(i)->refillHPandMP();
    }
}

void ModelConcrete::saveGame()
{
    //Restore health and mp
    for(int i = 0; i < playerCharacters.size(); i++)
    {
        playerCharacters.at(i)->refillHPandMP();
    }

    //Save
    std::vector<std::string> saveLines;

    //Chest obtained
    for(int i = 0; i < boardObjectsInteratctedWith.size(); i++)
    {
        saveLines.push_back("ObjInteracted," + std::to_string(boardObjectsInteratctedWith.at(i)));
    }

    //Board. Location
    saveLines.push_back("Board," + boardModel.getLastLoadedFilePath());
    saveLines.push_back("XPos," + std::to_string(boardModel.getXPos()));
    saveLines.push_back("YPos," + std::to_string(boardModel.getYPos()));

    //Items and equipment
    saveLines.push_back("Gold," + std::to_string(gold));
    saveLines.push_back("Potion," + std::to_string(numberOfPotions));
    saveLines.push_back("Remedy," + std::to_string(numberOfRemedies));
    saveLines.push_back("Ether," + std::to_string(numberOfEthers));
    saveLines.push_back("Jar," + std::to_string(numberOfPickleJars));
    saveLines.push_back("PartyGauge," + std::to_string(partyGaugeValue));

    for(int i = 0; i < equipment.size(); i++)
    {
        saveLines.push_back("Equip," + equipment.at(i).getCreationString());
    }

    //Enemies defeated
    for(int i = 0; i < monsterManual.size(); i++)
    {
        if(monsterManual.at(i).getDefeated())
        {
            saveLines.push_back("Defeated," + std::to_string(i));
        }
    }

    //Unlocked characters. Current level, xp, attacks unlocked, equipment
    for(int i = 0; i < playerCharacters.size(); i++)
    {
        saveLines.push_back("Character,"
                            + playerCharacters.at(i)->getName() + ","
                            + std::to_string(playerCharacters.at(i)->getLevel()) + ","
                            + std::to_string(playerCharacters.at(i)->getXP()) + ","
                            + std::to_string(playerCharacters.at(i)->getAP()) + ","
                            + std::to_string(playerCharacters.at(i)->getIsActive())
                            );
        if(playerCharacters.at(i)->getWeapon() != nullptr)
            saveLines.push_back("Weapon," + std::to_string(playerCharacters.at(i)->getWeapon()->getIndexInBag()));
        if(playerCharacters.at(i)->getArmor() != nullptr)
            saveLines.push_back("Armor," + std::to_string(playerCharacters.at(i)->getArmor()->getIndexInBag()));
        if(playerCharacters.at(i)->getAccessory1() != nullptr)
            saveLines.push_back("Accessory1," + std::to_string(playerCharacters.at(i)->getAccessory1()->getIndexInBag()));
        if(playerCharacters.at(i)->getAccessory2() != nullptr)
            saveLines.push_back("Accessory2," + std::to_string(playerCharacters.at(i)->getAccessory2()->getIndexInBag()));

        for(int j = 0; j < playerCharacters.at(i)->getAttacks()->size(); j++)
        {
            if(playerCharacters.at(i)->getAttacks()->at(j)->isUnlocked())
                saveLines.push_back("MoveUnlocked," + std::to_string(j));
        }
    }

    QDir dir(QDir::current());
    dir.cdUp();
    std::string theFilePath = dir.path().toStdString()+ "/DnDAdventure/src/test/Saves/Save.txt";

    FileWriter fw;
    fw.writeLines(theFilePath, saveLines);

    boardModelDialog.push("The game was saved");
}

