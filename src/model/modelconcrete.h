#ifndef MODELCONCRETE_H
#define MODELCONCRETE_H

#include "modelabstract.h"

class PauseMenuDrawState;

class ModelConcrete : public ModelAbstract
{
public:
    ModelConcrete();
    void drawBoardModel(std::vector<DrawInformation> * items, float *xOffset, float *yOffset);
    void loadBoardModel(std::string loadInfo);
    std::string handleBoardCollisionTriggers();
    void movePlayer(int x, int y, float t);

    //
    void drawPauseMenu(std::vector<DrawInformation> * items);
    void moveMenuCursor(int x, int y);
    void enterMenu();
    void closeMenu();

private:
    BoardModel boardModel;

    PauseMenuDrawState * currentMenuState;


};

#endif // MODELCONCRETE_H
