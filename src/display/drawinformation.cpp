#include "drawinformation.h"

DrawInformation::DrawInformation(int x, int y, int w, int h, std::string key, bool worldRel, std::string text)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->key = key;
    this->isRelativeToWorld = worldRel;
    this->text = text;
}
