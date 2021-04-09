#include "battlemenustatespecial.h"

#include "battlemenustatemain.h"
#include "battlemenustatetimeflow.h"
#include "../display/drawinformation.h"
#include "../model/battlemodel.h"
#include "../model/playercharacterstatsbattle.h"

BattleMenuStateSpecial::BattleMenuStateSpecial(BattleModel *model)
    : BattleMenuState(model)
{

}

void BattleMenuStateSpecial::moveMenuCursor(int x, int y)
{
    currentPos -= y;

    if(currentPos > 3)
        currentPos = 0;
    if(currentPos < 0)
        currentPos = 3;
}

BattleMenuState *BattleMenuStateSpecial::enterMenu()
{
    if(currentPos == 0)
    {
        //Access
        if(model->getPartyGaugeValue() >= 250)
        {
            model->changePartyGaugeValue(-250);
            return new BattleMenuStateTimeFlow(model);
        }
        else
        {
            return this;
        }
    }
    else if(currentPos == 1)
    {
        //Rez
        if(model->getPartyGaugeValue() >= 500)
        {
            model->changePartyGaugeValue(-500);

            for(int i = 0; i < model->getCharacters()->size(); i++)
            {
                if(model->getCharacters()->at(i)->getCurrentHealth() <= 0)
                {
                    model->getCharacters()->at(i)->setCurrentHealth(model->getCharacters()->at(i)->getMaxHealth()/2);
                }
            }

            return new BattleMenuStateTimeFlow(model);
        }
        else
        {
            return this;
        }
    }
    if(currentPos == 2)
    {
        //Super
        if(model->getPartyGaugeValue() >= 750)
        {
            model->changePartyGaugeValue(-750);

            //Cast an instant attack that does a lot of none damage
            model->activateSuper(model->getFocusPartyMember());

            return new BattleMenuStateTimeFlow(model);
        }
        else
        {
            return this;
        }
    }
    if(currentPos == 3)
    {
        //Overdrive
        if(model->getPartyGaugeValue() >= 1000)
        {
            model->changePartyGaugeValue(-1000);
            for(int i = 0; i < model->getCharacters()->size(); i++)
            {
                model->getCharacters()->at(i)->cureAllStatusEffects();
                model->getCharacters()->at(i)->applyStatusEffect("Overdrive");
            }
            return new BattleMenuStateTimeFlow(model);
        }
        else
        {
            return this;
        }
    }

    return new BattleMenuStateTimeFlow(model);
}

BattleMenuState *BattleMenuStateSpecial::closeMenu()
{
    return new BattleMenuStateMain(model);
}

BattleMenuState *BattleMenuStateSpecial::passTime(float value)
{
    return this;
}

void BattleMenuStateSpecial::drawBattleMenu(std::vector<DrawInformation> *items)
{
    DrawInformation accessText(435, (630 + ((0) * 50)), 400, 75, "",
                            false, "Access   (1 BAR)"
                            , true, 36);
    items->push_back(accessText);
    DrawInformation rezText(435, (630 + ((1) * 50)), 400, 75, "",
                            false, "Revive   (2 BAR)"
                            , true, 36);
    items->push_back(rezText);
    DrawInformation superText(435, (630 + ((2) * 50)), 400, 75, "",
                            false, "Super   (3 BAR)"
                            , true, 36);
    items->push_back(superText);
    DrawInformation overdriveText(435, (630 + ((3) * 50)), 400, 75, "",
                            false, "Overdrive   (4 BAR)"
                            , true, 36);
    items->push_back(overdriveText);

    DrawInformation mainCursor(405, 630 + ((currentPos) * 50), 75, 75, "", false, ">", true, 36);
    items->push_back(mainCursor);
}
