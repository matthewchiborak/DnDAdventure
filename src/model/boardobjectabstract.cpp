#include "boardobjectabstract.h"

BoardObjectAbstract::BoardObjectAbstract(int xpos, int ypos, int width, int height, std::string spriteName)
{
    this->xpos = xpos;
    this->ypos = ypos;
    this->width = width;
    this->height = height;
    this->spriteName = spriteName;
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
