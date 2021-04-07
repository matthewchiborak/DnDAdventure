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
    void clear();

    std::vector<BoardObjectAbstract*> * getObjects();

    void movePlayer(int x, int y, float t);

    float getXOffset();
    float getYOffset();
    int getXPos();
    int getYPos();

    void checkAndActivateDoor();

    bool tryToGetAnEnounter(std::string * keyToReturn);

    std::string getBattleBackgroundKey();

private:
    std::vector<BoardObjectAbstract*> boardObjects;
    std::vector<Doorway*> doors;
    BoardObjectFactory factory;

    std::vector<std::string> encounterTable;
    std::string battleBackgroundKey;

    int xPos;
    int yPos;
    float xOffset;
    float yOffset;

    bool playerCanMoveThisWay(int x, int y);
};

#endif // BOARDMODEL_H
