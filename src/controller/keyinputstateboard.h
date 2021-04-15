#ifndef KEYINPUTSTATEBOARD_H
#define KEYINPUTSTATEBOARD_H

#include "keyinputstate.h"
#include <chrono>

class KeyInputStateBoard : public KeyInputState
{
public:
    KeyInputStateBoard(ModelAbstract * model, std::queue<int> * keyboardEventQueue, std::vector<bool> * movementKeys);
    ~KeyInputStateBoard();

    bool handle(std::string * nextState);

private:
    bool handleUserInput(std::string * nextState);
    bool handleMovement(std::string * nextState);
    bool handleCollisionTriggers(std::string * nextState);

    bool lockMovement[4];
    bool movementEventSetUp = false;

};

#endif // KEYINPUTSTATEBOARD_H
