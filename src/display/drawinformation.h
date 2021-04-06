#ifndef DRAWINFORMATION_H
#define DRAWINFORMATION_H

#include <iostream>

class DrawInformation
{
public:
    DrawInformation(int x, int y, int w, int h, std::string key, bool worldRel);

    int x;
    int y;
    int w;
    int h;
    std::string key;
    bool isRelativeToWorld; //false means to screen
};

#endif // DRAWINFORMATION_H
