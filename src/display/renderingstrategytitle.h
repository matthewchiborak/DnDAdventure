#ifndef RENDERINGSTRATEGYTITLE_H
#define RENDERINGSTRATEGYTITLE_H

#include "renderingstrategy.h"

class RenderingStrategyTitle : public RenderingStrategy
{
public:
    RenderingStrategyTitle(ModelAbstract * model);
    void draw(std::vector<DrawInformation> * items, float *xOffset, float *yOffset);
};

#endif // RENDERINGSTRATEGYTITLE_H
