#ifndef BOARDOBJECTSAVEPOINT_H
#define BOARDOBJECTSAVEPOINT_H

#include "boardobjectabstract.h"

class BoardObjectSavePoint : public BoardObjectAbstract
{
public:
    BoardObjectSavePoint(
            int id,
            int xpos,
            int ypos,
            int width,
            int height,
            std::string spriteName,
            bool solid
            );

    std::string interact();
    std::string standOnInteract();
};

#endif // BOARDOBJECTSAVEPOINT_H
