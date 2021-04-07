#ifndef PAUSEMENUSTATEMAIN_H
#define PAUSEMENUSTATEMAIN_H

#include "pausemenustate.h"

class PauseMenuStateMain : public PauseMenuDrawState
{
public:
    PauseMenuStateMain(ModelAbstract * model);

    void moveMenuCursor(int x, int y);
    PauseMenuDrawState * enterMenu();
    PauseMenuDrawState * closeMenu();
    void drawPauseMenu(std::vector<DrawInformation> * items);

private:
    int currentPos = 4;
};

#endif // PAUSEMENUSTATEMAIN_H
