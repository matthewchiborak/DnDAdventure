#ifndef PAUSEMENUSTATESKILLS_H
#define PAUSEMENUSTATESKILLS_H

#include "pausemenustate.h"

class PauseMenuStateSkills : public PauseMenuDrawState
{
public:
    PauseMenuStateSkills(ModelAbstract * model);

    void moveMenuCursor(int x, int y);
    PauseMenuDrawState * enterMenu();
    PauseMenuDrawState * closeMenu();
    void drawPauseMenu(std::vector<DrawInformation> * items);

    bool isMain();

    void speicalMessage(std::string message);

private:
    int cursorPos = 0; //0-14
    int pagePos = 0; //0-3 for each character
};

#endif // PAUSEMENUSTATESKILLS_H
