#ifndef RENDERINGSTRATEGY_H
#define RENDERINGSTRATEGY_H

#include "../model/modelabstract.h"

class RenderingStrategy
{
public:
    RenderingStrategy(ModelAbstract * model);

    void draw(QPainter * p);

protected:
    ModelAbstract * model;
};

#endif // RENDERINGSTRATEGY_H
