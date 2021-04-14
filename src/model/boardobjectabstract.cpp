#include "boardobjectabstract.h"

BoardObjectAbstract::BoardObjectAbstract(int id, int xpos, int ypos, int width, int height, std::string spriteName, bool solid)
{
    this->id = id;
    this->xpos = xpos;
    this->ypos = ypos;
    this->width = width;
    this->height = height;
    this->spriteName = spriteName;
    this->solid = solid;
}

std::string BoardObjectAbstract::interact()
{
    return "None";
}

std::string BoardObjectAbstract::standOnInteract()
{
    return "None";
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

int BoardObjectAbstract::getId()
{
    return id;
}

bool BoardObjectAbstract::isOccupyThisSpace(int x, int y)
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
