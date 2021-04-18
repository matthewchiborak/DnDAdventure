#ifndef KEYINPUTSTATESHOP_H
#define KEYINPUTSTATESHOP_H

#include "keyinputstate.h"

class KeyInputStateShop : public KeyInputState
{
public:
    KeyInputStateShop(ModelAbstract * model, std::queue<int> * keyboardEventQueue, std::vector<bool> * movementKeys);

    bool handle(std::string * nextState);

private:
    bool handleUserInput(std::string * nextState);
};

#endif // KEYINPUTSTATESHOP_H
