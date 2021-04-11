#include "battlemodel.h"

#include "../factory/encounterfactory.h"
#include "../display/drawinformation.h"
#include "playercharacterstats.h"
#include "../controller/battlemenustatemain.h"
#include "../controller/battlemenustatetimeflow.h"
#include "playercharacterstatsbattle.h"
#include "attackmodel.h"
#include "../display/aboveheadbattlemessage.h"
#include "../controller/battlemenustatebattleover.h"

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
    gameOver = false;
    enteredBattleOverState = false;
    timelineP1Pos = 0;
    timelineP2Pos = 0;

    while(!advanceDialogLines.empty())
        advanceDialogLines.pop();

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

void BattleModel::load(std::string key, std::vector<PlayerCharacterStats *> *charactersInput, int* partyGaugeValue, int *numberOfPotions, int *numberOfRemedies)
{
    this->partyGaugeValue = partyGaugeValue;
    this->numberOfPotions = numberOfPotions;
    this->numberOfRemedies = numberOfRemedies;

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

    if(characters.at(0)->getCurrentHealth() > 0 && characters.at(0)->getIsVisible())
    {
        DrawInformation player1(-300, 100, 200, 200, characters.at(0)->getSpriteKey(), false);
        items->push_back(player1);
    }
    if(characters.at(1)->getCurrentHealth() > 0 && characters.at(1)->getIsVisible())
    {
        DrawInformation player2(-500, 0, 200, 200, characters.at(1)->getSpriteKey(), false);
        items->push_back(player2);
    }

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
    DrawInformation pg(-400, -395, 50, 270*((float)(*partyGaugeValue)/1000.f), "PartyGauge", false);
    items->push_back(pg);
    DrawInformation pgtop(-400, -395, 50, 270, "PartyGaugeTop", false);
    items->push_back(pgtop);
    DrawInformation pgmarker(-450, -395 + ((270/4) * ((*partyGaugeValue)/250)), 40, 4, "GaugeMarker", false);
    items->push_back(pgmarker);

    //Top Text Box
    elapsed_millies = theTimeNow - timeOfLastEvent;
    if(elapsed_millies < durationOfMessage)
    {
        DrawInformation topTextBox(-700, 350, 1500, 140, "BattleMenuBG", false);
        items->push_back(topTextBox);
    }

    for(int i = 0; i < aboveHeadBattleMessages.size(); i++)
        items->push_back(aboveHeadBattleMessages.at(i));

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
    //DrawInformation attackText(-750, -400, 200, 75, "", false, "Attack"); was 50 previously
    DrawInformation attackText(100, 637, 200, 75, "", false, "Attack", true, 36);
    items->push_back(attackText);
    DrawInformation guardText(100, 677, 200, 75, "", false, "Guard", true, 36);
    items->push_back(guardText);
    DrawInformation specialText(100, 717, 200, 75, "", false, "Special", true, 36);
    items->push_back(specialText);
    DrawInformation partyText(100, 757, 200, 75, "", false, "Party", true, 36);
    items->push_back(partyText);
    DrawInformation itemText(100, 797, 200, 75, "", false, "Items", true, 36);
    items->push_back(itemText);
    DrawInformation fleeText(100, 837, 200, 75, "", false, "Flee", true, 36);
    items->push_back(fleeText);

    for(int i = 0; i < aboveHeadBattleMessagesText.size(); i++)
        items->push_back(aboveHeadBattleMessagesText.at(i));

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

    for(int i = 0; i < aboveHeadBattleMessages.size(); i++)
    {
        if(aboveHeadBattleMessages.at(i).applyTime())
        {
            aboveHeadBattleMessages.erase(aboveHeadBattleMessages.begin() + i);
            i--;
        }
    }
    for(int i = 0; i < aboveHeadBattleMessagesText.size(); i++)
    {
        if(aboveHeadBattleMessagesText.at(i).applyTime())
        {
            aboveHeadBattleMessagesText.erase(aboveHeadBattleMessagesText.begin() + i);
            i--;
        }
    }

    checkIfEnemiesAreDead();
}

