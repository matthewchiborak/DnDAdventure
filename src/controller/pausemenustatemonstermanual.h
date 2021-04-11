#ifndef PAUSEMENUSTATEMONSTERMANUAL_H
#define PAUSEMENUSTATEMONSTERMANUAL_H

#include "pausemenustate.h"

class EnemyModel;

class PauseMenuStateMonsterManual : public PauseMenuDrawState
{
public:
    PauseMenuStateMonsterManual(ModelAbstract * model);

    void moveMenuCursor(int x, int y);
    PauseMenuDrawState * enterMenu();
    PauseMenuDrawState * closeMenu();
    void drawPauseMenu(std::vector<DrawInformation> * items);

    bool isMain();

    void speicalMessage(std::string message);

private:
    int cursorPos = 0;
    std::vector<std::string> names;
    std::vector<bool> defeats;
    std::vector<std::string> keys;

    EnemyModel * focusEnemy;
    bool displayingFocusEnemy = false;
};

#endif // PAUSEMENUSTATEMONSTERMANUAL_H
