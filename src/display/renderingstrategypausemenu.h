#ifndef RENDERINGSTRATEGYPAUSEMENU_H
#define RENDERINGSTRATEGYPAUSEMENU_H

#include "renderingstrategy.h"

class RenderingStrategyPauseMenu : public RenderingStrategy
{
public:
    RenderingStrategyPauseMenu(ModelAbstract * model);

    void draw(std::vector<DrawInformation> * items, float *xOffset, float *yOffset);
};

#endif // RENDERINGSTRATEGYPAUSEMENU_H
