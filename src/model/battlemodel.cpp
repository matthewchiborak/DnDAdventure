#include "battlemodel.h"

#include "../factory/encounterfactory.h"
#include "../display/drawinformation.h"
#include "playercharacterstats.h"
#include "../controller/battlemenustatemain.h"
#include "../controller/battlemenustatetimeflow.h"

#include <QDir>
#include <QDebug>

BattleModel::BattleModel()
{
    QDir dir(QDir::current());
    dir.cdUp();
    //Get the image location from the other map, create and store the flyweight
    std::string encounterFilepath = dir.path().toStdString()+ "/DnDAdventure/src/test/encounters.txt";


    this->encounterFact = new EncounterFactory(encounterFilepath);

    this->battleMenuState = new BattleMenuStateTimeFlow(this);
}

void BattleModel::clear()
{
    //Clear the vectory. Reset timeline position
    for(int i = 0; i < enemies.size(); i++)
    {
        delete enemies.at(i);
    }
    enemies.clear();

    BattleMenuState * temp = battleMenuState;
    this->battleMenuState = new BattleMenuStateTimeFlow(this);
    delete temp;
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

    DrawInformation player1TL((timeLineOffset) + timelineP1Pos, -60, 36, 48, characters->at(0)->getTimelineSpriteKey(), false);
    items->push_back(player1TL);
    DrawInformation player2TL((timeLineOffset) + timelineP2Pos, -60, 36, 48, characters->at(1)->getTimelineSpriteKey(), false);
    items->push_back(player2TL);

    for(int i = 0; i < enemies.size(); i++)
    {
        if(i == 0)
        {
            DrawInformation en(300, 50, 200, 200, enemies.at(i)->getSpriteKey(), false);
            items->push_back(en);
            DrawInformation enTL(timeLineOffset + enemies.at(i)->getTimeLinePos(), -108, 36, 48, "Enemy1TimeLine", false);
            items->push_back(enTL);
        }
        else if(i == 1)
        {
            DrawInformation en(100, 0, 200, 200, enemies.at(i)->getSpriteKey(), false);
            items->push_back(en);
            DrawInformation enTL(timeLineOffset + enemies.at(i)->getTimeLinePos(), -108, 36, 48, "Enemy2TimeLine", false);
            items->push_back(enTL);
        }
        else if(i == 2)
        {
            DrawInformation en(500, 0, 200, 200, enemies.at(i)->getSpriteKey(), false);
            items->push_back(en);
            DrawInformation enTL(timeLineOffset + enemies.at(i)->getTimeLinePos(), -108, 36, 48, "Enemy3TimeLine", false);
            items->push_back(enTL);
        }
        else if(i == 3)
        {
            DrawInformation en(100, 200, 200, 200, enemies.at(i)->getSpriteKey(), false);
            items->push_back(en);
            DrawInformation enTL(timeLineOffset + enemies.at(i)->getTimeLinePos(), -108, 36, 48, "Enemy4TimeLine", false);
            items->push_back(enTL);
        }
        else if(i == 4)
        {
            DrawInformation en(500, 200, 200, 200, enemies.at(i)->getSpriteKey(), false);
            items->push_back(en);
            DrawInformation enTL(timeLineOffset + enemies.at(i)->getTimeLinePos(), -108, 36, 48, "Enemy5TimeLine", false);
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
    //DrawInformation topTextBox(-700, 350, 1500, 140, "BattleMenuBG", false);
    //items->push_back(topTextBox);

    //Draw the dynamic parts of the menu that arn't static
    battleMenuState->drawBattleMenu(items);

    //TEXT IS LAST
    //DrawInformation attackText(-750, -400, 200, 75, "", false, "Attack");
    DrawInformation attackText(100, 637, 200, 75, "", false, "Attack", true, 36);
    items->push_back(attackText);
    DrawInformation guardText(100, 687, 200, 75, "", false, "Guard", true, 36);
    items->push_back(guardText);
    DrawInformation specialText(100, 737, 200, 75, "", false, "Special", true, 36);
    items->push_back(specialText);
    DrawInformation partyText(100, 787, 200, 75, "", false, "Party", true, 36);
    items->push_back(partyText);
    DrawInformation fleeText(100, 837, 200, 75, "", false, "Flee", true, 36);
    items->push_back(fleeText);



}

void BattleModel::passTime(float value)
{
    BattleMenuState * temp = battleMenuState;
    battleMenuState = battleMenuState->passTime(value);
    if(temp != battleMenuState)
        delete temp;
}

void BattleModel::moveMenuCursor(int x, int y)
{
    battleMenuState->moveMenuCursor(x, y);
}

void BattleModel::enterMenu()
{
    BattleMenuState * temp = battleMenuState;
    battleMenuState = battleMenuState->enterMenu();
    if(temp != battleMenuState)
        delete temp;
}

void BattleModel::closeMenu()
{
    BattleMenuState * temp = battleMenuState;
    battleMenuState = battleMenuState->closeMenu();
    if(temp != battleMenuState)
        delete temp;
}

std::vector<PlayerCharacterStats *> *BattleModel::getCharacters()
{
    return characters;
}

std::vector<EnemyModel *> *BattleModel::getEnemies()
{
    return &enemies;
}

float BattleModel::getP1TimeLinePos()
{
    return timelineP1Pos;
}

float BattleModel::getP2TimeLinePos()
{
    return timelineP2Pos;
}

void BattleModel::setP1TimeLinePos(float value)
{
    timelineP1Pos = value;
}

void BattleModel::setP2TimeLinePos(float value)
{
    timelineP2Pos = value;
}
