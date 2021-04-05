#ifndef RENDERINGSTRATEGYBOARD_H
#define RENDERINGSTRATEGYBOARD_H

#include <QBrush>

#include "renderingstrategy.h"

class RenderingStrategyBoard : public RenderingStrategy
{
public:
    RenderingStrategyBoard(ModelAbstract * model);

    void draw(QPainter * p);

private:
    QBrush clearColorBrush;
};

#endif // RENDERINGSTRATEGYBOARD_H
