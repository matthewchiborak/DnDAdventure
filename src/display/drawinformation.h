#ifndef DRAWINFORMATION_H
#define DRAWINFORMATION_H

#include <iostream>

class DrawInformation
{
public:
    DrawInformation(int x, int y, int w, int h, std::string key);

    int x;
    int y;
    int w;
    int h;
    std::string key;
};

#endif // DRAWINFORMATION_H
