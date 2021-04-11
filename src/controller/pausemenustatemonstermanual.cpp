#include "pausemenustatemonstermanual.h"

#include "pausemenustatemain.h"
#include "../display/drawinformation.h"
#include "../model/modelabstract.h"
#include "../model/monstermanualentry.h"
#include "../filemanagment/fileReader.h"
#include "../factory/enemyfactory.h"
#include "../model/EnemyModel.h"

#include <map>

PauseMenuStateMonsterManual::PauseMenuStateMonsterManual(ModelAbstract *model)
    : PauseMenuDrawState(model)
{
    focusEnemy = nullptr;

    for(int i = 0; i < model->getMonsterManual()->size(); i++)
    {
        if(model->getMonsterManual()->at(i).getDefeated())
        {
            names.push_back(model->getMonsterManual()->at(i).getName());
            defeats.push_back(true);
            keys.push_back(model->getMonsterManual()->at(i).getKey());
        }
        else
        {
            names.push_back("-----------");
            defeats.push_back(false);
            keys.push_back(model->getMonsterManual()->at(i).getKey());
        }
    }
}

void PauseMenuStateMonsterManual::moveMenuCursor(int x, int y)
{
    if(x < 0 || x > 0)
    {
        cursorPos = cursorPos + (x*34);

        if(cursorPos < 0)
            cursorPos = cursorPos + (5*34);
        if(cursorPos > 169)
            cursorPos = (cursorPos%34);
    }
    else
    {
        cursorPos -= y;

        if(cursorPos < 0)
            cursorPos = 169;
        if(cursorPos > 169)
            cursorPos = 0;
    }
}

PauseMenuDrawState *PauseMenuStateMonsterManual::enterMenu()
{
    if(!defeats.at(cursorPos))
        return this;

    EnemyFactory fact;
    EnemyModel * temp = focusEnemy;
    focusEnemy = fact.createEnemy(keys.at(cursorPos));
    if(temp != nullptr)
        delete temp;

    displayingFocusEnemy = true;

    return this;
}

PauseMenuDrawState *PauseMenuStateMonsterManual::closeMenu()
{
    if(displayingFocusEnemy)
    {
        displayingFocusEnemy = false;
        return this;
    }

    return new PauseMenuStateMain(model);
}

