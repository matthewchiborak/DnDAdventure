#include "battlemenustatemain.h"

#include "../display/drawinformation.h"
#include "../model/battlemodel.h"
#include "../model/playercharacterstats.h"
#include "battlemenustateswitch.h"
#include "battlemenustateattack.h"
#include "battlemenustatetimeflow.h"
#include "battlemenustatespecial.h"

BattleMenuStateMain::BattleMenuStateMain(BattleModel *model)
    : BattleMenuState(model)
{

}

void BattleMenuStateMain::moveMenuCursor(int x, int y)
{
    currentPos += y;

    if(currentPos > 4)
        currentPos = 0;
    if(currentPos < 0)
        currentPos = 4;
}

BattleMenuState *BattleMenuStateMain::enterMenu()
{
    if(currentPos == 4)
        return new BattleMenuStateAttack(model);
    if(currentPos == 3)
        return new BattleMenuStateTimeFlow(model);
    if(currentPos == 2)
        return new BattleMenuStateSpecial(model);
    if(currentPos == 1)
        return new BattleMenuStateSwitch(model);
    if(currentPos == 0)
        return new BattleMenuStateTimeFlow(model);

    return this;
}

BattleMenuState *BattleMenuStateMain::closeMenu()
{
    return this;
}

BattleMenuState *BattleMenuStateMain::passTime(float value)
{
    return this;
}

void BattleMenuStateMain::drawBattleMenu(std::vector<DrawInformation> *items)
{
    //Character portraits
    //images first
    DrawInformation port1(-300, -275, 150, 150, model->getCharacters()->at(0)->getMenuSpriteKey(), false);
    items->push_back(port1);
    DrawInformation port2(250, -275, 150, 150, model->getCharacters()->at(1)->getMenuSpriteKey(), false);
    items->push_back(port2);

    //Default menu text
    DrawInformation p1Name(625, 620, 300, 75, "", false, model->getCharacters()->at(0)->getName(), true);
    items->push_back(p1Name);
    DrawInformation p1hp(625, 670, 300, 75, "", false,
                         "HP: " + std::to_string(model->getCharacters()->at(0)->getCurrentHealth()) + "/"
                         + std::to_string(model->getCharacters()->at(0)->getMaxHealth())
                         , true);
    items->push_back(p1hp);
    DrawInformation p1mp(625, 720, 300, 75, "", false,
                         "MP: " + std::to_string(model->getCharacters()->at(0)->getCurrentMP()) + "/"
                         + std::to_string(model->getCharacters()->at(0)->getMaxMP())
                         , true);
    items->push_back(p1mp);
    DrawInformation p2Name(625 + 550, 620, 300, 75, "", false, model->getCharacters()->at(1)->getName(), true);
    items->push_back(p2Name);
    DrawInformation p2hp(625 + 550, 670, 300, 75, "", false,
                         "HP: " + std::to_string(model->getCharacters()->at(1)->getCurrentHealth()) + "/"
                         + std::to_string(model->getCharacters()->at(1)->getMaxHealth())
                         , true);
    items->push_back(p2hp);
    DrawInformation p2mp(625 + 550, 720, 300, 75, "", false,
                         "MP: " + std::to_string(model->getCharacters()->at(1)->getCurrentMP()) + "/"
                         + std::to_string(model->getCharacters()->at(1)->getMaxMP())
                         , true);
    items->push_back(p2mp);

    DrawInformation mainCursor(50, 637 + ((4 - currentPos) * 50), 75, 75, "", false, ">", true, 36);
    items->push_back(mainCursor);
}
