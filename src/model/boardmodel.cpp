#include "boardmodel.h"

#include <QDebug>

BoardModel::BoardModel()
{

}

void BoardModel::load(std::string loadInfo)
{
    factory.populate(&boardObjects, loadInfo);
}

std::vector<BoardObjectAbstract *> *BoardModel::getObjects()
{
    return &boardObjects;
}

