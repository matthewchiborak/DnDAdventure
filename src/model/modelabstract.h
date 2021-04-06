#ifndef MODELABSTRACT_H
#define MODELABSTRACT_H

#include "boardmodel.h"
#include "../display/spriteflyweightfactoryabstract.h"

class DrawInformation;

class ModelAbstract
{
public:
    ModelAbstract();
    virtual void drawBoardModel(std::vector<DrawInformation> * items, float *xOffset, float *yOffset);
    virtual void loadBoardModel(std::string loadInfo);

    virtual void movePlayer(int x, int y, float t);
};

#endif // MODELABSTRACT_H
