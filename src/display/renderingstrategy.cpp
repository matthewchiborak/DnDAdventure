#include "renderingstrategy.h"

RenderingStrategy::RenderingStrategy(ModelAbstract *model)
{
    this->model = model;
}

void RenderingStrategy::draw(QPainter *p)
{

}
