#include "battlemenustateattack.h"

#include "battlemenustatemain.h"
#include "../display/drawinformation.h"
#include "../model/playercharacterstats.h"
#include "../model/battlemodel.h"
#include "../model/attackmodel.h"
#include "battlemenustatetimeflow.h"

BattleMenuStateAttack::BattleMenuStateAttack(BattleModel *model)
    : BattleMenuState(model)
{

}

void BattleMenuStateAttack::moveMenuCursor(int x, int y)
{    
    int potX = currentPosX + x;
    int potY = currentPosY - y;

    if(potX > 2)
        potX = 0;
    if(potX < 0)
        potX = 2;

    if(potY > 4)
        potY = 0;
    if(potY < 0)
        potY = 4;

    if((((potX) * 5) + (potY)) >= model->getCharacters()->at(0)->getAttacks()->size())
        return;

    currentPosX = potX;
    currentPosY = potY;

//    currentPosX += x;
//    currentPosY -= y;

//    if(currentPosX > 2)
//        currentPosX = 0;
//    if(currentPosX < 0)
//        currentPosX = 2;

//    if(currentPosY > 4)
//        currentPosY = 0;
//    if(currentPosY < 0)
//        currentPosY = 4;
}

BattleMenuState *BattleMenuStateAttack::enterMenu()
{
    return new BattleMenuStateTimeFlow(model);
}

BattleMenuState *BattleMenuStateAttack::closeMenu()
{
    return new BattleMenuStateMain(model);
}

BattleMenuState *BattleMenuStateAttack::passTime(float value)
{
    return this;
}

void BattleMenuStateAttack::drawBattleMenu(std::vector<DrawInformation> *items)
{
    //Top Text Box
    DrawInformation topTextBox(-700, 350, 1500, 140, "BattleMenuBG", false);
    items->push_back(topTextBox);

    for(int i = 0; i < model->getCharacters()->at(0)->getAttacks()->size(); i++)
    {
        DrawInformation attack1(435 + ((i/5) * 400), (630 + ((i%5) * 50)), 400, 75, "",
                                false, model->getCharacters()->at(0)->getAttacks()->at(i)->getName()
                                + model->getCharacters()->at(0)->getAttacks()->at(i)->getMPCostString()
                                , true, 36);
        items->push_back(attack1);
    }

//    DrawInformation attack1(435, 630, 300, 75, "",
//                            false, model->getCharacters()->at(0)->getAttacks()->at(0)->getName(), true, 36);
//    items->push_back(attack1);

//    DrawInformation attack2(435, 680, 300, 75, "",
//                            false, model->getCharacters()->at(0)->getAttacks()->at(1)->getName(), true, 36);
//    items->push_back(attack2);

//    DrawInformation attack3(435, 730, 300, 75, "",
//                            false, model->getCharacters()->at(0)->getAttacks()->at(2)->getName(), true, 36);
//    items->push_back(attack3);

//    DrawInformation attack4(435, 780, 300, 75, "",
//                            false, model->getCharacters()->at(0)->getAttacks()->at(3)->getName(), true, 36);
//    items->push_back(attack4);

//    DrawInformation attack6(435, 830, 300, 75, "",
//                            false, model->getCharacters()->at(0)->getAttacks()->at(4)->getName(), true, 36);
//    items->push_back(attack6);

//    DrawInformation attack5(835, 680, 300, 75, "",
//                            false, model->getCharacters()->at(0)->getAttacks()->at(5)->getName(), true, 36);
//    items->push_back(attack5);

//    DrawInformation attack7(1235, 630, 300, 75, "",
//                            false, model->getCharacters()->at(0)->getAttacks()->at(6)->getName(), true, 36);
//    items->push_back(attack7);

    //Text
    DrawInformation mainCursor(405 + (currentPosX * 400), 630 + ((currentPosY) * 50), 75, 75, "", false, ">", true, 36);
    items->push_back(mainCursor);

    //Currently selected attack
    DrawInformation attackDesc(0, 10, 1500, 140, "",
                            false, model->getCharacters()->at(0)->getAttacks()->at(
                                   ((currentPosX * 5) + currentPosY)
                                   )->getDescription());
    items->push_back(attackDesc);
}
