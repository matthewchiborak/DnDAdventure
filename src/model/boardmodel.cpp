#include "boardmodel.h"

#include <QDebug>

BoardModel::BoardModel()
{

}

void BoardModel::draw(QPainter *p)
{
    qDebug() << "Board Model Draw";
}

void BoardModel::load(std::string loadInfo)
{
    factory.populate(&boardObjects, loadInfo);
}
