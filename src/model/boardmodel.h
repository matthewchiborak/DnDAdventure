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

private:
    std::vector<BoardObjectAbstract*> boardObjects;
    BoardObjectFactory factory;
};

#endif // BOARDMODEL_H
