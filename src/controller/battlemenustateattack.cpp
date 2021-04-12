#include "battlemenustateattack.h"

#include "battlemenustatemain.h"
#include "../display/drawinformation.h"
#include "../model/playercharacterstats.h"
#include "../model/battlemodel.h"
#include "../model/attackmodel.h"
#include "battlemenustatetimeflow.h"
#include "../model/EnemyModel.h"
#include "../model/playercharacterstatsbattle.h"
#include <QDebug>

BattleMenuStateAttack::BattleMenuStateAttack(BattleModel *model)
    : BattleMenuState(model)
{
    currentTarget = 0;

    model->forceClearDisplayMessage();

    while(model->getEnemies()->at(currentTarget)->getCurrentHealth() <= 0)
    {
        currentTarget = (currentTarget+1)%model->getEnemies()->size();
    }
}

void BattleMenuStateAttack::moveMenuCursor(int x, int y)
{    
    if(!isSelectingTarget)
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

        if((((potX) * 5) + (potY)) >= model->getCharacters()->at(model->getFocusPartyMember())->getAttacks()->size())
            return;

        currentPosX = potX;
        currentPosY = potY;
    }
    else
    {        
        if(x < 0 || x > 0)
        {
            if(!currentTargetAllies)
            {
                currentTarget = 0;
                if(model->getCharacters()->at(0)->getCurrentHealth() <= 0)
                {
                    currentTarget = 1;
                }
                currentTargetAllies = true;
            }
            else
            {
                currentTarget = 0;
                while(model->getEnemies()->at(currentTarget)->getCurrentHealth() <= 0)
                {
                    currentTarget++;
                }

                currentTargetAllies = false;
            }
        }

        if(!currentTargetAllies)
        {
            do
            {
                currentTarget += y;

                if(currentTarget >= model->getNumberOfEnemies())
                    currentTarget = 0;
                else if(currentTarget < 0)
                    currentTarget = (model->getNumberOfEnemies()) - 1;

            }while(model->getEnemies()->at(currentTarget)->getCurrentHealth() <= 0);
        }
        else
        {
            currentTarget = (currentTarget+1)%2;
        }
    }
}

BattleMenuState *BattleMenuStateAttack::enterMenu()
{
    if(isSelectingTarget)
    {
        model->getCharacters()->at(model->getFocusPartyMember())->beginCasting(((currentPosX) * 5) + (currentPosY), currentTarget, currentTargetAllies);
        return new BattleMenuStateTimeFlow(model);
    }

    if(!model->getCharacters()->at(model->getFocusPartyMember())->getAttacks()->at(((currentPosX) * 5) + (currentPosY))->isUnlocked())
    {
        return this;
    }

    //Make sure not silenced
    if(model->getCharacters()->at(model->getFocusPartyMember())->getStatusEffectModel()->silenced)
    {
        if(model->getCharacters()->at(model->getFocusPartyMember())->getAttacks()->at(((currentPosX) * 5) + (currentPosY))->getMpcost() > 0)
        {
            return this;
        }
    }

    if(model->getCharacters()->at(model->getFocusPartyMember())->getAttacks()->at(((currentPosX) * 5) + (currentPosY))->getMpcost()
            > model->getCharacters()->at(model->getFocusPartyMember())->getCurrentMP())
    {
        return this;
    }

    if(model->getCharacters()->at(model->getFocusPartyMember())->getAttacks()->at(((currentPosX) * 5) + (currentPosY))->getMultitarget() == 1
            || model->getCharacters()->at(model->getFocusPartyMember())->getAttacks()->at(((currentPosX) * 5) + (currentPosY))->getMultitarget() == 2
            )
    {
        model->getCharacters()->at(model->getFocusPartyMember())->beginCasting(((currentPosX) * 5) + (currentPosY), currentTarget,
                              model->getCharacters()->at(model->getFocusPartyMember())->getAttacks()->at(((currentPosX) * 5) + (currentPosY))->getMultitarget() == 2
                                                                               );
        return new BattleMenuStateTimeFlow(model);
    }
    else if(model->getCharacters()->at(model->getFocusPartyMember())->getAttacks()->at(((currentPosX) * 5) + (currentPosY))->getMultitarget() == 3)
    {
        model->getCharacters()->at(model->getFocusPartyMember())->beginCasting(((currentPosX) * 5) + (currentPosY), model->getFocusPartyMember(), true);
        return new BattleMenuStateTimeFlow(model);
    }

    isSelectingTarget = true;

    return this;
}

