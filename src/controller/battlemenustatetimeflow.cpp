#include "battlemenustatetimeflow.h"

#include "../display/drawinformation.h"
#include "../model/battlemodel.h"
#include "../model/playercharacterstats.h"
#include "../model/EnemyModel.h"
#include "../controller/battlemenustatemain.h"
#include "../model/playercharacterstatsbattle.h"
#include "../model/attackmodel.h"

#include <chrono>
#include <QDebug>

BattleMenuStateTimeFlow::BattleMenuStateTimeFlow(BattleModel *model)
    : BattleMenuState(model)
{
    auto nowTime = std::chrono::system_clock::now().time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime).count();
    theTimeNow = (millis);
    timeOfLastEvent = theTimeNow;
}

void BattleMenuStateTimeFlow::moveMenuCursor(int x, int y)
{

}

BattleMenuState *BattleMenuStateTimeFlow::enterMenu()
{
    return this;
}

BattleMenuState *BattleMenuStateTimeFlow::closeMenu()
{
    return this;
}

BattleMenuState *BattleMenuStateTimeFlow::passTime(float value)
{
    //Actually do something
    //value will be t just like how movement is done. Maybe. That value might not
    //Even be used.
    //For now. Your speed stat will be how much increase 0-1200 for your speed stat per second
    auto nowTime = std::chrono::system_clock::now().time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime).count();
    theTimeNow =(millis);
    elapsed_millies = theTimeNow - timeOfLastEvent;

    float p1PosBefore = model->getP1TimeLinePos();
    float p2PosBefore = model->getP2TimeLinePos();

    model->getCharacters()->at(0)->applyTime(elapsed_millies);
    model->getCharacters()->at(1)->applyTime(elapsed_millies);

    if(model->getCharacters()->at(0)->getCurrentHealth() > 0)
    {
        if(!model->getCharacters()->at(0)->getIsCasting())
            model->setP1TimeLinePos(p1PosBefore + ((0.2f * elapsed_millies) * ((float)model->getCharacters()->at(0)->getSpeed() / (float)model->getSpeedValueToGet200PointsPerSecond())));
        else
            model->setP1TimeLinePos(p1PosBefore + ((elapsed_millies * 200) / model->getCharacters()->at(0)->getCastingAttack()->getCastTime()));
    }

    if(model->getCharacters()->at(1)->getCurrentHealth() > 0)
    {
        if(!model->getCharacters()->at(1)->getIsCasting())
            model->setP2TimeLinePos(p2PosBefore + ((0.2f * elapsed_millies) * ((float)model->getCharacters()->at(1)->getSpeed() / (float)model->getSpeedValueToGet200PointsPerSecond())));
        else
            model->setP2TimeLinePos(p2PosBefore + ((elapsed_millies * 200) / model->getCharacters()->at(1)->getCastingAttack()->getCastTime()));
    }

    for(int i = 0; i < model->getEnemies()->size(); i++)
    {
        if(model->getEnemies()->at(i)->getCurrentHealth() > 0)
        {
            model->getEnemies()->at(i)->applyTime(elapsed_millies);

            float enPosBefore =  model->getEnemies()->at(i)->getTimeLinePos();
            if(!model->getEnemies()->at(i)->getIsCasting())
                model->getEnemies()->at(i)->setTimeLinePos(enPosBefore + ((0.2f * elapsed_millies) * ((float)model->getEnemies()->at(i)->getSpeed() / (float)model->getSpeedValueToGet200PointsPerSecond())));
            else
                model->getEnemies()->at(i)->setTimeLinePos(enPosBefore + ((elapsed_millies * 200) / model->getEnemies()->at(i)->getCastingAttack()->getCastTime()));

            if(enPosBefore < 1000 && model->getEnemies()->at(i)->getTimeLinePos() >= 1000)
            {
                std::vector<int> aliveAlies;
                for(int ass = 0; ass < model->getEnemies()->size(); ass++)
                {
                    if(model->getEnemies()->at(ass)->getCurrentHealth() > 0)
                        aliveAlies.push_back(ass);
                }

                model->getEnemies()->at(i)->setTimeLinePos(1000);
                model->getEnemies()->at(i)->castARandomAttack(model->getCharacters()->at(0)->getCurrentHealth() > 0,
                                                              model->getCharacters()->at(1)->getCurrentHealth() > 0,
                                                              i,
                                                              aliveAlies
                                                              );
            }

            if(model->getEnemies()->at(i)->getTimeLinePos() >= 1200)
            {
                if(model->getEnemies()->at(i)->getCastingAttack()->getMultitarget() == 1)
                {
                    model->incrementPartyGauge(false);
                    model->applyAttackAllAllies(model->getEnemies()->at(i), model->getEnemies()->at(i)->getCastingAttack());
                }
                else if(model->getEnemies()->at(i)->getCastingAttack()->getMultitarget() == 2)
                {
                    model->incrementPartyGauge(false);
                    model->applyAttackAllEnemies(model->getEnemies()->at(i), model->getEnemies()->at(i)->getCastingAttack());
                }
                else
                {
                    model->incrementPartyGauge(false);

                    if(!model->getEnemies()->at(i)->getAttackTargetAlly())
                    {
                        model->applyAttack(model->getEnemies()->at(i),
                                           model->getCharacters()->at(model->getEnemies()->at(i)->getAttackTarget()),
                                           model->getEnemies()->at(i)->getCastingAttack()
                                           );
                    }
                    else
                    {
                        model->applyAttack(model->getEnemies()->at(i),
                                           model->getEnemies()->at(model->getEnemies()->at(i)->getAttackTarget()),
                                           model->getEnemies()->at(i)->getCastingAttack()
                                           );
                    }
                }
                int poiDam = model->getEnemies()->at(i)->justGotToEndOfTimeLine();
                if(poiDam != 0)
                    model->addAboveHeadBattleMessage(true, i, "Hurt", std::to_string(-1 * poiDam), 5000, -1);
                model->getEnemies()->at(i)->stopCasting();
                model->getEnemies()->at(i)->setTimeLinePos(0);


            }
        }
    }

    //Thats why it was always speeding up
    timeOfLastEvent = theTimeNow;

    if(p1PosBefore < 1000 && model->getP1TimeLinePos() >= 1000)
    {
        model->getCharacters()->at(0)->getStatusEffectModel()->guard = false;
        model->setP1TimeLinePos(1000);
        model->setFocusPartyMember(0);
        return new BattleMenuStateMain(model);
    }
    if(p2PosBefore < 1000 && model->getP2TimeLinePos() >= 1000)
    {
        model->getCharacters()->at(1)->getStatusEffectModel()->guard = false;
        model->setP2TimeLinePos(1000);
        model->setFocusPartyMember(1);
        return new BattleMenuStateMain(model);
    }

    if(model->getP1TimeLinePos() >= 1200)
    {
        if(model->getCharacters()->at(0)->getIsCasting())
        {
            if(model->getCharacters()->at(0)->getCastingAttack()->getMultitarget() == 1)
            {
                model->applyAttackAllEnemies(model->getCharacters()->at(0), model->getCharacters()->at(0)->getCastingAttack());
            }
            else if(model->getCharacters()->at(0)->getCastingAttack()->getMultitarget() == 2)
            {
                model->applyAttackAllAllies(model->getCharacters()->at(0), model->getCharacters()->at(0)->getCastingAttack());
            }
            else
            {
                if(!model->getCharacters()->at(0)->getIsTargetAllies())
                {
                    model->applyAttack(model->getCharacters()->at(0),
                                   model->getEnemies()->at(model->getCharacters()->at(0)->getAttackTarget()),
                                   model->getCharacters()->at(0)->getCastingAttack()
                                   );
                }
                else
                {
                    model->applyAttack(model->getCharacters()->at(0),
                                   model->getCharacters()->at(model->getCharacters()->at(0)->getAttackTarget()),
                                   model->getCharacters()->at(0)->getCastingAttack()
                                   );
                }
            }
            model->getCharacters()->at(0)->changeCurrentMP(-1 * model->getCharacters()->at(0)->getCastingAttack()->getMpcost());
            model->getCharacters()->at(0)->stopCasting();
            model->incrementPartyGauge(true);
        }
        int poiDam = model->getCharacters()->at(0)->justGotToEndOfTimeLine();
        if(poiDam != 0)
            model->addAboveHeadBattleMessage(false, 0, "Hurt", std::to_string(-1 * poiDam), 5000, -1);
        model->setP1TimeLinePos(0);
    }
    if(model->getP2TimeLinePos() >= 1200)
    {
        if(model->getCharacters()->at(1)->getIsCasting())
        {
            if(model->getCharacters()->at(1)->getCastingAttack()->getMultitarget() == 1)
            {
                model->applyAttackAllEnemies(model->getCharacters()->at(1), model->getCharacters()->at(1)->getCastingAttack());
            }
            else if(model->getCharacters()->at(1)->getCastingAttack()->getMultitarget() == 2)
            {
                model->applyAttackAllAllies(model->getCharacters()->at(1), model->getCharacters()->at(1)->getCastingAttack());
            }
            else
            {
                if(!model->getCharacters()->at(1)->getIsTargetAllies())
                {
                    model->applyAttack(model->getCharacters()->at(1),
                                       model->getEnemies()->at(model->getCharacters()->at(1)->getAttackTarget()),
                                       model->getCharacters()->at(1)->getCastingAttack()
                                       );
                }
                else
                {
                    model->applyAttack(model->getCharacters()->at(1),
                                       model->getCharacters()->at(model->getCharacters()->at(1)->getAttackTarget()),
                                       model->getCharacters()->at(1)->getCastingAttack()
                                       );
                }
            }
            model->incrementPartyGauge(true);
            model->getCharacters()->at(1)->changeCurrentMP(-1 * model->getCharacters()->at(1)->getCastingAttack()->getMpcost());
            model->getCharacters()->at(1)->stopCasting();
        }
        int poiDam = model->getCharacters()->at(1)->justGotToEndOfTimeLine();
        if(poiDam != 0)
            model->addAboveHeadBattleMessage(false, 1, "Hurt", std::to_string(-1 * poiDam), 5000, -1);
        model->setP2TimeLinePos(0);
    }

    return this;
}

