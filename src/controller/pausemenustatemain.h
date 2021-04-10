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


    bool isMain();

    void speicalMessage(std::string message);

private:
    int currentPos = 5;
};

#endif // PAUSEMENUSTATEMAIN_H
