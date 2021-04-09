#include "drawinformation.h"

DrawInformation::DrawInformation(int x, int y, int w, int h, std::string key, bool worldRel, std::string text, bool isLeftAlign, float fontSize, int r, int g, int b)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->key = key;
    this->isRelativeToWorld = worldRel;
    this->text = text;
    this->fontSize = fontSize;
    this->isLeftAlign = isLeftAlign;
    this->r = r;
    this->g = g;
    this->b = b;
}
