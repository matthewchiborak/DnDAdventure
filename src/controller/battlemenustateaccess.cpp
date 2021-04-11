#include "battlemenustateaccess.h"

#include <QDebug>

#include "battlemenustatetimeflow.h"
#include "../model/battlemodel.h"
#include "../model/EnemyModel.h"
#include "../display/drawinformation.h"

BattleMenuStateAccess::BattleMenuStateAccess(BattleModel *model)
    : BattleMenuState(model)
{
    model->forceClearDisplayMessage();
}

void BattleMenuStateAccess::moveMenuCursor(int x, int y)
{

}

BattleMenuState *BattleMenuStateAccess::enterMenu()
{
    return this;
}

BattleMenuState *BattleMenuStateAccess::closeMenu()
{
    return new BattleMenuStateTimeFlow(model);
}

BattleMenuState *BattleMenuStateAccess::passTime(float value)
{
    return this;
}

void BattleMenuStateAccess::drawBattleMenu(std::vector<DrawInformation> *items)
{
    DrawInformation topTextBox(-750, -115, 1600, 620, "AccessBG", false);
    items->push_back(topTextBox);

    DrawInformation port(-150, 0, 400, 400, model->getEnemyToAccess()->getSpriteKey(), false);
    items->push_back(port);

    DrawInformation slash(300, 400, 50, 50, "SlashIcon", false);
    items->push_back(slash);
    DrawInformation blunt(300, 350, 50, 50, "BluntIcon", false);
    items->push_back(blunt);
    DrawInformation pierce(300, 300, 50, 50, "PierceIcon", false);
    items->push_back(pierce);
    DrawInformation fire(300, 250, 50, 50, "FireIcon", false);
    items->push_back(fire);
    DrawInformation ice(300, 200, 50, 50, "IceIcon", false);
    items->push_back(ice);
    DrawInformation lightning(300, 150, 50, 50, "LightningIcon", false);
    items->push_back(lightning);
    DrawInformation water(300, 100, 50, 50, "WaterIcon", false);
    items->push_back(water);
    DrawInformation wind(300, 50, 50, 50, "WindIcon", false);
    items->push_back(wind);
    DrawInformation earth(300, 0, 50, 50, "EarthIcon", false);
    items->push_back(earth);

    //Status effect immuntes
    int numImm = 0;

    if(model->getEnemyToAccess()->isImmuneToThis("AttackDown"))
    {
        DrawInformation aliment(-600 + (((numImm%3) * 50) + 25), 350 - ((numImm/3) * 50), 50, 50, "SEAttackDown", false);
        items->push_back(aliment);
        numImm++;
    }
    if(model->getEnemyToAccess()->isImmuneToThis("DefenceDown"))
    {
        DrawInformation aliment(-600 + (((numImm%3) * 50) + 25), 350 - ((numImm/3) * 50), 50, 50, "SEDefenceDown", false);
        items->push_back(aliment);
        numImm++;
    }
    if(model->getEnemyToAccess()->isImmuneToThis("MagicDown"))
    {
        DrawInformation aliment(-600 + (((numImm%3) * 50) + 25), 350 - ((numImm/3) * 50), 50, 50, "SEMagicDown", false);
        items->push_back(aliment);
        numImm++;
    }
    if(model->getEnemyToAccess()->isImmuneToThis("MagicDefenceDown"))
    {
        DrawInformation aliment(-600 + (((numImm%3) * 50) + 25), 350 - ((numImm/3) * 50), 50, 50, "SEMagicDefenceDown", false);
        items->push_back(aliment);
        numImm++;
    }
    if(model->getEnemyToAccess()->isImmuneToThis("Slow"))
    {
        DrawInformation aliment(-600 + (((numImm%3) * 50) + 25), 350 - ((numImm/3) * 50), 50, 50, "SESlow", false);
        items->push_back(aliment);
        numImm++;
    }
    if(model->getEnemyToAccess()->isImmuneToThis("Poison"))
    {
        DrawInformation aliment(-600 + (((numImm%3) * 50) + 25), 350 - ((numImm/3) * 50), 50, 50, "SEPoison", false);
        items->push_back(aliment);
        numImm++;
    }
    if(model->getEnemyToAccess()->isImmuneToThis("Blind"))
    {
        DrawInformation aliment(-600 + (((numImm%3) * 50) + 25), 350 - ((numImm/3) * 50), 50, 50, "SEBlind", false);
        items->push_back(aliment);
        numImm++;
    }
    if(model->getEnemyToAccess()->isImmuneToThis("Sleep"))
    {
        DrawInformation aliment(-600 + (((numImm%3) * 50) + 25), 350 - ((numImm/3) * 50), 50, 50, "SESleep", false);
        items->push_back(aliment);
        numImm++;
    }
    if(model->getEnemyToAccess()->isImmuneToThis("Silence"))
    {
        DrawInformation aliment(-600 + (((numImm%3) * 50) + 25), 350 - ((numImm/3) * 50), 50, 50, "SESilence", false);
        items->push_back(aliment);
        numImm++;
    }


    //Text
    DrawInformation info2(500, 0, 500, 100, "", false, model->getEnemyToAccess()->getName(), false, 72.f);
    items->push_back(info2);
    DrawInformation info3(100, 500, 1400, 100, "", false,
                          "[Level: " + std::to_string(model->getEnemyToAccess()->getLevel())
                          + "] [HP: " + std::to_string(model->getEnemyToAccess()->getMaxHealth())
                          + "] [Att: " + std::to_string(model->getEnemyToAccess()->getAttack())
                          + "] [Def: " + std::to_string(model->getEnemyToAccess()->getDefence())
                          + "] [Magic: " + std::to_string(model->getEnemyToAccess()->getMagicAttack())
                          + "] [MagicDef: " + std::to_string(model->getEnemyToAccess()->getMagicDefence())
                          + "] [Speed: " + std::to_string(model->getEnemyToAccess()->getSpeed())
                          + "]",
                          false, 28.f);
    items->push_back(info3);

    /////////////////////

    DrawInformation debuffImmunes(150, 0, 200, 100, "", false, "Immunities:", false, 36);
    items->push_back(debuffImmunes);


    std::string tempType = model->getEnemyToAccess()->getElementalString(1);
    int tempr = 0, tempg = 0, tempb = 0;
    model->getEnemyToAccess()->getRGB(tempType, &tempr, &tempg, &tempb);
    DrawInformation fireText(1125, 200, 200, 50, "", false, tempType, true, 36, tempr, tempg, tempb);
    items->push_back(fireText);

    tempType = model->getEnemyToAccess()->getElementalString(2);
    model->getEnemyToAccess()->getRGB(tempType, &tempr, &tempg, &tempb);
    DrawInformation iceText(1125, 250, 200, 50, "", false, tempType, true, 36, tempr, tempg, tempb);
    items->push_back(iceText);

    tempType = model->getEnemyToAccess()->getElementalString(3);
    model->getEnemyToAccess()->getRGB(tempType, &tempr, &tempg, &tempb);
    DrawInformation lightningText(1125, 300, 200, 50, "", false, tempType, true, 36, tempr, tempg, tempb);
    items->push_back(lightningText);

    tempType = model->getEnemyToAccess()->getElementalString(4);
    model->getEnemyToAccess()->getRGB(tempType, &tempr, &tempg, &tempb);
    DrawInformation waterText(1125, 350, 200, 50, "", false, tempType, true, 36, tempr, tempg, tempb);
    items->push_back(waterText);

    tempType = model->getEnemyToAccess()->getElementalString(5);
    model->getEnemyToAccess()->getRGB(tempType, &tempr, &tempg, &tempb);
    DrawInformation windText(1125, 400, 200, 50, "", false, tempType, true, 36, tempr, tempg, tempb);
    items->push_back(windText);

    tempType = model->getEnemyToAccess()->getElementalString(6);
    model->getEnemyToAccess()->getRGB(tempType, &tempr, &tempg, &tempb);
    DrawInformation earthText(1125, 450, 200, 50, "", false, tempType, true, 36, tempr, tempg, tempb);
    items->push_back(earthText);

    tempType = model->getEnemyToAccess()->getElementalString(7);
    model->getEnemyToAccess()->getRGB(tempType, &tempr, &tempg, &tempb);
    DrawInformation bashText(1125, 100, 200, 50, "", false, tempType, true, 36, tempr, tempg, tempb);
    items->push_back(bashText);

    tempType = model->getEnemyToAccess()->getElementalString(8);
    model->getEnemyToAccess()->getRGB(tempType, &tempr, &tempg, &tempb);
    DrawInformation slashText(1125, 50, 200, 50, "", false, tempType, true, 36, tempr, tempg, tempb);
    items->push_back(slashText);

    tempType = model->getEnemyToAccess()->getElementalString(9);
    model->getEnemyToAccess()->getRGB(tempType, &tempr, &tempg, &tempb);
    DrawInformation pierceText(1125, 150, 200, 50, "", false, tempType, true, 36, tempr, tempg, tempb);
    items->push_back(pierceText);


    ///////////////

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

    DrawInformation mainCursor(405, 630 + ((0) * 50), 75, 75, "", false, ">", true, 36);
    items->push_back(mainCursor);
}

BattleMenuState *BattleMenuStateAccess::qrPressed(bool wasQ)
{
    return this;
}
