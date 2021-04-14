#include "doorway.h"
#include <QDir>
#include <QDebug>

Doorway::Doorway(int xpos, int ypos, int width, int height, std::string boardKey, int newXPos, int newYPos)
{
    this->xpos = xpos;
    this->ypos = ypos;
    this->width = width;
    this->height= height;

    //Get the image location from the other map, create and store the flyweight
    this->boardKey = boardKey;
    this->newXPos = newXPos;
    this->newYPos = newYPos;
}

std::string Doorway::getBoardKey()
{
    return boardKey;
}

int Doorway::getNewXPos()
{
    return newXPos;
}

int Doorway::getNewYPos()
{
    return newYPos;
}

bool Doorway::isOccupyThisSpace(int x, int y)
{
    if(x >= xpos
            && x < (xpos + width)
            && y >= ypos
            && y < (ypos + height)
            )
    {
        return true;
    }

    return false;
}