void PauseMenuStateMonsterManual::drawPauseMenu(std::vector<DrawInformation> *items)
{
    if(displayingFocusEnemy)
    {
        DrawInformation topTextBox(-800, -400, 1700, 900, "AccessBG", false);
        items->push_back(topTextBox);

        DrawInformation port(-150, 0, 400, 400, focusEnemy->getSpriteKey(), false);
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

        if(focusEnemy->isImmuneToThis("AttackDown"))
        {
            DrawInformation aliment(-600 + (((numImm%3) * 50) + 25), 350 - ((numImm/3) * 50), 50, 50, "SEAttackDown", false);
            items->push_back(aliment);
            numImm++;
        }
        if(focusEnemy->isImmuneToThis("DefenceDown"))
        {
            DrawInformation aliment(-600 + (((numImm%3) * 50) + 25), 350 - ((numImm/3) * 50), 50, 50, "SEDefenceDown", false);
            items->push_back(aliment);
            numImm++;
        }
        if(focusEnemy->isImmuneToThis("MagicDown"))
        {
            DrawInformation aliment(-600 + (((numImm%3) * 50) + 25), 350 - ((numImm/3) * 50), 50, 50, "SEMagicDown", false);
            items->push_back(aliment);
            numImm++;
        }
        if(focusEnemy->isImmuneToThis("MagicDefenceDown"))
        {
            DrawInformation aliment(-600 + (((numImm%3) * 50) + 25), 350 - ((numImm/3) * 50), 50, 50, "SEMagicDefenceDown", false);
            items->push_back(aliment);
            numImm++;
        }
        if(focusEnemy->isImmuneToThis("Slow"))
        {
            DrawInformation aliment(-600 + (((numImm%3) * 50) + 25), 350 - ((numImm/3) * 50), 50, 50, "SESlow", false);
            items->push_back(aliment);
            numImm++;
        }
        if(focusEnemy->isImmuneToThis("Poison"))
        {
            DrawInformation aliment(-600 + (((numImm%3) * 50) + 25), 350 - ((numImm/3) * 50), 50, 50, "SEPoison", false);
            items->push_back(aliment);
            numImm++;
        }
        if(focusEnemy->isImmuneToThis("Blind"))
        {
            DrawInformation aliment(-600 + (((numImm%3) * 50) + 25), 350 - ((numImm/3) * 50), 50, 50, "SEBlind", false);
            items->push_back(aliment);
            numImm++;
        }
        if(focusEnemy->isImmuneToThis("Sleep"))
        {
            DrawInformation aliment(-600 + (((numImm%3) * 50) + 25), 350 - ((numImm/3) * 50), 50, 50, "SESleep", false);
            items->push_back(aliment);
            numImm++;
        }
        if(focusEnemy->isImmuneToThis("Silence"))
        {
            DrawInformation aliment(-600 + (((numImm%3) * 50) + 25), 350 - ((numImm/3) * 50), 50, 50, "SESilence", false);
            items->push_back(aliment);
            numImm++;
        }


        //Text
        DrawInformation info2(500, 0, 500, 100, "", false, focusEnemy->getName(), false, 72.f);
        items->push_back(info2);
        DrawInformation info3(100, 500, 1400, 100, "", false,
                              "[Level: " + std::to_string(focusEnemy->getLevel())
                              + "] [HP: " + std::to_string(focusEnemy->getMaxHealth())
                              + "] [Att: " + std::to_string(focusEnemy->getAttack())
                              + "] [Def: " + std::to_string(focusEnemy->getDefence())
                              + "] [Magic: " + std::to_string(focusEnemy->getMagicAttack())
                              + "] [MagicDef: " + std::to_string(focusEnemy->getMagicDefence())
                              + "] [Speed: " + std::to_string(focusEnemy->getSpeed())
                              + "]",
                              false, 28.f);
        items->push_back(info3);

        /////////////////////

        DrawInformation debuffImmunes(150, 0, 200, 100, "", false, "Immunities:", false, 36);
        items->push_back(debuffImmunes);


        std::string tempType = focusEnemy->getElementalString(1);
        int tempr = 0, tempg = 0, tempb = 0;
        focusEnemy->getRGB(tempType, &tempr, &tempg, &tempb);
        DrawInformation fireText(1125, 200, 200, 50, "", false, tempType, true, 36, tempr, tempg, tempb);
        items->push_back(fireText);

        tempType = focusEnemy->getElementalString(2);
        focusEnemy->getRGB(tempType, &tempr, &tempg, &tempb);
        DrawInformation iceText(1125, 250, 200, 50, "", false, tempType, true, 36, tempr, tempg, tempb);
        items->push_back(iceText);

        tempType = focusEnemy->getElementalString(3);
        focusEnemy->getRGB(tempType, &tempr, &tempg, &tempb);
        DrawInformation lightningText(1125, 300, 200, 50, "", false, tempType, true, 36, tempr, tempg, tempb);
        items->push_back(lightningText);

        tempType = focusEnemy->getElementalString(4);
        focusEnemy->getRGB(tempType, &tempr, &tempg, &tempb);
        DrawInformation waterText(1125, 350, 200, 50, "", false, tempType, true, 36, tempr, tempg, tempb);
        items->push_back(waterText);

        tempType = focusEnemy->getElementalString(5);
        focusEnemy->getRGB(tempType, &tempr, &tempg, &tempb);
        DrawInformation windText(1125, 400, 200, 50, "", false, tempType, true, 36, tempr, tempg, tempb);
        items->push_back(windText);

        tempType = focusEnemy->getElementalString(6);
        focusEnemy->getRGB(tempType, &tempr, &tempg, &tempb);
        DrawInformation earthText(1125, 450, 200, 50, "", false, tempType, true, 36, tempr, tempg, tempb);
        items->push_back(earthText);

        tempType = focusEnemy->getElementalString(7);
        focusEnemy->getRGB(tempType, &tempr, &tempg, &tempb);
        DrawInformation bashText(1125, 100, 200, 50, "", false, tempType, true, 36, tempr, tempg, tempb);
        items->push_back(bashText);

        tempType = focusEnemy->getElementalString(8);
        focusEnemy->getRGB(tempType, &tempr, &tempg, &tempb);
        DrawInformation slashText(1125, 50, 200, 50, "", false, tempType, true, 36, tempr, tempg, tempb);
        items->push_back(slashText);

        tempType = focusEnemy->getElementalString(9);
        focusEnemy->getRGB(tempType, &tempr, &tempg, &tempb);
        DrawInformation pierceText(1125, 150, 200, 50, "", false, tempType, true, 36, tempr, tempg, tempb);
        items->push_back(pierceText);

        return;
    }

    DrawInformation info7(25 + ((cursorPos/34) * 300), 25 + ((cursorPos%34)*25), 100, 100, "", false, ">", true, 24.f);
    items->push_back(info7);

    for(int i = 0; i < names.size(); i++)
    {
        DrawInformation info2(50 + ((i/34) * 300), 25 + ((i%34) * 25), 200, 100, "", false, std::to_string(i+1) + ": " + names.at(i), true, 24.f);
        items->push_back(info2);
    }
}

bool PauseMenuStateMonsterManual::isMain()
{
    return false;
}

void PauseMenuStateMonsterManual::speicalMessage(std::string message)
{

}
