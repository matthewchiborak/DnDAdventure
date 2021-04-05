#ifndef MODELCONCRETE_H
#define MODELCONCRETE_H

#include "modelabstract.h"

class ModelConcrete : public ModelAbstract
{
public:
    ModelConcrete(SpriteFlyweightFactoryAbstract * factory);
    void drawBoardModel(QPainter *p);
    void loadBoardModel(std::string loadInfo);
};

#endif // MODELCONCRETE_H