void BattleModel::qrPressed(bool wasQ)
{
    battleMenuState->qrPressed(wasQ);
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

    if(rand()%100 > attack->getAccuracy() || defender->getCurrentHealth() <= 0)
    {

        displayMessage(attacker->getName() + "'s attack misses...");
        if(defender->getCurrentHealth() > 0)
            addAboveHeadBattleMessage(true, attacker->getAttackTarget(), "Miss", "", 5000, 0);
        return;
    }

    if(attack->getAttackType() == 0)
    {
        //Phys
        damage = ((((((2.f*((float)attacker->getLevel() + 15.f)) / 5.f) + 2.f)
                  * (float)attack->getPower() * ((float)attacker->getAttack()/(float)defender->getDefence())) / 50.f) + 2)
                * (defender->getElementalMultiplier(attack->getElement()) * (((rand()%15)+85)/100.f));
        //Apply player boosts
        damage *= attacker->getAttackingMultiplier(attack->getElement());

        if(attack->getPower() == 0)
        {
            damage = 0;
            displayMessage(attacker->getName() + " uses " + attack->getName() + "!");
        }
        else
        {
            displayMessage(attacker->getName() + " uses " + attack->getName() + "! " + defender->getName() + " takes " + std::to_string(damage) + " damage");
        }
    }
    else if(attack->getAttackType() == 1)
    {
        //Magic
        damage = ((((((2.f*((float)attacker->getLevel() + 15.f)) / 5.f) + 2.f)
                  * (float)attack->getPower() * ((float)attacker->getMagicAttack()/(float)defender->getMagicDefence())) / 50.f) + 2.f)
                * ((float)defender->getElementalMultiplier(attack->getElement()) * ((rand()%100)/100.f));
        //Apply player boosts
        damage *= attacker->getAttackingMultiplier(attack->getElement());

        if(attack->getPower() == 0)
        {
            damage = 0;
            displayMessage(attacker->getName() + " uses " + attack->getName() + "!");
        }
        else
        {
            displayMessage(attacker->getName() + " uses " + attack->getName() + "! " + defender->getName() + " takes " + std::to_string(damage) + " damage");
        }
    }
    else if(attack->getAttackType() == 2)
    {
        //No stats allies. Just the raw value
        damage = attack->getPower();
        //Apply player boosts
        damage *= attacker->getAttackingMultiplier(attack->getElement());
        displayMessage(attacker->getName() + " uses " + attack->getName() + "!");
    }

    if(attack->getPower() == 0)
        damage = 0;

    defender->changeHealth(-1 * damage);
    if(damage > 0)
        addAboveHeadBattleMessage(true, attacker->getAttackTarget(), "Hurt", std::to_string(damage), 5000, attack->getElement());
    if(damage < 0)
        addAboveHeadBattleMessage(true, attacker->getAttackTarget(), "Heal", std::to_string(-1*damage), 5000, attack->getElement());
    if(defender->applyStatusEffect(attack->getAdditionalEffectRoll()))
        addAboveHeadBattleMessage(true, attacker->getAttackTarget(), attack->getAdditionalEffect(), "", 5000, attack->getElement());
    //else
        //addAboveHeadBattleMessage(true, attacker->getAttackTarget(), "Immune", "", 2000);

    //Try interrupt
    if(damage > 0)
    {
        if(defender->tryInterrupt(500))
        {
            addAboveHeadBattleMessage(true, attacker->getAttackTarget(), "Interrupt", "", 5000, attack->getElement());
        }
    }

}