void BattleMenuStateTimeFlow::drawBattleMenu(std::vector<DrawInformation> *items)
{
    //Character portraits
    //images first
    DrawInformation port1(-300, -275, 150, 150, model->getCharacters()->at(0)->getMenuSpriteKey(), false);
    items->push_back(port1);
    DrawInformation port2(250, -275, 150, 150, model->getCharacters()->at(1)->getMenuSpriteKey(), false);
    items->push_back(port2);

    //Draw if can instant turn
    if(model->getPartyGaugeValue() >= 250)
    {
        if(model->getP1TimeLinePos() < 1000 && model->getCharacters()->at(0)->getCurrentHealth() > 0)
        {
            DrawInformation port1(-300, -275 + 125, 25, 25, "InstantTurnR", false);
            items->push_back(port1);
        }
        if(model->getP2TimeLinePos() < 1000 && model->getCharacters()->at(1)->getCurrentHealth() > 0)
        {
            DrawInformation port1(250, -275 + 125, 25, 25, "InstantTurnQ", false);
            items->push_back(port1);
        }
    }

    //Status effects
    drawStatusEffects(items);

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
}

BattleMenuState *BattleMenuStateTimeFlow::qrPressed(bool wasQ)
{
    //instant turn
    if(model->getPartyGaugeValue() >= 250)
    {
        if(!wasQ)
        {
            if(model->getP1TimeLinePos() < 1000 && model->getCharacters()->at(0)->getCurrentHealth() > 0)
                model->setP1TimeLinePos(999);
            else
                return this;
        }
        else
        {
            if(model->getP2TimeLinePos() < 1000 && model->getCharacters()->at(1)->getCurrentHealth() > 0)
                model->setP2TimeLinePos(999);
            else
                return this;
        }

        model->changePartyGaugeValue(-250);
    }

    return this;
}

