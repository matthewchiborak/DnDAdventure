#include "statuseffectmodel.h"

StatusEffectModel::StatusEffectModel()
{
//    applyStatusEffect("Poison");
//    applyStatusEffect("Sleep");
//    applyStatusEffect("Silence");
//    applyStatusEffect("AttackDown");
//    applyStatusEffect("DefenceUp");
//    applyStatusEffect("MagicDown");
//    applyStatusEffect("MagicDefenceUp");
//    applyStatusEffect("Haste");
}

void StatusEffectModel::applyStatusEffect(std::string se)
{
    if(se == "Poison")
        poison = true;
    else if(se == "Sleep")
    {
        sleepCount = 0;
        sleep = true;
    }
    else if(se == "Silence")
        silenced = true;
    else if(se == "Wet")
        wet = true;
    else if(se == "AttackUp")
    {
        attackCount = 0;
        SE_att++;
        if(SE_att > 1)
            SE_att = 1;
    }
    else if(se == "AttackDown")
    {
        attackCount = 0;
        SE_att--;
        if(SE_att < -1)
            SE_att = -1;
    }
    else if(se == "DefenceUp")
    {
        defenceCount = 0;
        SE_def++;
        if(SE_def > 1)
            SE_def = 1;
    }
    else if(se == "DefenceDown")
    {
        defenceCount = 0;
        SE_def--;
        if(SE_def < -1)
            SE_def = -1;
    }
    else if(se == "MagicUp")
    {
        magicCount = 0;
        SE_magic++;
        if(SE_magic > 1)
            SE_magic = 1;
    }
    else if(se == "MagicDown")
    {
        magicCount = 0;
        SE_magic--;
        if(SE_magic < -1)
            SE_magic = -1;
    }
    else if(se == "MagicDefenceUp")
    {
        magicDefenceCount = 0;
        SE_magicDef++;
        if(SE_magicDef > 1)
            SE_magicDef = 1;
    }
    else if(se == "MagicDefenceDown")
    {
        magicDefenceCount = 0;
        SE_magicDef--;
        if(SE_magicDef < -1)
            SE_magicDef = -1;
    }
    else if(se == "Haste")
    {
        speedCount = 0;
        SE_speed++;
        if(SE_speed > 1)
            SE_speed = 1;
    }
    else if(se == "Slow")
    {
        speedCount = 0;
        SE_speed--;
        if(SE_speed < -1)
            SE_speed = -1;
    }
    else if(se == "Overdrive")
    {
        overdriveCount = 0;
        overdrive = true;
    }
}

void StatusEffectModel::cureAllNegativeStatusEffects()
{
    poison = false;
    sleep = false;
    silenced = false;
    wet = false;

    if(SE_att < 0)
        SE_att = 0;
    if(SE_def < 0)
        SE_def = 0;
    if(SE_magic < 0)
        SE_magic = 0;
    if(SE_magicDef < 0)
        SE_magicDef = 0;
    if(SE_speed < 0)
        SE_speed = 0;
}

void StatusEffectModel::applyTime(float t)
{
    if(sleep)
    {
        sleepCount += t;
        if(sleepCount > sleepDuration)
            sleep = false;
    }
    if(SE_att != 0)
    {
        attackCount += t;
        if(attackCount > buffDuration)
            SE_att = 0;
    }
    if(SE_def != 0)
    {
        defenceCount += t;
        if(defenceCount > buffDuration)
            SE_def = 0;
    }
    if(SE_magic != 0)
    {
        magicCount += t;
        if(magicCount > buffDuration)
            SE_magic = 0;
    }
    if(SE_magicDef != 0)
    {
        magicDefenceCount += t;
        if(magicDefenceCount > buffDuration)
            SE_magicDef = 0;
    }
    if(SE_speed != 0)
    {
        speedCount += t;
        if(speedCount > buffDuration)
            SE_speed = 0;
    }
    if(overdrive)
    {
        overdriveCount += t;
        if(overdriveCount > overdriveDuration)
            overdrive = false;
    }
}
