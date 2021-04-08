#include "battlemodel.h"

#include "../factory/encounterfactory.h"
#include "../display/drawinformation.h"
#include "playercharacterstats.h"
#include "../controller/battlemenustatemain.h"
#include "../controller/battlemenustatetimeflow.h"
#include "playercharacterstatsbattle.h"
#include "attackmodel.h"

#include <QDir>
#include <QDebug>

BattleModel::BattleModel()
{
    QDir dir(QDir::current());
    dir.cdUp();
    //Get the image location from the other map, create and store the flyweight
    std::string encounterFilepath = dir.path().toStdString()+ "/DnDAdventure/src/test/encounters.txt";

    auto nowTime = std::chrono::system_clock::now().time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime).count();
    theTimeNow = (millis);
    timeOfLastEvent = theTimeNow - durationOfMessage;

    this->encounterFact = new EncounterFactory(encounterFilepath);

    this->battleMenuState = new BattleMenuStateTimeFlow(this);
}

void BattleModel::clear()
{
    timeOfLastEvent = theTimeNow - durationOfMessage;

    battleIsDone = false;
    timelineP1Pos = 0;
    timelineP2Pos = 0;

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

void BattleModel::load(std::string key, std::vector<PlayerCharacterStats *> *charactersInput)
{
    for(int i = 0; i < charactersInput->size(); i++)
    {
        PlayerCharacterStatsBattle * temp;
        if(characters.size() > i)
        {
            temp = characters.at(i);
            this->characters.at(i) = new PlayerCharacterStatsBattle(charactersInput->at(i));
            delete temp;
        }
        else
        {
            this->characters.push_back(new PlayerCharacterStatsBattle(charactersInput->at(i)));
        }
    }

    clear();

    numberOfEnemies = encounterFact->populate(&enemies, key);

    //Handle initivate
    //0-500? Lets say
    int maxSpeed = characters.at(0)->getSpeed();
    if(characters.at(1)->getSpeed() > maxSpeed)
        maxSpeed = characters.at(1)->getSpeed();
    for(int i = 0; i < numberOfEnemies; i++)
    {
        if(enemies.at(i)->getSpeed() > maxSpeed)
            maxSpeed = enemies.at(i)->getSpeed();
    }

    setP1TimeLinePos((rand()%500) * (characters.at(0)->getSpeed() / maxSpeed));
    setP2TimeLinePos((rand()%500) * (characters.at(1)->getSpeed() / maxSpeed));
    for(int i = 0; i < numberOfEnemies; i++)
    {
        enemies.at(i)->setTimeLinePos((rand()%500) * ((float)enemies.at(i)->getSpeed() / (float)maxSpeed));
    }
}

void BattleModel::draw(std::vector<DrawInformation> *items)
{
    if(characters.size() < 0)
        return;

    //Timeline
    DrawInformation timeline(-600, -70, 1200, 20, "TimeLine", false);
    items->push_back(timeline);

    //TODO get a background into the board file? Or encounter file?
    DrawInformation player1(-300, 100, 200, 200, characters.at(0)->getSpriteKey(), false);
    items->push_back(player1);
    DrawInformation player2(-500, 0, 200, 200, characters.at(1)->getSpriteKey(), false);
    items->push_back(player2);

    DrawInformation player1TL((timeLineOffset) + timelineP1Pos, -60, 36, 48, characters.at(0)->getTimelineSpriteKey(), false);
    items->push_back(player1TL);
    DrawInformation player2TL((timeLineOffset) + timelineP2Pos, -60, 36, 48, characters.at(1)->getTimelineSpriteKey(), false);
    items->push_back(player2TL);

    for(int i = 0; i < enemies.size(); i++)
    {
        if(i == 0 && enemies.at(i)->getCurrentHealth() > 0)
        {
            DrawInformation en(300, 50, 200, 200, enemies.at(i)->getSpriteKey(), false);
            items->push_back(en);
            DrawInformation enTL(timeLineOffset + enemies.at(i)->getTimeLinePos(), -108, 36, 48, "Enemy1TimeLine", false);
            items->push_back(enTL);
        }
        else if(i == 1 && enemies.at(i)->getCurrentHealth() > 0)
        {
            DrawInformation en(100, 0, 200, 200, enemies.at(i)->getSpriteKey(), false);
            items->push_back(en);
            DrawInformation enTL(timeLineOffset + enemies.at(i)->getTimeLinePos(), -108, 36, 48, "Enemy2TimeLine", false);
            items->push_back(enTL);
        }
        else if(i == 2 && enemies.at(i)->getCurrentHealth() > 0)
        {
            DrawInformation en(500, 0, 200, 200, enemies.at(i)->getSpriteKey(), false);
            items->push_back(en);
            DrawInformation enTL(timeLineOffset + enemies.at(i)->getTimeLinePos(), -108, 36, 48, "Enemy3TimeLine", false);
            items->push_back(enTL);
        }
        else if(i == 3 && enemies.at(i)->getCurrentHealth() > 0)
        {
            DrawInformation en(100, 200, 200, 200, enemies.at(i)->getSpriteKey(), false);
            items->push_back(en);
            DrawInformation enTL(timeLineOffset + enemies.at(i)->getTimeLinePos(), -108, 36, 48, "Enemy4TimeLine", false);
            items->push_back(enTL);
        }
        else if(i == 4 && enemies.at(i)->getCurrentHealth() > 0)
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
    elapsed_millies = theTimeNow - timeOfLastEvent;
    if(elapsed_millies < durationOfMessage)
    {
        DrawInformation topTextBox(-700, 350, 1500, 140, "BattleMenuBG", false);
        items->push_back(topTextBox);
    }

    //Draw the dynamic parts of the menu that arn't static
    battleMenuState->drawBattleMenu(items);

    if(elapsed_millies < durationOfMessage)
    {
        DrawInformation attackDesc(0, 10, 1500, 140, "",
                                   false,
                                   messageToDisplay
                                   );
        items->push_back(attackDesc);
    }

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
    auto nowTime = std::chrono::system_clock::now().time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime).count();
    theTimeNow =(millis);

    BattleMenuState * temp = battleMenuState;
    battleMenuState = battleMenuState->passTime(value);
    if(temp != battleMenuState)
        delete temp;

    checkIfEnemiesAreDead();
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

std::vector<PlayerCharacterStatsBattle *> *BattleModel::getCharacters()
{
    return &characters;
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

int BattleModel::getFocusPartyMember()
{
    return focusPartyMember;
}

void BattleModel::setFocusPartyMember(int index)
{
    focusPartyMember = index;
}

void BattleModel::applyAttack(PlayerCharacterStatsBattle *attacker, EnemyModel *defender, AttackModel *attack)
{
    int damage = 0;

    if(attack->getAttackType() == 0)
    {
        //Phys
        damage = ((((((2.f*((float)attacker->getLevel() + 15.f)) / 5.f) + 2.f)
                  * (float)attack->getPower() * ((float)attacker->getAttack()/(float)defender->getDefence())) / 50.f) + 2)
                * (defender->getElementalMultiplier(attack->getElement()) * (((rand()%15)+85)/100.f));

        displayMessage(attacker->getName() + " uses " + attack->getName() + "! " + defender->getName() + " takes " + std::to_string(damage) + " damage");
    }
    else if(attack->getAttackType() == 1)
    {
        //Magic
        damage = ((((((2.f*((float)attacker->getLevel() + 15.f)) / 5.f) + 2.f)
                  * (float)attack->getPower() * ((float)attacker->getMagicAttack()/(float)defender->getMagicDefence())) / 50.f) + 2.f)
                * ((float)defender->getElementalMultiplier(attack->getElement()) * ((rand()%100)/100.f));

        displayMessage(attacker->getName() + " uses " + attack->getName() + "! " + defender->getName() + " takes " + std::to_string(damage) + " damage");
    }

    defender->changeHealth(-1 * damage);

}

void BattleModel::applyAttack(EnemyModel *attacker, PlayerCharacterStatsBattle *defender, AttackModel *attack)
{
    int damage = 0;

    if(attack->getAttackType() == 0)
    {
        //Phys
        damage = ((((((2.f*((float)attacker->getLevel() + 15.f)) / 5.f) + 2.f)
                  * (float)attack->getPower() * ((float)attacker->getAttack()/(float)defender->getDefence())) / 50.f) + 2)
                * (defender->getElementalMultiplier(attack->getElement()) * (((rand()%15)+85)/100.f));

        displayMessage(attacker->getName() + " uses " + attack->getName() + "! " + defender->getName() + " takes " + std::to_string(damage) + " damage");
    }
    else if(attack->getAttackType() == 1)
    {
        //Magic
        damage = ((((((2.f*((float)attacker->getLevel() + 15.f)) / 5.f) + 2.f)
                  * (float)attack->getPower() * ((float)attacker->getMagicAttack()/(float)defender->getMagicDefence())) / 50.f) + 2.f)
                * ((float)defender->getElementalMultiplier(attack->getElement()) * ((rand()%100)/100.f));

        displayMessage(attacker->getName() + " uses " + attack->getName() + "! " + defender->getName() + " takes " + std::to_string(damage) + " damage");
    }

    defender->changeCurrentHealth(-1 * damage);
}

bool BattleModel::isTheBattleDone()
{
    return battleIsDone;
}

int BattleModel::getNumberOfEnemies()
{
    return numberOfEnemies;
}

void BattleModel::displayMessage(std::string message)
{
    messageToDisplay = message;

    auto nowTime = std::chrono::system_clock::now().time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime).count();
    timeOfLastEvent =(millis);
}

void BattleModel::forceClearDisplayMessage()
{
    auto nowTime = std::chrono::system_clock::now().time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime).count();
    timeOfLastEvent =(millis) - durationOfMessage;
}

void BattleModel::checkIfEnemiesAreDead()
{
    int deadEnemyCount = 0;

    for(int i = 0; i < enemies.size(); i++)
    {
        if(enemies.at(i)->getCurrentHealth() <= 0)
            deadEnemyCount++;
    }

    if(deadEnemyCount >= enemies.size())
        battleIsDone = true;
}
