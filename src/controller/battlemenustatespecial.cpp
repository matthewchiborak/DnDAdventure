#include "battlemenustatespecial.h"

#include "battlemenustatemain.h"
#include "battlemenustatetimeflow.h"
#include "../display/drawinformation.h"
#include "../model/battlemodel.h"
#include "../model/playercharacterstatsbattle.h"
#include "battlemenustateaccess.h"
#include "../model/EnemyModel.h"

BattleMenuStateSpecial::BattleMenuStateSpecial(BattleModel *model)
    : BattleMenuState(model)
{
    model->forceClearDisplayMessage();

    numOfCh = 0;
    for(int i = 0; i < model->getCharacters()->size(); i++)
        numOfCh++;
}

void BattleMenuStateSpecial::moveMenuCursor(int x, int y)
{
    if(isSelecting)
    {
        do
        {
            accessPos += y;

            if(accessPos >= model->getNumberOfEnemies())
                accessPos = 0;
            else if(accessPos < 0)
                accessPos = (model->getNumberOfEnemies()) - 1;

        }while(model->getEnemies()->at(accessPos)->getCurrentHealth() <= 0);

        return;
    }

    currentPos -= y;

    if(currentPos > (numOfCh-1))
        currentPos = 0;
    if(currentPos < 0)
        currentPos = (numOfCh-1);
}

