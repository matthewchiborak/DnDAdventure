#include "battlemenustateitem.h"

#include "../model/battlemodel.h"
#include "battlemenustatemain.h"
#include "battlemenustatetimeflow.h"

BattleMenuStateItem::BattleMenuStateItem(BattleModel *model)
    : BattleMenuState(model)
{
    model->forceClearDisplayMessage();
}

void BattleMenuStateItem::moveMenuCursor(int x, int y)
{
    currentPos -=y;

    if(currentPos < 0)
        currentPos = 3;
    if(currentPos > 3)
        currentPos = 0;
}

BattleMenuState *BattleMenuStateItem::enterMenu()
{
    if(currentPos == 0)
    {
        if(model->getNumberOfPotions() > 0)
        {
            model->useAPotion();
            return new BattleMenuStateTimeFlow(model);
        }
    }
    if(currentPos == 1)
    {
        if(model->getNumberOfRemedies() > 0)
        {
            model->useARemedy();
            return new BattleMenuStateTimeFlow(model);
        }
    }
    if(currentPos == 2)
    {
        if(model->getNumberOfEthers() > 0)
        {
            model->useAEther();
            return new BattleMenuStateTimeFlow(model);
        }
    }
    if(currentPos == 3)
    {
        if(model->getNumberOfJars() > 0)
        {
            model->useAJar();
            return new BattleMenuStateTimeFlow(model);
        }
    }

    return this;
}

BattleMenuState *BattleMenuStateItem::closeMenu()
{
    return new BattleMenuStateMain(model);
}

BattleMenuState *BattleMenuStateItem::passTime(float value)
{
    return this;
}

void BattleMenuStateItem::drawBattleMenu(std::vector<DrawInformation> *items)
{
    //Top Text Box
    DrawInformation topTextBox(-700, 350, 1500, 140, "BattleMenuBG", false);
    items->push_back(topTextBox);

    //Text
    DrawInformation accessText(435, (630 + ((0) * 50)), 400, 75, "",
                            false, "Potion x" + std::to_string(model->getNumberOfPotions())
                            , true, 36);
    items->push_back(accessText);
    DrawInformation rezText(435, (630 + ((1) * 50)), 400, 75, "",
                            false, "Remedy x" + std::to_string(model->getNumberOfRemedies())
                            , true, 36);
    items->push_back(rezText);
    DrawInformation etherText(435, (630 + ((2) * 50)), 400, 75, "",
                            false, "Ether x" + std::to_string(model->getNumberOfEthers())
                            , true, 36);
    items->push_back(etherText);
    DrawInformation jarText(435, (630 + ((3) * 50)), 400, 75, "",
                            false, "Pickle Jars x" + std::to_string(model->getNumberOfJars())
                            , true, 36);
    items->push_back(jarText);

    if(currentPos == 0)
    {
        DrawInformation attackDesc(0, 10, 1500, 140, "",
                                false,
                                   "Instantly heal all party members for 50 HP"
                                   );
        items->push_back(attackDesc);
    }
    else if(currentPos == 1)
    {
        DrawInformation attackDesc(0, 10, 1500, 140, "",
                                false,
                                   "Instantly cure all party member status ailments"
                                   );
        items->push_back(attackDesc);
    }
    else if(currentPos == 2)
    {
        DrawInformation attackDesc(0, 10, 1500, 140, "",
                                false,
                                   "Instantly restore 50 MP to all party members"
                                   );
        items->push_back(attackDesc);
    }
    else if(currentPos == 3)
    {
        DrawInformation attackDesc(0, 10, 1500, 140, "",
                                false,
                                   "Instantly fill the party gauge"
                                   );
        items->push_back(attackDesc);
    }

    DrawInformation mainCursor(405, 630 + ((currentPos) * 50), 75, 75, "", false, ">", true, 36);
    items->push_back(mainCursor);
}

BattleMenuState *BattleMenuStateItem::qrPressed(bool wasQ)
{
    return this;
}
