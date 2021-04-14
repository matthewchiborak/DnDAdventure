#include "boardobjectnpc.h"

BoardObjectNPC::BoardObjectNPC(int id, int xpos, int ypos, int width, int height, std::string spriteName, bool solid, std::string dialog)
    : BoardObjectAbstract(id, xpos, ypos, width, height, spriteName, solid)
{
    this->dialog = dialog;
}

std::string BoardObjectNPC::interact()
{
    //Unsure what im doing to do with this yet
    return "NPC$" + dialog;
}

std::string BoardObjectNPC::standOnInteract()
{
    return "None";
}
