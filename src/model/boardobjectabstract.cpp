#include "boardobjectabstract.h"

BoardObjectAbstract::BoardObjectAbstract(int xpos, int ypos, int width, int height, std::string spriteName, bool solid)
{
    this->xpos = xpos;
    this->ypos = ypos;
    this->width = width;
    this->height = height;
    this->spriteName = spriteName;
    this->solid = solid;
}

void BoardObjectAbstract::interact()
{

}

int BoardObjectAbstract::getXpos()
{
    return xpos;
}

int BoardObjectAbstract::getYpos()
{
    return ypos;
}

int BoardObjectAbstract::getWidth()
{
    return width;
}

int BoardObjectAbstract::getHeight()
{
    return height;
}

std::string BoardObjectAbstract::getSpriteName()
{
    return spriteName;
}

bool BoardObjectAbstract::getSolid()
{
    return solid;
}

bool BoardObjectAbstract::isOccupyThisSpace(int x, int y)
{
    if(x >= ypos
            && x < (xpos + width)
            && y >= ypos
            && y < (ypos + height)
            )
    {
        return true;
    }

    return false;
}
