#ifndef PAUSEMENUSTATEPARTY_H
#define PAUSEMENUSTATEPARTY_H

#include "pausemenustate.h"

class PauseMenuStateParty : public PauseMenuDrawState
{
public:
    PauseMenuStateParty(ModelAbstract * model);

    void moveMenuCursor(int x, int y);
    PauseMenuDrawState * enterMenu();
    PauseMenuDrawState * closeMenu();
    void drawPauseMenu(std::vector<DrawInformation> * items);

private:
    int currentPos = 0;
};

#endif // PAUSEMENUSTATEPARTY_H
