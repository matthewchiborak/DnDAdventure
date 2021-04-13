#ifndef BOARDOBJECTABSTRACT_H
#define BOARDOBJECTABSTRACT_H

#include <iostream>


class BoardObjectAbstract
{
public:
    BoardObjectAbstract(
            int id,
            int xpos,
            int ypos,
            int width,
            int height,
            std::string spriteName,
            bool solid);

    virtual std::string interact();

    int getXpos();
    int getYpos();
    int getWidth();
    int getHeight();
    std::string getSpriteName();
    bool getSolid();
    int getId(); //Will be needed when saving is introduced

    bool isOccupyThisSpace(int x, int y);

protected:
    int xpos;
    int ypos;
    int width;
    int height;
    std::string spriteName;
    bool solid;
    int id;
};

//////////////////



#endif // BOARDOBJECTABSTRACT_H
