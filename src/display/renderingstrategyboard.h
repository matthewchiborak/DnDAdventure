#ifndef RENDERINGSTRATEGYBOARD_H
#define RENDERINGSTRATEGYBOARD_H

#include "renderingstrategy.h"

class RenderingStrategyBoard : public RenderingStrategy
{
public:
    RenderingStrategyBoard(ModelAbstract * model);

    void draw(std::vector<DrawInformation> * items, float *xOffset, float *yOffset);

};

#endif // RENDERINGSTRATEGYBOARD_H
