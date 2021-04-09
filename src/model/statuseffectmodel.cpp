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
        SE_att++;
        if(SE_att > 1)
            SE_att = 1;
    }
    else if(se == "AttackDown")
    {
        SE_att--;
        if(SE_att < -1)
            SE_att = -1;
    }
    else if(se == "DefenceUp")
    {
        SE_def++;
        if(SE_def > 1)
            SE_def = 1;
    }
    else if(se == "DefenceDown")
    {
        SE_def--;
        if(SE_def < -1)
            SE_def = -1;
    }
    else if(se == "MagicUp")
    {
        SE_magic++;
        if(SE_magic > 1)
            SE_magic = 1;
    }
    else if(se == "MagicDown")
    {
        SE_magic--;
        if(SE_magic < -1)
            SE_magic = -1;
    }
    else if(se == "MagicDefenceUp")
    {
        SE_magicDef++;
        if(SE_magicDef > 1)
            SE_magicDef = 1;
    }
    else if(se == "MagicDefenceDown")
    {
        SE_magicDef--;
        if(SE_magicDef < -1)
            SE_magicDef = -1;
    }
    else if(se == "Haste")
    {
        SE_speed++;
        if(SE_speed > 1)
            SE_speed = 1;
    }
    else if(se == "Slow")
    {
        SE_speed--;
        if(SE_speed < -1)
            SE_speed = -1;
    }
}