void BattleModel::applyAttack(EnemyModel *attacker, PlayerCharacterStatsBattle *defender, AttackModel *attack)
{
    int damage = 0;

    if(rand()%100 > attack->getAccuracy() || defender->getCurrentHealth() <= 0)
    {
        displayMessage(attacker->getName() + "'s attack misses...");
        if(defender->getCurrentHealth() > 0)
            addAboveHeadBattleMessage(false, attacker->getAttackTarget(), "Miss", "", 5000, 0);
        return;
    }

    if(attack->getAttackType() == 0)
    {
        //Phys
        damage = ((((((2.f*((float)attacker->getLevel() + 15.f)) / 5.f) + 2.f)
                  * (float)attack->getPower() * ((float)attacker->getAttack()/(float)defender->getDefence())) / 50.f) + 2)
                * (defender->getElementalMultiplier(attack->getElement()) * (((rand()%15)+85)/100.f));
        damage *= defender->getDefendingMultiplier(attack->getElement());

        if(attack->getPower() == 0)
        {
            damage = 0;
            displayMessage(attacker->getName() + " uses " + attack->getName() + "!");
        }
        else
        {
            displayMessage(attacker->getName() + " uses " + attack->getName() + "! " + defender->getName() + " takes " + std::to_string(damage) + " damage");
        }
    }
    else if(attack->getAttackType() == 1)
    {
        //Magic
        damage = ((((((2.f*((float)attacker->getLevel() + 15.f)) / 5.f) + 2.f)
                  * (float)attack->getPower() * ((float)attacker->getMagicAttack()/(float)defender->getMagicDefence())) / 50.f) + 2.f)
                * ((float)defender->getElementalMultiplier(attack->getElement()) * ((rand()%100)/100.f));
        damage *= defender->getDefendingMultiplier(attack->getElement());

        if(attack->getPower() == 0)
        {
            damage = 0;
            displayMessage(attacker->getName() + " uses " + attack->getName() + "!");
        }
        else
        {
            displayMessage(attacker->getName() + " uses " + attack->getName() + "! " + defender->getName() + " takes " + std::to_string(damage) + " damage");
        }
    }
    else if(attack->getAttackType() == 2)
    {
        //No stats allies. Just the raw value
        damage = attack->getPower();
        damage *= defender->getDefendingMultiplier(attack->getElement());
        displayMessage(attacker->getName() + " uses " + attack->getName() + "!");
    }

    defender->changeCurrentHealth(-1 * damage);
    if(damage > 0)
        addAboveHeadBattleMessage(false, attacker->getAttackTarget(), "Hurt", std::to_string(damage), 5000, attack->getElement());
    if(damage < 0)
        addAboveHeadBattleMessage(false, attacker->getAttackTarget(), "Heal", std::to_string(-1*damage), 5000, attack->getElement());
    if(defender->applyStatusEffect(attack->getAdditionalEffectRoll()))
        addAboveHeadBattleMessage(false, attacker->getAttackTarget(), attack->getAdditionalEffect(), "", 5000, attack->getElement());

    //Try interrupt
    if(damage > 0)
    {
        if(defender->getIsCasting())
        {
            if(attacker->getAttackTarget() == 0)
            {
                defender->stopCasting();
                timelineP1Pos -= 500;
            }
            else
            {
                defender->stopCasting();
                timelineP2Pos -= 500;
            }

            addAboveHeadBattleMessage(false, attacker->getAttackTarget(), "Interrupt", "", 5000, attack->getElement());
        }
    }


}

