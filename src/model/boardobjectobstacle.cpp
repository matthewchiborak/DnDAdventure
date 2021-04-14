#include "boardobjectobstacle.h"

BoardObjectObstacle::BoardObjectObstacle(int id, int xpos, int ypos, int width, int height, std::string spriteName, bool solid)
    : BoardObjectAbstract(id, xpos, ypos, width, height, spriteName, solid)
{

}

std::string BoardObjectObstacle::interact()
{
    return "None";
}

std::string BoardObjectObstacle::standOnInteract()
{
    return "None";
}
