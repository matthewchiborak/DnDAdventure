#ifndef RENDERINGSTRATEGY_H
#define RENDERINGSTRATEGY_H

#include "../model/modelabstract.h"

class DrawInformation;

class RenderingStrategy
{
public:
    RenderingStrategy(ModelAbstract * model);

    virtual void draw(std::vector<DrawInformation> * items, float * xOffset, float * yOffset);

protected:
    ModelAbstract * model;
};

#endif // RENDERINGSTRATEGY_H
