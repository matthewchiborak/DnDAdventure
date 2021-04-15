#ifndef KEYINPUTSTATECUTSCENE_H
#define KEYINPUTSTATECUTSCENE_H

#include "keyinputstate.h"

class KeyInputStateCutscene : public KeyInputState
{
public:
    KeyInputStateCutscene(ModelAbstract * model, std::queue<int> * keyboardEventQueue, std::vector<bool> * movementKeys);
    ~KeyInputStateCutscene();

    bool handle(std::string * nextState);

};

#endif // KEYINPUTSTATECUTSCENE_H
