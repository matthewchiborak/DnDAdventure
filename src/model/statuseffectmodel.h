#ifndef STATUSEFFECTMODEL_H
#define STATUSEFFECTMODEL_H

#include <string>

class StatusEffectModel
{
public:
    StatusEffectModel();

    void applyStatusEffect(std::string se);
    void cureAllNegativeStatusEffects();

    void applyTime(float t);

    int SE_att = 0;
    int SE_def = 0;
    int SE_magic = 0;
    int SE_magicDef = 0;
    int SE_speed = 0;

    bool guard = false;
    bool poison = false;
    bool sleep = false;
    bool blind = false;
    bool silenced = false;
    bool wet = false;

    bool taunt = false;
    bool disguise = false;
    bool stance = false;

    int sleepCount = 0;
    const int sleepDuration = 15000;
    const float poisonDamagePercentagePerAction = 0.1f;

    const int buffDuration = 45000;
    int attackCount = 0;
    int defenceCount = 0;
    int magicCount = 0;
    int magicDefenceCount = 0;
    int speedCount = 0;
    int tauntCount = 0;
    int disguiseCount = 0;

    bool overdrive = false;
    const int overdriveDuration = 20000;
    int overdriveCount = 0;
};

#endif // STATUSEFFECTMODEL_H
