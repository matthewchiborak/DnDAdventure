#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <vector>

#include "gamemodelabstract.h"
#include "../factory/boardobjectfactory.h"

class BoardObjectAbstract;

class BoardModel //: public GameModelAbstract
{
public:
    BoardModel();

    //void draw(QPainter *p);
    void load(std::string loadInfo);

    std::vector<BoardObjectAbstract*> * getObjects();

    void movePlayer(int x, int y, float t);

    float getXOffset();
    float getYOffset();
    int getXPos();
    int getYPos();

private:
    std::vector<BoardObjectAbstract*> boardObjects;
    BoardObjectFactory factory;

    int xPos;
    int yPos;
    float xOffset;
    float yOffset;

};

#endif // BOARDMODEL_H
