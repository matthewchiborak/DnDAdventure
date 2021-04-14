#ifndef BOARDOBJECTCUTSCENETRIGGER_H
#define BOARDOBJECTCUTSCENETRIGGER_H

#include "boardobjectabstract.h"

class BoardObjectCutsceneTrigger : public BoardObjectAbstract
{
public:
    BoardObjectCutsceneTrigger(
            int id,
            int xpos,
            int ypos,
            int width,
            int height,
            std::string spriteName,
            bool solid,
            std::string cutsceneFilepath
            );

    std::string interact();
    std::string standOnInteract();

private:
    std::string cutsceneFilepath;
};

#endif // BOARDOBJECTCUTSCENETRIGGER_H
