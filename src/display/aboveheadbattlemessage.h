#ifndef ABOVEHEADBATTLEMESSAGE_H
#define ABOVEHEADBATTLEMESSAGE_H

#include "drawinformation.h"

class AboveHeadBattleMessage : public DrawInformation
{
public:
    AboveHeadBattleMessage(int duration,
                           int x, int y, int w, int h, std::string key, bool worldRel, std::string text = "", bool isLeftAlign = false, float fontSize = 48.f,
                           int r = 0, int g = 0, int b = 0
                           );

    bool applyTime();

private:
    int duration;

    long long theTimeNow;
    long long timeOfLastEvent;
    double elapsed_millies;
};

#endif // ABOVEHEADBATTLEMESSAGE_H