BattleMenuState *BattleMenuStateAttack::closeMenu()
{
    if(!isSelectingTarget)
        return new BattleMenuStateMain(model);

    isSelectingTarget = false;

    return this;
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

    //Status effect iccons under the enemy name
    if(isSelectingTarget)
    {
        drawEnemyStatusEffect(items);
    }

    //Text
    for(int i = 0; i < model->getCharacters()->at(model->getFocusPartyMember())->getAttacks()->size(); i++)
    {
        if(model->getCharacters()->at(model->getFocusPartyMember())->getAttacks()->at(i)->isUnlocked())
        {
            DrawInformation attack1(435 + ((i/5) * 400), (630 + ((i%5) * 50)), 400, 75, "",
                                    false, model->getCharacters()->at(model->getFocusPartyMember())->getAttacks()->at(i)->getName()
                                    + model->getCharacters()->at(model->getFocusPartyMember())->getAttacks()->at(i)->getMPCostString()
                                    , true, 36);
            items->push_back(attack1);
        }
    }


    DrawInformation mainCursor(405 + (currentPosX * 400), 630 + ((currentPosY) * 50), 75, 75, "", false, ">", true, 36);
    items->push_back(mainCursor);

    if(isSelectingTarget)
    {
        if(!currentTargetAllies)
        {
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
            if(currentTarget == 0)
            {
                DrawInformation en(450, 250, 75, 75, "", false, ">", true);
                items->push_back(en);
            }
            else if(currentTarget == 1)
            {
                DrawInformation en(250, 350, 75, 75, "", false, ">", true);
                items->push_back(en);
            }

            DrawInformation attackDesc(0, 10, 1500, 140, "",
                                    false,
                                       model->getCharacters()->at(currentTarget)->getName()
                                       );
            items->push_back(attackDesc);
        }
    }

    //Currently selected attack
    if(!isSelectingTarget)
    {
        if(model->getCharacters()->at(model->getFocusPartyMember())->getAttacks()->at(
                    ((currentPosX * 5) + currentPosY)
                    )->isUnlocked())
        {
            DrawInformation attackDesc(0, 10, 1500, 140, "",
                                    false, model->getCharacters()->at(model->getFocusPartyMember())->getAttacks()->at(
                                           ((currentPosX * 5) + currentPosY)
                                           )->getDescription());
            items->push_back(attackDesc);
        }
    }
}

BattleMenuState *BattleMenuStateAttack::qrPressed(bool wasQ)
{
    return this;
}

