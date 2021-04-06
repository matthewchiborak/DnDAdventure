#ifndef RENDERINGSTRATEGYBOARD_H
#define RENDERINGSTRATEGYBOARD_H

#include <QBrush>

#include "renderingstrategy.h"

class RenderingStrategyBoard : public RenderingStrategy
{
public:
    RenderingStrategyBoard(ModelAbstract * model);

    void draw(std::vector<DrawInformation> * items, float *xOffset, float *yOffset);

private:
    QBrush clearColorBrush;
};

#endif // RENDERINGSTRATEGYBOARD_H
