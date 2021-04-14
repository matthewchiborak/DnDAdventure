#ifndef RENDERINGSTRATEGYCUTSCENE_H
#define RENDERINGSTRATEGYCUTSCENE_H

#include "renderingstrategy.h"

class RenderingStrategyCutscene : public RenderingStrategy
{
public:
    RenderingStrategyCutscene(ModelAbstract * model);
    void draw(std::vector<DrawInformation> * items, float *xOffset, float *yOffset);
};

#endif // RENDERINGSTRATEGYCUTSCENE_H