void BattleModel::applyAttack(PlayerCharacterStatsBattle *attacker, PlayerCharacterStatsBattle *defender, AttackModel *attack)
{
    int damage = 0;

    if(rand()%100 > attack->getAccuracy() || defender->getCurrentHealth() <= 0)
    {
        displayMessage(attacker->getName() + "'s attack misses...");
        if(defender->getCurrentHealth() > 0)
            addAboveHeadBattleMessage(false, attacker->getAttackTarget(), "Miss", "", 5000, 0);
        return;
    }

    if(attack->getAttackType() == 0)
    {
        //Phys
        damage = ((((((2.f*((float)attacker->getLevel() + 15.f)) / 5.f) + 2.f)
                  * (float)attack->getPower() * ((float)attacker->getAttack()/(float)defender->getDefence())) / 50.f) + 2)
                * (defender->getElementalMultiplier(attack->getElement()) * (((rand()%15)+85)/100.f));
        damage *= attacker->getAttackingMultiplier(attack->getElement()) * defender->getDefendingMultiplier(attack->getElement());

        if(attack->getPower() == 0)
        {
            damage = 0;
            displayMessage(attacker->getName() + " uses " + attack->getName() + "!");
        }
        else
        {
            displayMessage(attacker->getName() + " uses " + attack->getName() + "! " + defender->getName() + " takes " + std::to_string(damage) + " damage");
        }
    }
    else if(attack->getAttackType() == 1)
    {
        //Magic
        damage = ((((((2.f*((float)attacker->getLevel() + 15.f)) / 5.f) + 2.f)
                  * (float)attack->getPower() * ((float)attacker->getMagicAttack()/(float)defender->getMagicDefence())) / 50.f) + 2.f)
                * ((float)defender->getElementalMultiplier(attack->getElement()) * ((rand()%100)/100.f));
        damage *= attacker->getAttackingMultiplier(attack->getElement()) * defender->getDefendingMultiplier(attack->getElement());

        if(attack->getPower() == 0)
        {
            damage = 0;
            displayMessage(attacker->getName() + " uses " + attack->getName() + "!");
        }
        else
        {
            displayMessage(attacker->getName() + " uses " + attack->getName() + "! " + defender->getName() + " takes " + std::to_string(damage) + " damage");
        }
    }
    else if(attack->getAttackType() == 2)
    {
        //No stats allies. Just the raw value
        damage = attack->getPower();
        damage *= attacker->getAttackingMultiplier(attack->getElement()) * defender->getDefendingMultiplier(attack->getElement());
        displayMessage(attacker->getName() + " uses " + attack->getName() + "!");
    }



    defender->changeCurrentHealth(-1 * damage);
    if(damage > 0)
        addAboveHeadBattleMessage(false, attacker->getAttackTarget(), "Hurt", std::to_string(damage), 5000, attack->getElement());
    if(damage < 0)
        addAboveHeadBattleMessage(false, attacker->getAttackTarget(), "Heal", std::to_string(-1 * damage), 5000, attack->getElement());

    if(defender->applyStatusEffect(attack->getAdditionalEffectRoll()))
        addAboveHeadBattleMessage(false, attacker->getAttackTarget(), attack->getAdditionalEffect(), "", 5000, attack->getElement());

    //Try interrupt
    if(damage > 0)
    {
        if(defender->getIsCasting())
        {
            if(attacker->getAttackTarget() == 0)
            {
                defender->stopCasting();
                timelineP1Pos -= 500;
            }
            else
            {
                defender->stopCasting();
                timelineP2Pos -= 500;
            }
            addAboveHeadBattleMessage(false, attacker->getAttackTarget(), "Interrupt", "", 5000, attack->getElement());
        }
    }
}

