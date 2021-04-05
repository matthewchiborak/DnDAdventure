#include "modelconcrete.h"
#include <QDebug>

ModelConcrete::ModelConcrete(SpriteFlyweightFactoryAbstract * factory)
    : ModelAbstract(spriteFactory)
{

}

void ModelConcrete::drawBoardModel(QPainter *p)
{
    qDebug() << "Drawing Board Model";
    boardModel.draw(p);
}

void ModelConcrete::loadBoardModel(std::string loadInfo)
{
    qDebug() << "Loading Board Model";
    boardModel.load(loadInfo);
}

