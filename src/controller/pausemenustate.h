#ifndef PAUSEMENUDRAWSTRATEGY_H
#define PAUSEMENUDRAWSTRATEGY_H

class ModelAbstract;
class DrawInformation;

#include <vector>
#include <string>

class PauseMenuDrawState
{
public:
    PauseMenuDrawState(ModelAbstract * model);

    virtual void moveMenuCursor(int x, int y);
    virtual PauseMenuDrawState * enterMenu();
    virtual PauseMenuDrawState * closeMenu();
    virtual void drawPauseMenu(std::vector<DrawInformation> * items);

    virtual bool isMain();

    virtual void speicalMessage(std::string message);

protected:
    ModelAbstract * model;
};

#endif // PAUSEMENUDRAWSTRATEGY_H
