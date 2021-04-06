#include "renderingstrategypausemenu.h"

#include "../model/modelabstract.h"

RenderingStrategyPauseMenu::RenderingStrategyPauseMenu(ModelAbstract *model)
    : RenderingStrategy(model)
{

}

void RenderingStrategyPauseMenu::draw(std::vector<DrawInformation> *items, float *xOffset, float *yOffset)
{
    xOffset = 0;
    yOffset = 0;
    model->drawPauseMenu(items);
}