void BattleMenuStateAttack::drawEnemyStatusEffect(std::vector<DrawInformation> *items)
{
    /*    DrawInformation topTextBox(-700, 350, 1500, 140, "BattleMenuBG", false);
    items->push_back(topTextBox);*/ //

    int enemyStatusCount = 1;

    if(!currentTargetAllies)
    {
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
    else
    {
        //Allies
        if(model->getCharacters()->at(currentTarget)->getStatusEffectModel()->SE_att > 0)
        {
            DrawInformation SEAttUp(-12 + (((enemyStatusCount%2) - (((enemyStatusCount+1)%2))) * 15*enemyStatusCount++), 360, 25, 25, "SEAttackUp", false);
            items->push_back(SEAttUp);
        }
        if(model->getCharacters()->at(currentTarget)->getStatusEffectModel()->SE_att < 0)
        {
            DrawInformation SEAttUp(-12 + (((enemyStatusCount%2) - (((enemyStatusCount+1)%2))) * 15*enemyStatusCount++), 360, 25, 25, "SEAttackDown", false);
            items->push_back(SEAttUp);
        }
        if(model->getCharacters()->at(currentTarget)->getStatusEffectModel()->SE_def > 0)
        {
            DrawInformation SEAttUp(-12 + (((enemyStatusCount%2) - (((enemyStatusCount+1)%2))) * 15*enemyStatusCount++), 360, 25, 25, "SEDefenceUp", false);
            items->push_back(SEAttUp);
        }
        if(model->getCharacters()->at(currentTarget)->getStatusEffectModel()->SE_def < 0)
        {
            DrawInformation SEAttUp(-12 + (((enemyStatusCount%2) - (((enemyStatusCount+1)%2))) * 15*enemyStatusCount++), 360, 25, 25, "SEDefenceDown", false);
            items->push_back(SEAttUp);
        }
        if(model->getCharacters()->at(currentTarget)->getStatusEffectModel()->SE_magic > 0)
        {
            DrawInformation SEAttUp(-12 + (((enemyStatusCount%2) - (((enemyStatusCount+1)%2))) * 15*enemyStatusCount++), 360, 25, 25, "SEMagicUp", false);
            items->push_back(SEAttUp);
        }
        if(model->getCharacters()->at(currentTarget)->getStatusEffectModel()->SE_magic < 0)
        {
            DrawInformation SEAttUp(-12 + (((enemyStatusCount%2) - (((enemyStatusCount+1)%2))) * 15*enemyStatusCount++), 360, 25, 25, "SEMagicDown", false);
            items->push_back(SEAttUp);
        }
        if(model->getCharacters()->at(currentTarget)->getStatusEffectModel()->SE_magicDef > 0)
        {
            DrawInformation SEAttUp(-12 + (((enemyStatusCount%2) - (((enemyStatusCount+1)%2))) * 15*enemyStatusCount++), 360, 25, 25, "SEMagicDefenceUp", false);
            items->push_back(SEAttUp);
        }
        if(model->getCharacters()->at(currentTarget)->getStatusEffectModel()->SE_magicDef < 0)
        {
            DrawInformation SEAttUp(-12 + (((enemyStatusCount%2) - (((enemyStatusCount+1)%2))) * 15*enemyStatusCount++), 360, 25, 25, "SEMagicDefenceDown", false);
            items->push_back(SEAttUp);
        }
        if(model->getCharacters()->at(currentTarget)->getStatusEffectModel()->SE_speed > 0)
        {
            DrawInformation SEAttUp(-12 + (((enemyStatusCount%2) - (((enemyStatusCount+1)%2))) * 15*enemyStatusCount++), 360, 25, 25, "SEHaste", false);
            items->push_back(SEAttUp);
        }
        if(model->getCharacters()->at(currentTarget)->getStatusEffectModel()->SE_speed < 0)
        {
            DrawInformation SEAttUp(-12 + (((enemyStatusCount%2) - (((enemyStatusCount+1)%2))) * 15*enemyStatusCount++), 360, 25, 25, "SESlow", false);
            items->push_back(SEAttUp);
        }
        /////////////////
        if(model->getCharacters()->at(currentTarget)->getStatusEffectModel()->poison)
        {
            DrawInformation SEAttUp(-12 + (((enemyStatusCount%2) - (((enemyStatusCount+1)%2))) * 15*enemyStatusCount++), 360, 25, 25, "SEPoison", false);
            items->push_back(SEAttUp);
        }
        if(model->getCharacters()->at(currentTarget)->getStatusEffectModel()->blind)
        {
            DrawInformation SEAttUp(-12 + (((enemyStatusCount%2) - (((enemyStatusCount+1)%2))) * 15*enemyStatusCount++), 360, 25, 25, "SEBlind", false);
            items->push_back(SEAttUp);
        }
        if(model->getCharacters()->at(currentTarget)->getStatusEffectModel()->sleep)
        {
            DrawInformation SEAttUp(-12 + (((enemyStatusCount%2) - (((enemyStatusCount+1)%2))) * 15*enemyStatusCount++), 360, 25, 25, "SESleep", false);
            items->push_back(SEAttUp);
        }
        if(model->getCharacters()->at(currentTarget)->getStatusEffectModel()->silenced)
        {
            DrawInformation SEAttUp(-12 + (((enemyStatusCount%2) - (((enemyStatusCount+1)%2))) * 15*enemyStatusCount++), 360, 25, 25, "SESilence", false);
            items->push_back(SEAttUp);
        }
    }
}
