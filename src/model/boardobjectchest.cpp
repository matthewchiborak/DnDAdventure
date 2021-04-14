#include "boardobjectchest.h"

BoardObjectChest::BoardObjectChest(int id, int xpos, int ypos, int width, int height, std::string spriteName, bool solid, std::string emptySpriteName, std::string contents)
    : BoardObjectAbstract(id, xpos, ypos, width, height, spriteName, solid)
{
    this->contents = contents;
    this->emptySpriteName = emptySpriteName;
}

std::string BoardObjectChest::interact()
{
    if(contents == "None")
        return "None";

    std::string toReturn = contents;

    contents = "None";

    this->spriteName = emptySpriteName;

    return "Chest$"+toReturn;
}

std::string BoardObjectChest::standOnInteract()
{
    return "None";
}
