#ifndef BOARDOBJECTABSTRACT_H
#define BOARDOBJECTABSTRACT_H

#include <iostream>


class BoardObjectAbstract
{
public:
    BoardObjectAbstract(
            int xpos,
            int ypos,
            int width,
            int height,
            std::string spriteName);

    void interact();

    int getXpos();
    int getYpos();
    int getWidth();
    int getHeight();
    std::string getSpriteName();

protected:
    int xpos;
    int ypos;
    int width;
    int height;
    std::string spriteName;
};

#endif // BOARDOBJECTABSTRACT_H
