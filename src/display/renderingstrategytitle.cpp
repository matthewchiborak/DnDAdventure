#include "renderingstrategytitle.h"

RenderingStrategyTitle::RenderingStrategyTitle(ModelAbstract *model)
    : RenderingStrategy(model)
{

}

void RenderingStrategyTitle::draw(std::vector<DrawInformation> *items, float *xOffset, float *yOffset)
{
    (*xOffset) = 0;
    (*yOffset) = 0;
    model->drawTitleScreen(items);
}
