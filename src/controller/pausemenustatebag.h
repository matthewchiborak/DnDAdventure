#ifndef PAUSEMENUSTATEBAG_H
#define PAUSEMENUSTATEBAG_H

#include "pausemenustate.h"

class PauseMenuStateBag : public PauseMenuDrawState
{
public:
    PauseMenuStateBag(ModelAbstract * model);

    void moveMenuCursor(int x, int y);
    PauseMenuDrawState * enterMenu();
    PauseMenuDrawState * closeMenu();
    void drawPauseMenu(std::vector<DrawInformation> * items);

    bool isMain();

    void speicalMessage(std::string message);

private:
    int cursorPos = 0;

    std::vector<int> equippedItems;
};

#endif // PAUSEMENUSTATEBAG_H