void BattleModel::applyAttack(EnemyModel *attacker, EnemyModel *defender, AttackModel *attack)
{
    int damage = 0;

    if(rand()%100 > attack->getAccuracy() || defender->getCurrentHealth() <= 0)
    {
        displayMessage(attacker->getName() + "'s attack misses...");
        if(defender->getCurrentHealth() > 0)
            addAboveHeadBattleMessage(true, attacker->getAttackTarget(), "Miss", "", 5000, 0);
        return;
    }

    if(attack->getAttackType() == 0)
    {
        //Phys
        damage = ((((((2.f*((float)attacker->getLevel() + 15.f)) / 5.f) + 2.f)
                  * (float)attack->getPower() * ((float)attacker->getAttack()/(float)defender->getDefence())) / 50.f) + 2)
                * (defender->getElementalMultiplier(attack->getElement()) * (((rand()%15)+85)/100.f));

        if(attack->getPower() == 0)
        {
            damage = 0;
            displayMessage(attacker->getName() + " uses " + attack->getName() + "!");
        }
        else
        {
            displayMessage(attacker->getName() + " uses " + attack->getName() + "! " + defender->getName() + " takes " + std::to_string(damage) + " damage");
        }
    }
    else if(attack->getAttackType() == 1)
    {
        //Magic
        damage = ((((((2.f*((float)attacker->getLevel() + 15.f)) / 5.f) + 2.f)
                  * (float)attack->getPower() * ((float)attacker->getMagicAttack()/(float)defender->getMagicDefence())) / 50.f) + 2.f)
                * ((float)defender->getElementalMultiplier(attack->getElement()) * ((rand()%100)/100.f));

        if(attack->getPower() == 0)
        {
            damage = 0;
            displayMessage(attacker->getName() + " uses " + attack->getName() + "!");
        }
        else
        {
            displayMessage(attacker->getName() + " uses " + attack->getName() + "! " + defender->getName() + " takes " + std::to_string(damage) + " damage");
        }
    }
    else if(attack->getAttackType() == 2)
    {
        //No stats allies. Just the raw value
        damage = attack->getPower();
        displayMessage(attacker->getName() + " uses " + attack->getName() + "!");
    }

    if(attack->getPower() == 0)
        damage = 0;

    defender->changeHealth(-1 * damage);
    if(damage > 0)
        addAboveHeadBattleMessage(true, attacker->getAttackTarget(), "Hurt", std::to_string(damage), 5000, attack->getElement());
    if(damage < 0)
        addAboveHeadBattleMessage(true, attacker->getAttackTarget(), "Heal", std::to_string(-1 * damage), 5000, attack->getElement());

    if(defender->applyStatusEffect(attack->getAdditionalEffectRoll()))
        addAboveHeadBattleMessage(true, attacker->getAttackTarget(), attack->getAdditionalEffect(), "", 5000, attack->getElement());
    else
        addAboveHeadBattleMessage(true, attacker->getAttackTarget(), "Immune", "", 2000, attack->getElement());

    //Try interrupt
    if(damage > 0)
    {
        if(defender->tryInterrupt(500))
        {
            addAboveHeadBattleMessage(true, attacker->getAttackTarget(), "Interrupt", "", 5000, attack->getElement());
        }
    }
}

void BattleModel::applyAttackAllEnemies(PlayerCharacterStatsBattle * attacker, AttackModel *attack)
{
    for(int i = 0; i < enemies.size(); i++)
    {
        attacker->setTarget(i);
        applyAttack(attacker, enemies.at(i), attack);
    }
}

void BattleModel::applyAttackAllAllies(PlayerCharacterStatsBattle * attacker, AttackModel *attack)
{
    attacker->setTarget(0);
    applyAttack(attacker, characters.at(0), attack);
    attacker->setTarget(1);
    applyAttack(attacker, characters.at(1), attack);
}

void BattleModel::applyAttackAllEnemies(EnemyModel *attacker, AttackModel *attack)
{
    for(int i = 0; i < enemies.size(); i++)
    {
        attacker->setTarget(i);
        applyAttack(attacker, enemies.at(i), attack);
    }
}

void BattleModel::applyAttackAllAllies(EnemyModel *attacker, AttackModel *attack)
{
    attacker->setTarget(0);
    applyAttack(attacker, characters.at(0), attack);
    attacker->setTarget(1);
    applyAttack(attacker, characters.at(1), attack);
}

