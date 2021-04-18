#ifndef RENDERINGSTRATEGYSHOP_H
#define RENDERINGSTRATEGYSHOP_H

#include "renderingstrategy.h"

class RenderingStrategyShop : public RenderingStrategy
{
public:
    RenderingStrategyShop(ModelAbstract * model);

    void draw(std::vector<DrawInformation> * items, float *xOffset, float *yOffset);
};

#endif // RENDERINGSTRATEGYSHOP_H
