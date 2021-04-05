#ifndef MODELABSTRACT_H
#define MODELABSTRACT_H

#include "boardmodel.h"
#include "../display/spriteflyweightfactoryabstract.h"

class ModelAbstract
{
public:
    ModelAbstract(SpriteFlyweightFactoryAbstract * factory);
    void drawBoardModel(QPainter *p);
    void loadBoardModel(std::string loadInfo);

protected:
    BoardModel boardModel;
    SpriteFlyweightFactoryAbstract * spriteFactory;
};

#endif // MODELABSTRACT_H
