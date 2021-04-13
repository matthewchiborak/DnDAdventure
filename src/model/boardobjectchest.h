#ifndef BOARDOBJECTCHEST_H
#define BOARDOBJECTCHEST_H

#include "boardobjectabstract.h"

class BoardObjectChest : public BoardObjectAbstract
{
public:
    BoardObjectChest(
            int id,
            int xpos,
            int ypos,
            int width,
            int height,
            std::string spriteName,
            bool solid,
            std::string emptySpriteName,
            std::string contents
            );

    std::string interact();

private:
    std::string contents;
    std::string emptySpriteName;
};

#endif // BOARDOBJECTCHEST_H
