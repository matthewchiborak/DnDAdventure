#include "renderingstrategy.h"

RenderingStrategy::RenderingStrategy(ModelAbstract *model)
{
    this->model = model;
}

void RenderingStrategy::draw(std::vector<DrawInformation> * items, float *xOffset, float *yOffset)
{

}
