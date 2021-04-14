#ifndef BOARDOBJECTOBSTACLE_H
#define BOARDOBJECTOBSTACLE_H

#include "boardobjectabstract.h"

class BoardObjectObstacle : public BoardObjectAbstract
{
public:
    BoardObjectObstacle(
            int id,
            int xpos,
            int ypos,
            int width,
            int height,
            std::string spriteName,
            bool solid);

    std::string interact();
    std::string standOnInteract();
};

#endif // BOARDOBJECTOBSTACLE_H
