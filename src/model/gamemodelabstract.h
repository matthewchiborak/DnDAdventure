#ifndef GAMEMODELABSTRACT_H
#define GAMEMODELABSTRACT_H

#include <iostream>

class QPainter;

//This feels redundant. TODO review
class GameModelAbstract
{
public:
    GameModelAbstract();

    void draw(QPainter *p);
    void load(std::string loadInfo);
};

#endif // GAMEMODELABSTRACT_H
