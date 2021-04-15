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
            int newYPos,
            std::string spriteKey
            );

    std::string getBoardKey();
    int getNewXPos();
    int getNewYPos();

    bool isOccupyThisSpace(int x, int y);

    std::string getSpriteKey();
    int getXPos();
    int getYPos();
    int getWidth();
    int getHeight();

private:
    std::string spriteKey;
    int xpos;
    int ypos;
    int width;
    int height;
    std::string boardKey;
    int newXPos;
    int newYPos;
};

#endif // DOORWAY_H
