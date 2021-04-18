#ifndef BOARDOBJECTSHOP_H
#define BOARDOBJECTSHOP_H

#include "boardobjectabstract.h"

class BoardObjectShop : public BoardObjectAbstract
{
public:
    BoardObjectShop(
            int id,
            int xpos,
            int ypos,
            int width,
            int height,
            std::string spriteName,
            bool solid,
            std::string availableItemsStrings
            );

    std::string interact();
    std::string standOnInteract();

private:
    std::string availableItemsStrings;
};

#endif // BOARDOBJECTSHOP_H
