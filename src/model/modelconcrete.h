#ifndef MODELCONCRETE_H
#define MODELCONCRETE_H

#include "modelabstract.h"

class ModelConcrete : public ModelAbstract
{
public:
    ModelConcrete();
    void drawBoardModel(std::vector<DrawInformation> * items);
    void loadBoardModel(std::string loadInfo);
};

#endif // MODELCONCRETE_H
