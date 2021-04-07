#include "battlemodel.h"

#include "../factory/encounterfactory.h"
#include "../display/drawinformation.h"
#include "playercharacterstats.h"

#include <QDir>
#include <QDebug>

BattleModel::BattleModel()
{
    QDir dir(QDir::current());
    dir.cdUp();
    //Get the image location from the other map, create and store the flyweight
    std::string encounterFilepath = dir.path().toStdString()+ "/DnDAdventure/src/test/encounters.txt";


    this->encounterFact = new EncounterFactory(encounterFilepath);
}

void BattleModel::clear()
{
    //Clear the vectory. Reset timeline position
    for(int i = 0; i < enemies.size(); i++)
    {
        delete enemies.at(i);
    }
    enemies.clear();
}

void BattleModel::load(std::string key, std::vector<PlayerCharacterStats *> *characters)
{
    this->characters = characters;

    clear();

    encounterFact->populate(&enemies, key);
}

void BattleModel::draw(std::vector<DrawInformation> *items)
{
    //Timeline
    DrawInformation timeline(-600, -70, 1200, 20, "TimeLine", false);
    items->push_back(timeline);

    //TODO get a background into the board file? Or encounter file?
    DrawInformation player1(-300, 100, 200, 200, characters->at(0)->getSpriteKey(), false);
    items->push_back(player1);
    DrawInformation player2(-500, 0, 200, 200, characters->at(1)->getSpriteKey(), false);
    items->push_back(player2);

    DrawInformation player1TL(-100, -60, 36, 48, characters->at(0)->getTimelineSpriteKey(), false);
    items->push_back(player1TL);
    DrawInformation player2TL(-500, -60, 36, 48, characters->at(1)->getTimelineSpriteKey(), false);
    items->push_back(player2TL);

    for(int i = 0; i < enemies.size(); i++)
    {
        if(i == 0)
        {
            DrawInformation en(300, 50, 200, 200, enemies.at(i)->getSpriteKey(), false);
            items->push_back(en);
            DrawInformation enTL(-100, -108, 36, 48, "Enemy1TimeLine", false);
            items->push_back(enTL);
        }
        else if(i == 1)
        {
            DrawInformation en(100, 0, 200, 200, enemies.at(i)->getSpriteKey(), false);
            items->push_back(en);
            DrawInformation enTL(100, -108, 36, 48, "Enemy2TimeLine", false);
            items->push_back(enTL);
        }
        else if(i == 2)
        {
            DrawInformation en(500, 0, 200, 200, enemies.at(i)->getSpriteKey(), false);
            items->push_back(en);
            DrawInformation enTL(200, -108, 36, 48, "Enemy3TimeLine", false);
            items->push_back(enTL);
        }
        else if(i == 3)
        {
            DrawInformation en(100, 200, 200, 200, enemies.at(i)->getSpriteKey(), false);
            items->push_back(en);
            DrawInformation enTL(300, -108, 36, 48, "Enemy4TimeLine", false);
            items->push_back(enTL);
        }
        else if(i == 4)
        {
            DrawInformation en(500, 200, 200, 200, enemies.at(i)->getSpriteKey(), false);
            items->push_back(en);
            DrawInformation enTL(-400, -108, 36, 48, "Enemy5TimeLine", false);
            items->push_back(enTL);
        }
    }




    //Bottem menu
    DrawInformation menuBG(-750, -405, 1600, 290, "BattleMenuBG", false);
    items->push_back(menuBG);

    //Party guage
    DrawInformation pg(-400, -395, 50, 270, "PartyGauge", false);
    items->push_back(pg);
    DrawInformation pgtop(-400, -395, 50, 270, "PartyGaugeTop", false);
    items->push_back(pgtop);

    //Top Text Box
    DrawInformation topTextBox(-700, 350, 1500, 140, "BattleMenuBG", false);
    items->push_back(topTextBox);

    //Character portraits
    //images first
    DrawInformation port1(-300, -275, 150, 150, characters->at(0)->getMenuSpriteKey(), false);
    items->push_back(port1);
    DrawInformation port2(250, -275, 150, 150, characters->at(1)->getMenuSpriteKey(), false);
    items->push_back(port2);

    //TEXT IS LAST
    //DrawInformation attackText(-750, -400, 200, 75, "", false, "Attack");
    DrawInformation attackText(100, 637, 200, 75, "", false, "Attack", true);
    items->push_back(attackText);
    DrawInformation specialText(100, 697, 200, 75, "", false, "Special", true);
    items->push_back(specialText);
    DrawInformation partyText(100, 757, 200, 75, "", false, "Party", true);
    items->push_back(partyText);
    DrawInformation fleeText(100, 817, 200, 75, "", false, "Flee", true);
    items->push_back(fleeText);
    DrawInformation mainCursor(50, 643 + (0 * 60), 75, 75, "", false, ">", true);
    items->push_back(mainCursor);

    //Default menu text
    DrawInformation p1Name(625, 620, 300, 75, "", false, characters->at(0)->getName(), true);
    items->push_back(p1Name);
    DrawInformation p1hp(625, 670, 300, 75, "", false,
                         "HP: " + std::to_string(characters->at(0)->getCurrentHealth()) + "/"
                         + std::to_string(characters->at(0)->getMaxHealth())
                         , true);
    items->push_back(p1hp);
    DrawInformation p1mp(625, 720, 300, 75, "", false,
                         "MP: " + std::to_string(characters->at(0)->getCurrentMP()) + "/"
                         + std::to_string(characters->at(0)->getMaxMP())
                         , true);
    items->push_back(p1mp);
    DrawInformation p2Name(625 + 550, 620, 300, 75, "", false, characters->at(1)->getName(), true);
    items->push_back(p2Name);
    DrawInformation p2hp(625 + 550, 670, 300, 75, "", false,
                         "HP: " + std::to_string(characters->at(1)->getCurrentHealth()) + "/"
                         + std::to_string(characters->at(1)->getMaxHealth())
                         , true);
    items->push_back(p2hp);
    DrawInformation p2mp(625 + 550, 720, 300, 75, "", false,
                         "MP: " + std::to_string(characters->at(1)->getCurrentMP()) + "/"
                         + std::to_string(characters->at(1)->getMaxMP())
                         , true);
    items->push_back(p2mp);
}

void BattleModel::passTime(float value)
{


}
