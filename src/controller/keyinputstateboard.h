#ifndef KEYINPUTSTATEBOARD_H
#define KEYINPUTSTATEBOARD_H

#include "keyinputstate.h"
#include <chrono>

class KeyInputStateBoard : public KeyInputState
{
public:
    KeyInputStateBoard(ModelAbstract * model, std::queue<int> * keyboardEventQueue);
    ~KeyInputStateBoard();

    bool handle(std::string * nextState);

private:
    bool eventBeenSetUp;

    float movementLockTimeMil;
    long long theTimeNow;
    long long timeOfLastButtonEvent;
    double elapsed_millies;

    bool handleUserInput(std::string * nextState);
    bool handleCollisionTriggers(std::string * nextState);
};

#endif // KEYINPUTSTATEBOARD_H
