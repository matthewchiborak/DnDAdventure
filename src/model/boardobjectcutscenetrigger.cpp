#include "boardobjectcutscenetrigger.h"

BoardObjectCutsceneTrigger::BoardObjectCutsceneTrigger(int id, int xpos, int ypos, int width, int height, std::string spriteName, bool solid, std::string cutsceneFilepath)
    : BoardObjectAbstract(id, xpos, ypos, width, height, spriteName, solid)
{
    this->cutsceneFilepath = cutsceneFilepath;
}

std::string BoardObjectCutsceneTrigger::interact()
{
    return "None";
}

std::string BoardObjectCutsceneTrigger::standOnInteract()
{
    return "Cutscene$" + cutsceneFilepath;
}
