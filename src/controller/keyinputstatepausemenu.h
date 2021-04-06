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
    bool eventBeenSetUp;

    float movementLockTimeMil;
    long long theTimeNow;
    long long timeOfLastButtonEvent;
    double elapsed_millies;

    bool handleUserInput(std::string * nextState);
};

#endif // KEYINPUTSTATEPAUSEMENU_H
