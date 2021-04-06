#include "boardmodel.h"

#include <QDebug>

#include "boardobjectabstract.h"

BoardModel::BoardModel()
{

}

void BoardModel::load(std::string loadInfo)
{
    factory.populate(&boardObjects, &xPos, &yPos, loadInfo);
    xOffset = xPos;// + 12.f;
    yOffset = yPos;// + 0.5f;// + 7.5f;
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

