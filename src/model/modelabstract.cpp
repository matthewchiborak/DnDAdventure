#include "modelabstract.h"

ModelAbstract::ModelAbstract(SpriteFlyweightFactoryAbstract *factory)
{
    this->spriteFactory = factory;
}

void ModelAbstract::drawBoardModel(QPainter *p)
{

}

void ModelAbstract::loadBoardModel(std::string loadInfo)
{

}

