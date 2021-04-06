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

    bool eventBeenSetUp;

    int keyToCheck;
    float movementLockTimeMil;
    long long theTimeNow;
    long long timeOfLastButtonEvent;
    double elapsed_millies;
    bool keepIncrLoop;
};

#endif // KEYINPUTSTATEBOARD_H
