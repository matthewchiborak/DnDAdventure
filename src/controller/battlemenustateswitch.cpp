#include "battlemenustateswitch.h"

#include "battlemenustatemain.h"
#include "battlemenustatetimeflow.h"

#include <iostream>
#include "../display/drawinformation.h"
#include "../model/battlemodel.h"
#include "../model/playercharacterstats.h"
#include "../model/playercharacterstatsbattle.h"
#include "battlemenustatemain.h"

BattleMenuStateSwitch::BattleMenuStateSwitch(BattleModel *model)
    : BattleMenuState(model)
{

}

void BattleMenuStateSwitch::moveMenuCursor(int x, int y)
{
    currentPos += x;

    if(currentPos < 0)
        currentPos = 1;
    if(currentPos > 1)
        currentPos = 0;
}

BattleMenuState *BattleMenuStateSwitch::enterMenu()
{
    //Can't make it so you swap in dead characters if other party member is dead
    if(model->getCharacters()->at(2 + currentPos)->getCurrentHealth() <= 0)
    {
        return this;
    }

    PlayerCharacterStatsBattle * temp1 = model->getCharacters()->at(model->getFocusPartyMember());
    PlayerCharacterStatsBattle * temp2 = model->getCharacters()->at(2 + currentPos);
    model->getCharacters()->at(model->getFocusPartyMember()) = temp2;
    model->getCharacters()->at(2 + currentPos) = temp1;

    return new BattleMenuStateMain(model);
}

BattleMenuState *BattleMenuStateSwitch::closeMenu()
{
    return new BattleMenuStateMain(model);
}

BattleMenuState *BattleMenuStateSwitch::passTime(float value)
{
    return this;
}

void BattleMenuStateSwitch::drawBattleMenu(std::vector<DrawInformation> *items)
{
    //Character portraits
    //images first
    DrawInformation port1(-300, -275, 150, 150, model->getCharacters()->at(2)->getMenuSpriteKey(), false);
    items->push_back(port1);
    DrawInformation port2(250, -275, 150, 150, model->getCharacters()->at(3)->getMenuSpriteKey(), false);
    items->push_back(port2);

    //Default menu text
    DrawInformation p1Name(625, 620, 300, 75, "", false, model->getCharacters()->at(2)->getName(), true);
    items->push_back(p1Name);
    DrawInformation p1hp(625, 670, 300, 75, "", false,
                         "HP: " + std::to_string(model->getCharacters()->at(2)->getCurrentHealth()) + "/"
                         + std::to_string(model->getCharacters()->at(2)->getMaxHealth())
                         , true);
    items->push_back(p1hp);
    DrawInformation p1mp(625, 720, 300, 75, "", false,
                         "MP: " + std::to_string(model->getCharacters()->at(2)->getCurrentMP()) + "/"
                         + std::to_string(model->getCharacters()->at(2)->getMaxMP())
                         , true);
    items->push_back(p1mp);
    DrawInformation p2Name(625 + 550, 620, 300, 75, "", false, model->getCharacters()->at(3)->getName(), true);
    items->push_back(p2Name);
    DrawInformation p2hp(625 + 550, 670, 300, 75, "", false,
                         "HP: " + std::to_string(model->getCharacters()->at(3)->getCurrentHealth()) + "/"
                         + std::to_string(model->getCharacters()->at(3)->getMaxHealth())
                         , true);
    items->push_back(p2hp);
    DrawInformation p2mp(625 + 550, 720, 300, 75, "", false,
                         "MP: " + std::to_string(model->getCharacters()->at(3)->getCurrentMP()) + "/"
                         + std::to_string(model->getCharacters()->at(3)->getMaxMP())
                         , true);
    items->push_back(p2mp);

    DrawInformation mainCursor(425 + (550 * currentPos), 635, 75, 75, "", false, ">", true);
    items->push_back(mainCursor);
}

BattleMenuState *BattleMenuStateSwitch::qrPressed(bool wasQ)
{
    return this;
}