void BattleModel::checkIfNeedToSwapDeadCharacters()
{
    if(characters.at(0)->getCurrentHealth() <= 0)
    {
        if(characters.at(2)->getCurrentHealth() > 0)
        {
            PlayerCharacterStatsBattle * temp1 = characters.at(0);
            PlayerCharacterStatsBattle * temp2 = characters.at(2);
            characters.at(0) = temp2;
            characters.at(2) = temp1;
        }
        else if(characters.at(3)->getCurrentHealth() > 0)
        {
            PlayerCharacterStatsBattle * temp1 = characters.at(0);
            PlayerCharacterStatsBattle * temp2 = characters.at(3);
            characters.at(0) = temp2;
            characters.at(3) = temp1;
        }
    }
    if(characters.at(1)->getCurrentHealth() <= 0)
    {
        if(characters.at(2)->getCurrentHealth() > 0)
        {
            PlayerCharacterStatsBattle * temp1 = characters.at(1);
            PlayerCharacterStatsBattle * temp2 = characters.at(2);
            characters.at(0) = temp2;
            characters.at(2) = temp1;
        }
        else if(characters.at(3)->getCurrentHealth() > 0)
        {
            PlayerCharacterStatsBattle * temp1 = characters.at(1);
            PlayerCharacterStatsBattle * temp2 = characters.at(3);
            characters.at(1) = temp2;
            characters.at(3) = temp1;
        }
    }
//    if(characters.at(0)->getCurrentHealth() <= 0 && characters.at(1)->getCurrentHealth() <= 0)
//    {
//        if(characters.at(2)->getCurrentHealth() > 0 && characters.at(3)->getCurrentHealth() > 0)
//        {
//            PlayerCharacterStatsBattle * temp1 = characters.at(0);
//            PlayerCharacterStatsBattle * temp2 = characters.at(2);
//            characters.at(0) = temp2;
//            characters.at(2) = temp1;
//            PlayerCharacterStatsBattle * temp4 = characters.at(1);
//            PlayerCharacterStatsBattle * temp3 = characters.at(3);
//            characters.at(1) = temp3;
//            characters.at(3) = temp4;
//        }
//        else if(characters.at(2)->getCurrentHealth() > 0 && characters.at(3)->getCurrentHealth() <= 0)
//        {
//            PlayerCharacterStatsBattle * temp1 = characters.at(recentTarget);
//            PlayerCharacterStatsBattle * temp2 = characters.at(2);
//            characters.at(recentTarget) = temp2;
//            characters.at(2) = temp1;
//        }
//        else if(characters.at(2)->getCurrentHealth() <= 0 && characters.at(3)->getCurrentHealth() > 0)
//        {
//            PlayerCharacterStatsBattle * temp1 = characters.at(recentTarget);
//            PlayerCharacterStatsBattle * temp2 = characters.at(3);
//            characters.at(recentTarget) = temp2;
//            characters.at(3) = temp1;
//        }
//    }
}

bool BattleModel::isTheBattleDone()
{
    return battleIsDone;
}

bool BattleModel::isGameOver()
{
    return gameOver;
}

int BattleModel::getNumberOfEnemies()
{
    return numberOfEnemies;
}

void BattleModel::setBattleIsDoneManual(bool status)
{
    battleIsDone = status;
}

void BattleModel::setGameIsOverManual(bool status)
{
    gameOver = status;
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
    messageToDisplay = "";
    auto nowTime = std::chrono::system_clock::now().time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime).count();
    timeOfLastEvent =(millis) - durationOfMessage;
}

