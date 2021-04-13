#ifndef BOARDOBJECTNPC_H
#define BOARDOBJECTNPC_H

#include "boardobjectabstract.h"

class BoardObjectNPC : public BoardObjectAbstract
{
public:
    BoardObjectNPC(
            int id,
            int xpos,
            int ypos,
            int width,
            int height,
            std::string spriteName,
            bool solid,
            std::string dialog
            );

    std::string interact();

private:
    std::string dialog;
};

#endif // BOARDOBJECTNPC_H
