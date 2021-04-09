#include "aboveheadbattlemessage.h"

#include "QDebug"

AboveHeadBattleMessage::AboveHeadBattleMessage(int duration, int x, int y, int w, int h, std::string key, bool worldRel, std::string text, bool isLeftAlign, float fontSize, int r, int g, int b)
    : DrawInformation(x, y, w, h, key, worldRel, text, isLeftAlign, fontSize, r, g, b)
{
    this->duration = duration;

    auto nowTime = std::chrono::system_clock::now().time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime).count();
    theTimeNow =(millis);
    timeOfLastEvent = (millis);
}

bool AboveHeadBattleMessage::applyTime()
{
    auto nowTime = std::chrono::system_clock::now().time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime).count();
    theTimeNow =(millis);
    elapsed_millies = theTimeNow - timeOfLastEvent;

    if(elapsed_millies > duration)
        return true;

    return false;
}
