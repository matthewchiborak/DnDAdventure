#ifndef KEYINPUTSTATEPAUSEMENU_H
#define KEYINPUTSTATEPAUSEMENU_H

#include "keyinputstate.h"

class KeyInputStatePauseMenu : public KeyInputState
{
public:
    KeyInputStatePauseMenu(ModelAbstract * model, std::queue<int> * keyboardEventQueue);
    ~KeyInputStatePauseMenu();

    bool handle(std::string * nextState);

private:
    bool handleUserInput(std::string * nextState);
};

#endif // KEYINPUTSTATEPAUSEMENU_H
