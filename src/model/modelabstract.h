#ifndef MODELABSTRACT_H
#define MODELABSTRACT_H

#include "boardmodel.h"
#include "../display/spriteflyweightfactoryabstract.h"
#include "../model/playercharacterstats.h"

class DrawInformation;

class ModelAbstract
{
public:
    ModelAbstract();
    ~ModelAbstract();
    void addPlayerCharacter(PlayerCharacterStats* character);

    virtual void drawBoardModel(std::vector<DrawInformation> * items, float *xOffset, float *yOffset);
    virtual void loadBoardModel(std::string loadInfo);

    virtual void movePlayer(int x, int y, float t);

    std::vector<PlayerCharacterStats*> playerCharacters;
};

#endif // MODELABSTRACT_H
