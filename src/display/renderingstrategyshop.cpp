#include "renderingstrategyshop.h"

RenderingStrategyShop::RenderingStrategyShop(ModelAbstract *model)
    : RenderingStrategy(model)
{

}

void RenderingStrategyShop::draw(std::vector<DrawInformation> *items, float *xOffset, float *yOffset)
{
    xOffset = 0;
    yOffset = 0;
    model->drawShop(items);
}
