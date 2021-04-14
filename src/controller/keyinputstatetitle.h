#ifndef KEYINPUTSTATETITLE_H
#define KEYINPUTSTATETITLE_H

#include "keyinputstate.h"

class KeyInputStateTitle : public KeyInputState
{
public:
    KeyInputStateTitle(ModelAbstract * model, std::queue<int> * keyboardEventQueue);
    ~KeyInputStateTitle();

    bool handle(std::string * nextState);
};

#endif // KEYINPUTSTATETITLE_H
