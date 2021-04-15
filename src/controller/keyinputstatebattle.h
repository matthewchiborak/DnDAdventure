#ifndef KEYINPUTSTATEBATTLE_H
#define KEYINPUTSTATEBATTLE_H

#include "keyinputstate.h"

class KeyInputStateBattle : public KeyInputState
{
public:
    KeyInputStateBattle(ModelAbstract * model, std::queue<int> * keyboardEventQueue, std::vector<bool> * movementKeys);
    ~KeyInputStateBattle();

    bool handle(std::string * nextState);

private:
    bool handleUserInput(std::string * nextState);
};

#endif // KEYINPUTSTATEBATTLE_H
