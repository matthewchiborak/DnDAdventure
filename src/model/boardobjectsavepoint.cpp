#include "boardobjectsavepoint.h"

BoardObjectSavePoint::BoardObjectSavePoint(int id, int xpos, int ypos, int width, int height, std::string spriteName, bool solid)
    : BoardObjectAbstract(id, xpos, ypos, width, height, spriteName, solid)
{

}

std::string BoardObjectSavePoint::interact()
{
    return "Save";
}

std::string BoardObjectSavePoint::standOnInteract()
{
    return "None";
}
