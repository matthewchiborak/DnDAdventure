#include "boardobjectnpc.h"

BoardObjectNPC::BoardObjectNPC(int xpos, int ypos, int width, int height, std::string spriteName, bool solid)
    : BoardObjectAbstract(xpos, ypos, width, height, spriteName, solid)
{

}

void BoardObjectNPC::interact()
{
    //Unsure what im doing to do with this yet
}
