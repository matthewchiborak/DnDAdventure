#ifndef DRAWINFORMATION_H
#define DRAWINFORMATION_H

#include <iostream>

class DrawInformation
{
public:
    DrawInformation(int x, int y, int w, int h, std::string key, bool worldRel, std::string text = "", bool isLeftAlign = false, float fontSize = 48.f,
            int r = 0, int g = 0, int b = 0
            );

    int x;
    int y;
    int w;
    int h;
    std::string key;
    bool isRelativeToWorld; //false means to screen
    std::string text;
    bool isLeftAlign;
    float fontSize;
    int r,g,b; //0-255
    bool flip = false;
};

#endif // DRAWINFORMATION_H
