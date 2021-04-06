#ifndef MODELCONCRETE_H
#define MODELCONCRETE_H

#include "modelabstract.h"

class ModelConcrete : public ModelAbstract
{
public:
    ModelConcrete();
    void drawBoardModel(std::vector<DrawInformation> * items, float *xOffset, float *yOffset);
    void loadBoardModel(std::string loadInfo);

    void movePlayer(int x, int y, float t);

private:
    BoardModel boardModel;
};

#endif // MODELCONCRETE_H
