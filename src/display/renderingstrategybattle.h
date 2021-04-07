#ifndef RENDERINGSTRATEGYBATTLE_H
#define RENDERINGSTRATEGYBATTLE_H

#include "renderingstrategy.h"

class RenderingStrategyBattle : public RenderingStrategy
{
public:
    RenderingStrategyBattle(ModelAbstract * model);
    void draw(std::vector<DrawInformation> * items, float *xOffset, float *yOffset);
};

#endif // RENDERINGSTRATEGYBATTLE_H
