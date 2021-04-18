#include "boardobjectshop.h"

#include <QDebug>

BoardObjectShop::BoardObjectShop(int id, int xpos, int ypos, int width, int height, std::string spriteName, bool solid, std::string availableItemsStrings)
    : BoardObjectAbstract(id, xpos, ypos, width, height, spriteName, solid)
{
    this->availableItemsStrings = availableItemsStrings;
}

std::string BoardObjectShop::interact()
{
    return "Shop@" + availableItemsStrings;
}

std::string BoardObjectShop::standOnInteract()
{
    return "None";
}
