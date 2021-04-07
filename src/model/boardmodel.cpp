#include "boardmodel.h"

#include <QDebug>

#include "boardobjectabstract.h"
#include "doorway.h"

BoardModel::BoardModel()
{
    srand (time(NULL));
}

void BoardModel::load(std::string loadInfo)
{
    factory.populate(&boardObjects, &doors, &encounterTable, &battleBackgroundKey, &xPos, &yPos, loadInfo);
    xOffset = xPos;// + 12.f;
    yOffset = yPos;// + 0.5f;// + 7.5f;
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

std::vector<BoardObjectAbstract *> *BoardModel::getObjects()
{
    return &boardObjects;
}

void BoardModel::movePlayer(int x, int y, float t)
{
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
            load(tempPath);
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


    int randVal = rand()%20;
    //qDebug() << randVal;

    //if(randVal == 1)
    if(true)
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

