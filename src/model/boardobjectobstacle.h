#ifndef BOARDOBJECTOBSTACLE_H
#define BOARDOBJECTOBSTACLE_H

#include "boardobjectabstract.h"

class BoardObjectObstacle : public BoardObjectAbstract
{
public:
    BoardObjectObstacle(
            int xpos,
            int ypos,
            int width,
            int height,
            std::string spriteName);
};

#endif // BOARDOBJECTOBSTACLE_H