BattleMenuState *BattleMenuStateSpecial::enterMenu()
{
    if(isSelecting)
    {
        model->changePartyGaugeValue(-250);
        model->setEnemyToAccess(accessPos);
        return new BattleMenuStateAccess(model);
        return this;
    }

    if(currentPos == 0)
    {
        //Access
        if(model->getPartyGaugeValue() >= 250)
        {
            isSelecting = true;
            return this;
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
    if(isSelecting)
    {
        isSelecting = false;
        return this;
    }

    return new BattleMenuStateMain(model);
}

BattleMenuState *BattleMenuStateSpecial::passTime(float value)
{
    return this;
}

void BattleMenuStateSpecial::drawBattleMenu(std::vector<DrawInformation> *items)
{
    //Top Text Box
    DrawInformation topTextBox(-700, 350, 1500, 140, "BattleMenuBG", false);
    items->push_back(topTextBox);

    if(isSelecting)
    {
        drawEnemyStatusEffect(items);

        int currentTarget = accessPos;

        if(currentTarget == 0)
        {
            DrawInformation en(700+300, 300+50-25, 75, 75, "", false, ">", true);
            //DrawInformation en(300, 50, 75, 75, "", false, ">", true);
            items->push_back(en);
        }
        else if(currentTarget == 1)
        {
            DrawInformation en(700+100, 200+200-25, 75, 75, "", false, ">", true);
            items->push_back(en);
        }
        else if(currentTarget == 2)
        {
            DrawInformation en(700+500, 200+200-25, 75, 75, "", false, ">", true);
            items->push_back(en);
        }
        else if(currentTarget == 3)
        {
            DrawInformation en(700+100, 200+0-25, 75, 75, "", false, ">", true);
            items->push_back(en);
        }
        else if(currentTarget == 4)
        {
            DrawInformation en(700+500, 200+0-25, 75, 75, "", false, ">", true);
            items->push_back(en);
        }

        DrawInformation attackDesc(0, 10, 1500, 140, "",
                                false,
                                   "[" + std::to_string(currentTarget+1) + "] " + model->getEnemies()->at(currentTarget)->getName()
                                   );
        items->push_back(attackDesc);
    }
    else
    {
        //Need top descriptions
        if(currentPos == 0)
        {
            DrawInformation attackDesc(0, 10, 1500, 140, "",
                                    false,
                                       "Reveal information about an enemy"
                                       );
            items->push_back(attackDesc);
        }
        else if(currentPos == 1)
        {
            DrawInformation attackDesc(0, 10, 1500, 140, "",
                                    false,
                                       "Revive all defeated allies"
                                       );
            items->push_back(attackDesc);
        }
        else if(currentPos == 2)
        {
            DrawInformation attackDesc(0, 10, 1500, 140, "",
                                    false,
                                       "Instantly deal massive damage to all enemies"
                                       );
            items->push_back(attackDesc);
        }
        else if(currentPos == 3)
        {
            DrawInformation attackDesc(0, 10, 1500, 140, "",
                                    false,
                                       "Massively increase attack, magic, and speed for 20 seconds"
                                       );
            items->push_back(attackDesc);
        }
    }

    DrawInformation accessText(435, (630 + ((0) * 50)), 400, 75, "",
                            false, "Access   (1 BAR)"
                            , true, 36);
    items->push_back(accessText);
    DrawInformation rezText(435, (630 + ((1) * 50)), 400, 75, "",
                            false, "Revive   (2 BAR)"
                            , true, 36);
    items->push_back(rezText);

    if(numOfCh > 2)
    {
        DrawInformation superText(435, (630 + ((2) * 50)), 400, 75, "",
                                false, "Super   (3 BAR)"
                                , true, 36);
        items->push_back(superText);
    }
    if(numOfCh > 3)
    {
        DrawInformation overdriveText(435, (630 + ((3) * 50)), 400, 75, "",
                                false, "Overdrive   (4 BAR)"
                                , true, 36);
        items->push_back(overdriveText);
    }

    DrawInformation mainCursor(405, 630 + ((currentPos) * 50), 75, 75, "", false, ">", true, 36);
    items->push_back(mainCursor);
}

BattleMenuState *BattleMenuStateSpecial::qrPressed(bool wasQ)
{
    return this;
}

void BattleMenuStateSpecial::drawEnemyStatusEffect(std::vector<DrawInformation> *items)
{
    int enemyStatusCount = 1;
    int currentTarget = accessPos;

    if(model->getEnemies()->at(currentTarget)->getStatusEffectModel()->SE_att > 0)
    {
        DrawInformation SEAttUp(-12 + (((enemyStatusCount%2) - (((enemyStatusCount+1)%2))) * 15*enemyStatusCount++), 360, 25, 25, "SEAttackUp", false);
        items->push_back(SEAttUp);
    }
    if(model->getEnemies()->at(currentTarget)->getStatusEffectModel()->SE_att < 0)
    {
        DrawInformation SEAttUp(-12 + (((enemyStatusCount%2) - (((enemyStatusCount+1)%2))) * 15*enemyStatusCount++), 360, 25, 25, "SEAttackDown", false);
        items->push_back(SEAttUp);
    }
    if(model->getEnemies()->at(currentTarget)->getStatusEffectModel()->SE_def > 0)
    {
        DrawInformation SEAttUp(-12 + (((enemyStatusCount%2) - (((enemyStatusCount+1)%2))) * 15*enemyStatusCount++), 360, 25, 25, "SEDefenceUp", false);
        items->push_back(SEAttUp);
    }
    if(model->getEnemies()->at(currentTarget)->getStatusEffectModel()->SE_def < 0)
    {
        DrawInformation SEAttUp(-12 + (((enemyStatusCount%2) - (((enemyStatusCount+1)%2))) * 15*enemyStatusCount++), 360, 25, 25, "SEDefenceDown", false);
        items->push_back(SEAttUp);
    }
    if(model->getEnemies()->at(currentTarget)->getStatusEffectModel()->SE_magic > 0)
    {
        DrawInformation SEAttUp(-12 + (((enemyStatusCount%2) - (((enemyStatusCount+1)%2))) * 15*enemyStatusCount++), 360, 25, 25, "SEMagicUp", false);
        items->push_back(SEAttUp);
    }
    if(model->getEnemies()->at(currentTarget)->getStatusEffectModel()->SE_magic < 0)
    {
        DrawInformation SEAttUp(-12 + (((enemyStatusCount%2) - (((enemyStatusCount+1)%2))) * 15*enemyStatusCount++), 360, 25, 25, "SEMagicDown", false);
        items->push_back(SEAttUp);
    }
    if(model->getEnemies()->at(currentTarget)->getStatusEffectModel()->SE_magicDef > 0)
    {
        DrawInformation SEAttUp(-12 + (((enemyStatusCount%2) - (((enemyStatusCount+1)%2))) * 15*enemyStatusCount++), 360, 25, 25, "SEMagicDefenceUp", false);
        items->push_back(SEAttUp);
    }
    if(model->getEnemies()->at(currentTarget)->getStatusEffectModel()->SE_magicDef < 0)
    {
        DrawInformation SEAttUp(-12 + (((enemyStatusCount%2) - (((enemyStatusCount+1)%2))) * 15*enemyStatusCount++), 360, 25, 25, "SEMagicDefenceDown", false);
        items->push_back(SEAttUp);
    }
    if(model->getEnemies()->at(currentTarget)->getStatusEffectModel()->SE_speed > 0)
    {
        DrawInformation SEAttUp(-12 + (((enemyStatusCount%2) - (((enemyStatusCount+1)%2))) * 15*enemyStatusCount++), 360, 25, 25, "SEHaste", false);
        items->push_back(SEAttUp);
    }
    if(model->getEnemies()->at(currentTarget)->getStatusEffectModel()->SE_speed < 0)
    {
        DrawInformation SEAttUp(-12 + (((enemyStatusCount%2) - (((enemyStatusCount+1)%2))) * 15*enemyStatusCount++), 360, 25, 25, "SESlow", false);
        items->push_back(SEAttUp);
    }
    /////////////////
    if(model->getEnemies()->at(currentTarget)->getStatusEffectModel()->poison)
    {
        DrawInformation SEAttUp(-12 + (((enemyStatusCount%2) - (((enemyStatusCount+1)%2))) * 15*enemyStatusCount++), 360, 25, 25, "SEPoison", false);
        items->push_back(SEAttUp);
    }
    if(model->getEnemies()->at(currentTarget)->getStatusEffectModel()->blind)
    {
        DrawInformation SEAttUp(-12 + (((enemyStatusCount%2) - (((enemyStatusCount+1)%2))) * 15*enemyStatusCount++), 360, 25, 25, "SEBlind", false);
        items->push_back(SEAttUp);
    }
    if(model->getEnemies()->at(currentTarget)->getStatusEffectModel()->sleep)
    {
        DrawInformation SEAttUp(-12 + (((enemyStatusCount%2) - (((enemyStatusCount+1)%2))) * 15*enemyStatusCount++), 360, 25, 25, "SESleep", false);
        items->push_back(SEAttUp);
    }
    if(model->getEnemies()->at(currentTarget)->getStatusEffectModel()->silenced)
    {
        DrawInformation SEAttUp(-12 + (((enemyStatusCount%2) - (((enemyStatusCount+1)%2))) * 15*enemyStatusCount++), 360, 25, 25, "SESilence", false);
        items->push_back(SEAttUp);
    }
}