void BattleModel::addAboveHeadBattleMessage(bool enemy, int index, std::string key, std::string text, int duration, int element)
{
    duration = 1000;

    int textX;
    int textY;
    int textW=200;
    int textH=75;

    if(enemy)
    {
        if(index == 0)
        {
            textX = 700+300+50;
            textY = 300+50-25;
        }
        else if(index == 1)
        {
            textX = 700+100+50;
            textY = 200+200-25;
        }
        else if(index == 2)
        {
            textX = 700+500+50;
            textY = 200+200-25;
        }
        else if(index == 3)
        {
            textX = 700+100+50;
            textY = 200+0-25;
        }
        else if(index == 4)
        {
            textX = 700+500+50;
            textY = 200+0-25;
        }
    }
    else
    {
        if(index == 0)
        {
            textX = 450;
            textY = 250;
        }
        else if(index == 1)
        {
            textX = 250;
            textY = 350;
        }
    }



    if(key == "Miss")
    {
        AboveHeadBattleMessage newMes(duration,
                                      textX,
                                      textY,
                                      textW,
                                      textH,
                                      "",
                                      false,
                                      "MISS"
                                      );
        aboveHeadBattleMessagesText.push_back(newMes);
    }
    else if(key == "Hurt")
    {
        AboveHeadBattleMessage newMes(duration,
                                      textX,
                                      textY,
                                      textW,
                                      textH,
                                      "",
                                      false,
                                      text,
                                      false,
                                      48.f,
                                      getElementR(element),
                                      getElementG(element),
                                      getElementB(element)
                                      );
        aboveHeadBattleMessagesText.push_back(newMes);
    }
    else if(key == "Heal")
    {
        AboveHeadBattleMessage newMes(duration,
                                      textX,
                                      textY,
                                      textW,
                                      textH,
                                      "",
                                      false,
                                      text,
                                      false,
                                      48.f,
                                      0,
                                      255
                                      );
        aboveHeadBattleMessagesText.push_back(newMes);
    }
    else if(key == "Interrupt")
    {
        AboveHeadBattleMessage newMes(2000,
                                      textX,
                                      textY+75,
                                      textW,
                                      textH,
                                      "",
                                      false,
                                      "INTERRUPT",
                                      false,
                                      36,
                                      120,120,120
                                      );
        aboveHeadBattleMessagesText.push_back(newMes);
    }
    else if(key == "Poison"
            || key == "Sleep"
            || key == "Silence"
            || key == "Immune"
            )
    {
        AboveHeadBattleMessage newMes(2000,
                                      textX,
                                      textY-75,
                                      textW,
                                      textH,
                                      "",
                                      false,
                                      key,
                                      false,
                                      36,
                                      128,0,128
                                      );
        aboveHeadBattleMessagesText.push_back(newMes);
    }
    else if(key == "AttackUp"
            || key == "DefenceUp"
            || key == "MagicUp"
            || key == "MagicDefenceUp"
            || key == "Haste"
            )
    {
        AboveHeadBattleMessage newMes(2000,
                                      textX,
                                      textY-75,
                                      textW,
                                      textH,
                                      "",
                                      false,
                                      key,
                                      false,
                                      36,
                                      0,255,255
                                      );
        aboveHeadBattleMessagesText.push_back(newMes);
    }
    else if(key == "AttackDown"
            || key == "DefenceDown"
            || key == "MagicDown"
            || key == "MagicDefenceDown"
            || key == "Slow"
            )
    {
        AboveHeadBattleMessage newMes(2000,
                                      textX,
                                      textY-75,
                                      textW,
                                      textH,
                                      "",
                                      false,
                                      key,
                                      false,
                                      36,
                                      255,0,0
                                      );
        aboveHeadBattleMessagesText.push_back(newMes);
    }
}

void BattleModel::incrementPartyGauge(bool isAttacking)
{
    if(isAttacking)
        (*partyGaugeValue) = (*partyGaugeValue) + partyGaugeIncrementAttack;
    else
        (*partyGaugeValue) = (*partyGaugeValue) + partyGaugeIncrementHit;

    if((*partyGaugeValue) > 1000)
        (*partyGaugeValue) = 1000;

}

int BattleModel::getPartyGaugeValue()
{
    return (*partyGaugeValue);
}

void BattleModel::changePartyGaugeValue(int amount)
{
    (*partyGaugeValue) = (*partyGaugeValue) + amount;

    if((*partyGaugeValue) < 0)
        (*partyGaugeValue) = 0;
    if((*partyGaugeValue) > 1000)
        (*partyGaugeValue) = 1000;
}

void BattleModel::activateSuper(int focusCharacter)
{
    AttackModel superAttack("Attack,Super_Attack,1,0," + std::to_string(characters.at(focusCharacter)->getLevel() * 50) + ",100,Attack_All_Enemies,0,0,None,1");
    applyAttackAllEnemies(characters.at(focusCharacter), &superAttack);
}

void BattleModel::setEnemyToAccess(int index)
{
    indexOfEnemyAccesing = index;
}

EnemyModel *BattleModel::getEnemyToAccess()
{
    return enemies.at(indexOfEnemyAccesing);
}

