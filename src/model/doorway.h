#ifndef DOORWAY_H
#define DOORWAY_H

#include <string>

class Doorway
{
public:
    Doorway(
            int xpos,
            int ypos,
            int width,
            int height,
            std::string boardKey,
            int newXPos,
            int newYPos
            );

    std::string getBoardKey();
    int getNewXPos();
    int getNewYPos();

    bool isOccupyThisSpace(int x, int y);

private:
    int xpos;
    int ypos;
    int width;
    int height;
    std::string boardKey;
    int newXPos;
    int newYPos;
};

#endif // DOORWAY_H
