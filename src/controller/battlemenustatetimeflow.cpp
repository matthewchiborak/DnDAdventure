#include "battlemenustatetimeflow.h"

#include "../display/drawinformation.h"
#include "../model/battlemodel.h"
#include "../model/playercharacterstats.h"
#include "../model/EnemyModel.h"
#include "../controller/battlemenustatemain.h"

#include <chrono>

BattleMenuStateTimeFlow::BattleMenuStateTimeFlow(BattleModel *model)
    : BattleMenuState(model)
{
    auto nowTime = std::chrono::system_clock::now().time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime).count();
    theTimeNow = (millis);
    timeOfLastEvent = theTimeNow;
}

void BattleMenuStateTimeFlow::moveMenuCursor(int x, int y)
{

}

BattleMenuState *BattleMenuStateTimeFlow::enterMenu()
{
    return this;
}

BattleMenuState *BattleMenuStateTimeFlow::closeMenu()
{
    return this;
}

BattleMenuState *BattleMenuStateTimeFlow::passTime(float value)
{
    //Actually do something
    //value will be t just like how movement is done. Maybe. That value might not
    //Even be used.
    //For now. Your speed stat will be how much increase 0-1200 for your speed stat per second
    auto nowTime = std::chrono::system_clock::now().time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime).count();
    theTimeNow =(millis);
    elapsed_millies = theTimeNow - timeOfLastEvent;

    float p1PosBefore = model->getP1TimeLinePos();
    float p2PosBefore = model->getP2TimeLinePos();

    model->setP1TimeLinePos(p1PosBefore + (model->getCharacters()->at(0)->getSpeed() * (elapsed_millies/1000.f)));
    model->setP2TimeLinePos(p2PosBefore + (model->getCharacters()->at(1)->getSpeed() * (elapsed_millies/1000.f)));

    for(int i = 0; i < model->getEnemies()->size(); i++)
    {
        float enPosBefore =  model->getEnemies()->at(i)->getTimeLinePos();
        model->getEnemies()->at(i)->setTimeLinePos(enPosBefore
                                                   + (model->getEnemies()->at(i)->getSpeed() * (elapsed_millies/1000.f)));

        if(model->getEnemies()->at(i)->getTimeLinePos() >= 1200)
            model->getEnemies()->at(i)->setTimeLinePos(0);
    }

    //Thats why it was always speeding up
    timeOfLastEvent = theTimeNow;

    if(p1PosBefore < 1000 && model->getP1TimeLinePos() >= 1000)
        return new BattleMenuStateMain(model);
    if(p2PosBefore < 1000 && model->getP2TimeLinePos() >= 1000)
        return new BattleMenuStateMain(model);

    if(model->getP1TimeLinePos() >= 1200)
        model->setP1TimeLinePos(0);
    if(model->getP2TimeLinePos() >= 1200)
        model->setP2TimeLinePos(0);

    return this;
}

void BattleMenuStateTimeFlow::drawBattleMenu(std::vector<DrawInformation> *items)
{
    //Character portraits
    //images first
    DrawInformation port1(-300, -275, 150, 150, model->getCharacters()->at(0)->getMenuSpriteKey(), false);
    items->push_back(port1);
    DrawInformation port2(250, -275, 150, 150, model->getCharacters()->at(1)->getMenuSpriteKey(), false);
    items->push_back(port2);

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
}
