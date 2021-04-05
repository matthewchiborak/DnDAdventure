#ifndef MODELABSTRACT_H
#define MODELABSTRACT_H

#include "boardmodel.h"
#include "../display/spriteflyweightfactoryabstract.h"

class DrawInformation;

class ModelAbstract
{
public:
    ModelAbstract();
    virtual void drawBoardModel(std::vector<DrawInformation> * items);
    virtual void loadBoardModel(std::string loadInfo);

protected:
    BoardModel boardModel;
};

#endif // MODELABSTRACT_H
