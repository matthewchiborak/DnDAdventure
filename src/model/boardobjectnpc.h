#ifndef BOARDOBJECTNPC_H
#define BOARDOBJECTNPC_H

#include "boardobjectabstract.h"

class BoardObjectNPC : public BoardObjectAbstract
{
public:
    BoardObjectNPC(
            int xpos,
            int ypos,
            int width,
            int height,
            std::string spriteName,
            bool solid
            );

    void interact();
};

#endif // BOARDOBJECTNPC_H
