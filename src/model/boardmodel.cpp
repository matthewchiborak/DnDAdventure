#include "boardmodel.h"

#include <QDebug>

#include "boardobjectabstract.h"
#include "doorway.h"

BoardModel::BoardModel()
{
    srand (time(NULL));
}

void BoardModel::load(std::string loadInfo, std::vector<int> *boardObjectInteractedWith)
{
    lastLoadedFilePath = loadInfo;

    clear();

    this->boardObjectInteractedWith = boardObjectInteractedWith;

    factory.populate(&boardObjects, &doors, &encounterTable, &battleBackgroundKey, &backgroundMusicKey, &xPos, &yPos, loadInfo);
    xOffset = xPos;// + 12.f;
    yOffset = yPos;// + 0.5f;// + 7.5f;

    for(int i = 0; i < boardObjects.size(); i++)
    {
        for(int j = 0; j < boardObjectInteractedWith->size(); j++)
        {
            if(boardObjectInteractedWith->at(j) == boardObjects.at(i)->getId())
            {
                boardObjects.at(i)->interact();
                j = boardObjectInteractedWith->size();
            }
        }
    }
}

void BoardModel::clear()
{
    for(int i = 0; i < boardObjects.size(); i++)
    {
        delete boardObjects.at(i);
    }
    boardObjects.clear();
    for(int i = 0; i < doors.size(); i++)
    {
        delete doors.at(i);
    }
    doors.clear();
}

std::string BoardModel::interact(int *objId)
{
    for(int i = 0; i < boardObjects.size(); i++)
    {
        if(boardObjects.at(i)->getSolid())
        {
            if(boardObjects.at(i)->isOccupyThisSpace(xPos + lastDirectionMovedX, yPos + lastDirectionMovedY))
            {
                (*objId) = boardObjects.at(i)->getId();
                return boardObjects.at(i)->interact();
            }
        }
    }

    return "None";
}

std::string BoardModel::standOnInteract()
{
    for(int i = 0; i < boardObjects.size(); i++)
    {
        if(!boardObjects.at(i)->getSolid())
        {
            if(boardObjects.at(i)->isOccupyThisSpace(xPos, yPos))
            {
                if(boardObjects.at(i)->standOnInteract() != "None")
                    return boardObjects.at(i)->standOnInteract();
            }
        }
    }

    return "None";
}

std::vector<BoardObjectAbstract *> *BoardModel::getObjects()
{
    return &boardObjects;
}

void BoardModel::movePlayer(int x, int y, float t)
{
    lastDirectionMovedX = x;
    lastDirectionMovedY = y;

    //Check if even can move
    if(!playerCanMoveThisWay(x, y))
        return;

    if(t > 1)
    {
        xPos += x;
        yPos += y;
        xOffset = (xPos);
        yOffset = (yPos);
    }
    else
    {
        xOffset = (xPos) + (x*t);
        yOffset = (yPos) + (y*t);
    }
}

void BoardModel::setPlayerPos(int x, int y)
{
    xPos = x;
    yPos = y;
    xOffset = x;
    yOffset = y;
}

float BoardModel::getXOffset()
{
    return xOffset;
}

float BoardModel::getYOffset()
{
    return yOffset;
}

int BoardModel::getXPos()
{
    return xPos;
}

int BoardModel::getYPos()
{
    return yPos;
}

void BoardModel::checkAndActivateDoor()
{
    for(int i = 0; i < doors.size(); i++)
    {
        if(doors.at(i)->isOccupyThisSpace(xPos, yPos))
        {
            int tempx = doors.at(i)->getNewXPos();
            int tempy = doors.at(i)->getNewYPos();
            std::string tempPath = doors.at(i)->getBoardKey();
            clear();
            load(tempPath, boardObjectInteractedWith);
            xPos = tempx;
            yPos = tempy;
            xOffset = (xPos);
            yOffset = (yPos);
            return;
        }
    }
}

bool BoardModel::tryToGetAnEnounter(std::string *keyToReturn)
{
    if(encounterTable.size() <= 0)
        return false;


    int randVal = rand()%10;

    if(randVal == 1)
    {
        (*keyToReturn) = encounterTable.at(rand()%encounterTable.size());
        return true;
    }

    return false;
}

std::string BoardModel::getBattleBackgroundKey()
{
    return battleBackgroundKey;
}

void BoardModel::setMusicController(MusicControllerAbstract *musicController)
{
    this->musicController = musicController;
}

void BoardModel::playBGMusic()
{
    musicController->playMusic(backgroundMusicKey);
}

std::string BoardModel::getLastLoadedFilePath()
{
    return lastLoadedFilePath;
}

bool BoardModel::playerCanMoveThisWay(int x, int y)
{
    for(int i = 0; i < boardObjects.size(); i++)
    {
        if(boardObjects.at(i)->getSolid())
        {
            if(boardObjects.at(i)->isOccupyThisSpace((xPos + x), (yPos + y)))
            {
                return false;
            }
        }
    }

    return true;
}