void BattleMenuStateTimeFlow::drawStatusEffects(std::vector<DrawInformation> * items)
{
    int p1UpperStatusCount = 0;
    int p1LowerStatusCount = 0;
    int p2UpperStatusCount = 0;
    int p2LowerStatusCount = 0;

    if(model->getCharacters()->at(0)->getStatusEffectModel()->guard)
    {
        DrawInformation port1(-300, -275, 50, 50, "Guard", false);
        items->push_back(port1);
    }
    if(model->getCharacters()->at(1)->getStatusEffectModel()->guard)
    {
        DrawInformation port1(250, -275, 50, 50, "Guard", false);
        items->push_back(port1);
    }

    //

    if(model->getCharacters()->at(0)->getStatusEffectModel()->overdrive)
    {
        DrawInformation port1(-250, -275, 50, 50, "Overdrive", false);
        items->push_back(port1);
    }
    if(model->getCharacters()->at(1)->getStatusEffectModel()->overdrive)
    {
        DrawInformation port1(300, -275, 50, 50, "Overdrive", false);
        items->push_back(port1);
    }

    //////////////

    if(model->getCharacters()->at(0)->getStatusEffectModel()->SE_att > 0)
    {
        DrawInformation SEAttUp(-300 + 10 + (60*p1UpperStatusCount++), -275-50-10, 50, 50, "SEAttackUp", false);
        items->push_back(SEAttUp);
    }
    if(model->getCharacters()->at(0)->getStatusEffectModel()->SE_att < 0)
    {
        DrawInformation SEAttUp(-300 + 10 + (60*p1UpperStatusCount++), -275-50-10, 50, 50, "SEAttackDown", false);
        items->push_back(SEAttUp);
    }
    if(model->getCharacters()->at(0)->getStatusEffectModel()->SE_def > 0)
    {
        DrawInformation SEAttUp(-300 + 10 + (60*p1UpperStatusCount++), -275-50-10, 50, 50, "SEDefenceUp", false);
        items->push_back(SEAttUp);
    }
    if(model->getCharacters()->at(0)->getStatusEffectModel()->SE_def < 0)
    {
        DrawInformation SEAttUp(-300 + 10 + (60*p1UpperStatusCount++), -275-50-10, 50, 50, "SEDefenceDown", false);
        items->push_back(SEAttUp);
    }
    if(model->getCharacters()->at(0)->getStatusEffectModel()->SE_magic > 0)
    {
        DrawInformation SEAttUp(-300 + 10 + (60*p1UpperStatusCount++), -275-50-10, 50, 50, "SEMagicUp", false);
        items->push_back(SEAttUp);
    }
    if(model->getCharacters()->at(0)->getStatusEffectModel()->SE_magic < 0)
    {
        DrawInformation SEAttUp(-300 + 10 + (60*p1UpperStatusCount++), -275-50-10, 50, 50, "SEMagicDown", false);
        items->push_back(SEAttUp);
    }
    if(model->getCharacters()->at(0)->getStatusEffectModel()->SE_magicDef > 0)
    {
        DrawInformation SEAttUp(-300 + 10 + (60*p1UpperStatusCount++), -275-50-10, 50, 50, "SEMagicDefenceUp", false);
        items->push_back(SEAttUp);
    }
    if(model->getCharacters()->at(0)->getStatusEffectModel()->SE_magicDef < 0)
    {
        DrawInformation SEAttUp(-300 + 10 + (60*p1UpperStatusCount++), -275-50-10, 50, 50, "SEMagicDefenceDown", false);
        items->push_back(SEAttUp);
    }
    if(model->getCharacters()->at(0)->getStatusEffectModel()->SE_speed > 0)
    {
        DrawInformation SEAttUp(-300 + 10 + (60*p1UpperStatusCount++), -275-50-10, 50, 50, "SEHaste", false);
        items->push_back(SEAttUp);
    }
    if(model->getCharacters()->at(0)->getStatusEffectModel()->SE_speed < 0)
    {
        DrawInformation SEAttUp(-300 + 10 + (60*p1UpperStatusCount++), -275-50-10, 50, 50, "SESlow", false);
        items->push_back(SEAttUp);
    }
    /////////////////
    if(model->getCharacters()->at(0)->getStatusEffectModel()->poison)
    {
        DrawInformation SEAttUp(-300 + 10 + (60*p1LowerStatusCount++), -275-100-15, 50, 50, "SEPoison", false);
        items->push_back(SEAttUp);
    }
    if(model->getCharacters()->at(0)->getStatusEffectModel()->blind)
    {
        DrawInformation SEAttUp(-300 + 10 + (60*p1LowerStatusCount++), -275-100-15, 50, 50, "SEBlind", false);
        items->push_back(SEAttUp);
    }
    if(model->getCharacters()->at(0)->getStatusEffectModel()->sleep)
    {
        DrawInformation SEAttUp(-300 + 10 + (60*p1LowerStatusCount++), -275-100-15, 50, 50, "SESleep", false);
        items->push_back(SEAttUp);
    }
    if(model->getCharacters()->at(0)->getStatusEffectModel()->silenced)
    {
        DrawInformation SEAttUp(-300 + 10 + (60*p1LowerStatusCount++), -275-100-15, 50, 50, "SESilence", false);
        items->push_back(SEAttUp);
    }
    if(model->getCharacters()->at(0)->getStatusEffectModel()->taunt)
    {
        DrawInformation SEAttUp(-300 + 10 + (60*p1LowerStatusCount++), -275-100-15, 50, 50, "SETaunt", false);
        items->push_back(SEAttUp);
    }
    if(model->getCharacters()->at(0)->getStatusEffectModel()->disguise)
    {
        DrawInformation SEAttUp(-300 + 10 + (60*p1LowerStatusCount++), -275-100-15, 50, 50, "SEDisguise", false);
        items->push_back(SEAttUp);
    }
    if(model->getCharacters()->at(0)->getStatusEffectModel()->stance)
    {
        DrawInformation SEAttUp(-300 + 10 + (60*p1LowerStatusCount++), -275-100-15, 50, 50, "SEStance", false);
        items->push_back(SEAttUp);
    }
    ////////////////
    if(model->getCharacters()->at(1)->getStatusEffectModel()->SE_att > 0)
    {
        DrawInformation SEAttUp(250 + 10 + (60*p2UpperStatusCount++), -275-50-10, 50, 50, "SEAttackUp", false);
        items->push_back(SEAttUp);
    }
    if(model->getCharacters()->at(1)->getStatusEffectModel()->SE_att < 0)
    {
        DrawInformation SEAttUp(250 + 10 + (60*p2UpperStatusCount++), -275-50-10, 50, 50, "SEAttackDown", false);
        items->push_back(SEAttUp);
    }
    if(model->getCharacters()->at(1)->getStatusEffectModel()->SE_def > 0)
    {
        DrawInformation SEAttUp(250 + 10 + (60*p2UpperStatusCount++), -275-50-10, 50, 50, "SEDefenceUp", false);
        items->push_back(SEAttUp);
    }
    if(model->getCharacters()->at(1)->getStatusEffectModel()->SE_def < 0)
    {
        DrawInformation SEAttUp(250 + 10 + (60*p2UpperStatusCount++), -275-50-10, 50, 50, "SEDefenceDown", false);
        items->push_back(SEAttUp);
    }
    if(model->getCharacters()->at(1)->getStatusEffectModel()->SE_magic > 0)
    {
        DrawInformation SEAttUp(250 + 10 + (60*p2UpperStatusCount++), -275-50-10, 50, 50, "SEMagicUp", false);
        items->push_back(SEAttUp);
    }
    if(model->getCharacters()->at(1)->getStatusEffectModel()->SE_magic < 0)
    {
        DrawInformation SEAttUp(250 + 10 + (60*p2UpperStatusCount++), -275-50-10, 50, 50, "SEMagicDown", false);
        items->push_back(SEAttUp);
    }
    if(model->getCharacters()->at(1)->getStatusEffectModel()->SE_magicDef > 0)
    {
        DrawInformation SEAttUp(250 + 10 + (60*p2UpperStatusCount++), -275-50-10, 50, 50, "SEMagicDefenceUp", false);
        items->push_back(SEAttUp);
    }
    if(model->getCharacters()->at(1)->getStatusEffectModel()->SE_magicDef < 0)
    {
        DrawInformation SEAttUp(250 + 10 + (60*p2UpperStatusCount++), -275-50-10, 50, 50, "SEMagicDefenceDown", false);
        items->push_back(SEAttUp);
    }
    if(model->getCharacters()->at(1)->getStatusEffectModel()->SE_speed > 0)
    {
        DrawInformation SEAttUp(250 + 10 + (60*p2UpperStatusCount++), -275-50-10, 50, 50, "SEHaste", false);
        items->push_back(SEAttUp);
    }
    if(model->getCharacters()->at(1)->getStatusEffectModel()->SE_speed < 0)
    {
        DrawInformation SEAttUp(250 + 10 + (60*p2UpperStatusCount++), -275-50-10, 50, 50, "SESlow", false);
        items->push_back(SEAttUp);
    }
    /////////////////
    if(model->getCharacters()->at(1)->getStatusEffectModel()->poison)
    {
        DrawInformation SEAttUp(250 + 10 + (60*p2LowerStatusCount++), -275-100-15, 50, 50, "SEPoison", false);
        items->push_back(SEAttUp);
    }
    if(model->getCharacters()->at(1)->getStatusEffectModel()->blind)
    {
        DrawInformation SEAttUp(250 + 10 + (60*p2LowerStatusCount++), -275-100-15, 50, 50, "SEBlind", false);
        items->push_back(SEAttUp);
    }
    if(model->getCharacters()->at(1)->getStatusEffectModel()->sleep)
    {
        DrawInformation SEAttUp(250 + 10 + (60*p2LowerStatusCount++), -275-100-15, 50, 50, "SESleep", false);
        items->push_back(SEAttUp);
    }
    if(model->getCharacters()->at(1)->getStatusEffectModel()->silenced)
    {
        DrawInformation SEAttUp(250 + 10 + (60*p2LowerStatusCount++), -275-100-15, 50, 50, "SESilence", false);
        items->push_back(SEAttUp);
    }
    if(model->getCharacters()->at(1)->getStatusEffectModel()->taunt)
    {
        DrawInformation SEAttUp(250 + 10 + (60*p2LowerStatusCount++), -275-100-15, 50, 50, "SETaunt", false);
        items->push_back(SEAttUp);
    }
    if(model->getCharacters()->at(1)->getStatusEffectModel()->disguise)
    {
        DrawInformation SEAttUp(250 + 10 + (60*p2LowerStatusCount++), -275-100-15, 50, 50, "SEDisguise", false);
        items->push_back(SEAttUp);
    }
    if(model->getCharacters()->at(1)->getStatusEffectModel()->stance)
    {
        DrawInformation SEAttUp(250 + 10 + (60*p2LowerStatusCount++), -275-100-15, 50, 50, "SEStance", false);
        items->push_back(SEAttUp);
    }
}