int BattleModel::getLastXPEarned()
{
    return lastXPEarned;
}

int BattleModel::getNumberOfPotions()
{
    return (*numberOfPotions);
}

int BattleModel::getNumberOfRemedies()
{
    return (*numberOfRemedies);
}

void BattleModel::useAPotion()
{
    if((*numberOfPotions) > 0)
    {
        (*numberOfPotions) = (*numberOfPotions) - 1;

        for(int i = 0; i < characters.size(); i++)
        {
            if(characters.at(i)->getCurrentHealth() > 0)
            {
                characters.at(i)->changeCurrentHealth(50);
            }
        }
    }
}

void BattleModel::useARemedy()
{
    if((*numberOfRemedies) > 0)
    {
        (*numberOfRemedies) = (*numberOfRemedies) - 1;

        for(int i = 0; i < characters.size(); i++)
        {
            characters.at(i)->cureAllStatusEffects();
        }
    }
}

void BattleModel::addAdvanceDialogLine(std::string line)
{
    advanceDialogLines.push(line);
}

std::queue<std::string> *BattleModel::getAdvanceDialogLines()
{
    return &advanceDialogLines;
}

void BattleModel::checkIfEnemiesAreDead()
{
    if(battleIsDone || enteredBattleOverState)
        return;

    int characterCount = 0;
    int deadCount = 0;
    for(int i = 0; i < characters.size(); i++)
    {
        characterCount++;
        if(characters.at(i)->getCurrentHealth() <= 0)
            deadCount++;
    }

    if(deadCount >= characterCount)
    {
        enteredBattleOverState = true;
        gameOver = true;
        addAdvanceDialogLine("GAME OVER");
        BattleMenuState * temp = battleMenuState;
        battleMenuState = new BattleMenuStateBattleOver(this);
        delete temp;
    }
    else
    {
        checkIfNeedToSwapDeadCharacters();
    }


    int deadEnemyCount = 0;

    for(int i = 0; i < numberOfEnemies; i++)
    {
        if(enemies.at(i)->getCurrentHealth() <= 0)
            deadEnemyCount++;
    }

    if(deadEnemyCount >= numberOfEnemies)
    {
        enteredBattleOverState = true;

        int xpEarned = 0;
        for(int i = 0; i < numberOfEnemies; i++)
        {
            xpEarned += enemies.at(i)->getXP(characters.at(0)->getLevel());
        }

        addAdvanceDialogLine("VICTORY! Experience earned: " + std::to_string(xpEarned));

        for(int i = 0; i < characters.size(); i++)
        {
            if(characters.at(i)->getCurrentHealth() > 0)
            {
                if(characters.at(i)->changeXP(xpEarned))
                {
                    addAdvanceDialogLine(characters.at(i)->getName() + " grew to level " + std::to_string(characters.at(i)->getLevel()) + "!");
                }
            }
        }
        this->lastXPEarned = xpEarned;
        BattleMenuState * temp = battleMenuState;
        battleMenuState = new BattleMenuStateBattleOver(this);
        delete temp;
    }
}

int BattleModel::getElementR(int ele)
{
    if(ele == 0 || ele == 7 || ele == 8 || ele == 9)
        return 255;
    if(ele == 1)
        return 255;
    if(ele == 3)
        return 255;
    if(ele == 6)
        return 210;
    if(ele == -1)
        return 128;

    return 0;
}

int BattleModel::getElementG(int ele)
{
    if(ele == 0 || ele == 7 || ele == 8 || ele == 9)
        return 255;
    if(ele == 2)
        return 255;
    if(ele == 3)
        return 255;
    if(ele == 5)
        return 128;
    if(ele == 6)
        return 180;

    return 0;
}

int BattleModel::getElementB(int ele)
{
    if(ele == 0 || ele == 7 || ele == 8 || ele == 9)
        return 255;
    if(ele == 2)
        return 255;
    if(ele == 4)
        return 255;
    if(ele == 6)
        return 140;
    if(ele == -1)
        return 128;

    return 0;
}
