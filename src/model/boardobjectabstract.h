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
            std::string spriteName,
            bool solid);

    virtual void interact();

    int getXpos();
    int getYpos();
    int getWidth();
    int getHeight();
    std::string getSpriteName();
    bool getSolid();

protected:
    int xpos;
    int ypos;
    int width;
    int height;
    std::string spriteName;
    bool solid;
};

//////////////////



#endif // BOARDOBJECTABSTRACT_H
