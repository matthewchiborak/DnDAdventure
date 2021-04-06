#ifndef DRAWINFORMATION_H
#define DRAWINFORMATION_H

#include <iostream>

class DrawInformation
{
public:
    DrawInformation(int x, int y, int w, int h, std::string key, bool worldRel, std::string text = "");

    int x;
    int y;
    int w;
    int h;
    std::string key;
    bool isRelativeToWorld; //false means to screen
    std::string text;
};

#endif // DRAWINFORMATION_H
