#include "renderingstrategycutscene.h"

RenderingStrategyCutscene::RenderingStrategyCutscene(ModelAbstract *model)
    : RenderingStrategy(model)
{

}

void RenderingStrategyCutscene::draw(std::vector<DrawInformation> *items, float *xOffset, float *yOffset)
{
    (*xOffset) = 0;
    (*yOffset) = 0;
    model->drawCutscene(items);
}
