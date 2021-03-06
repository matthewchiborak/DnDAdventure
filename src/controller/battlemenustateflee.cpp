#include "battlemenustateflee.h"

#include "../model/battlemodel.h"

#include "../model/playercharacterstatsbattle.h"

BattleMenuStateFlee::BattleMenuStateFlee(BattleModel *model)
    : BattleMenuState(model)
{
    model->forceClearDisplayMessage();
}

BattleMenuState *BattleMenuStateFlee::enterMenu()
{
    for(int i = 0; i < model->getCharacters()->size(); i++)
    {
        if(model->getCharacters()->at(i)->getCurrentHealth() <= 0)
            model->getCharacters()->at(i)->setCurrentHealth(1);
    }
    model->setBattleIsDoneManual(true);
    return this;
}

BattleMenuState *BattleMenuStateFlee::closeMenu()
{
    return this;
}

BattleMenuState *BattleMenuStateFlee::passTime(float value)
{
    return this;
}

void BattleMenuStateFlee::drawBattleMenu(std::vector<DrawInformation> *items)
{

    //Character portraits
    //images first
    DrawInformation port1(-300, -275, 150, 150, model->getCharacters()->at(0)->getMenuSpriteKey(), false);
    items->push_back(port1);
    DrawInformation port2(250, -275, 150, 150, model->getCharacters()->at(1)->getMenuSpriteKey(), false);
    items->push_back(port2);

    DrawInformation topTextBox(-700, 350, 1500, 140, "BattleMenuBG", false);
    items->push_back(topTextBox);

    drawStatusEffects(items);

    DrawInformation attackDesc(0, 10, 1500, 140, "",
                            false,
                               "Successfully got away"
                               );
    items->push_back(attackDesc);

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

    DrawInformation mainCursor(50, 637 + ((4 - 0) * 50), 75, 75, "", false, ">", true, 36);
    items->push_back(mainCursor);
}

BattleMenuState *BattleMenuStateFlee::qrPressed(bool wasQ)
{
    return this;
}

void BattleMenuStateFlee::drawStatusEffects(std::vector<DrawInformation> *items)
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
