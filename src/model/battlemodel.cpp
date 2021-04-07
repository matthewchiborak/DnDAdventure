#include "battlemodel.h"

#include "../factory/encounterfactory.h"

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

void BattleModel::draw(std::vector<DrawInformation> *drawInfo)
{
    //qDebug() << "Time To Draw the battle";
}

void BattleModel::passTime(float value)
{

}
