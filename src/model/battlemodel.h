#ifndef BATTLEMODEL_H
#define BATTLEMODEL_H

#include <vector>
#include <string>
#include <queue>
#include "../controller/battlemenustate.h"
#include "../display/aboveheadbattlemessage.h"
#include <map>
#include "../controller/musiccontrollerabstract.h"

class PlayerCharacterStats;
class DrawInformation;
class EnemyModel;
class AttackModel;
class EncounterFactory;
class PlayerCharacterStatsBattle;
class MonsterManualEntry;


class BattleModel
{
public:
    BattleModel();

    void clear();
    void load(std::string key, std::vector<PlayerCharacterStats*> * charactersInput, int *partyGaugeValue
              , int * numberOfPotions, int * numberOfRemedies, int * numberOfEthers, int * numberOfJars,
              int * goldCount, std::vector<MonsterManualEntry> * monsterManual, bool isFleeable = true);
    void draw(std::vector<DrawInformation> * items);
    void passTime(float value);
    void qrPressed(bool wasQ);

    void moveMenuCursor(int x, int y);
    void enterMenu();
    void closeMenu();

    std::vector<PlayerCharacterStatsBattle*> * getCharacters();
    std::vector<EnemyModel*> * getEnemies();
    float getP1TimeLinePos();
    float getP2TimeLinePos();
    void setP1TimeLinePos(float value);
    void setP2TimeLinePos(float value);
    int getFocusPartyMember();
    void setFocusPartyMember(int index);

    void applyAttack(PlayerCharacterStatsBattle * attacker,
                     EnemyModel * defender,
                     AttackModel * attack
                     );
    void applyAttack(EnemyModel * attacker,
                     PlayerCharacterStatsBattle * defender,
                     AttackModel * attack
                     );
    void applyAttack(PlayerCharacterStatsBattle * attacker,
                     PlayerCharacterStatsBattle * defender,
                     AttackModel * attack
                     );
    void applyAttack(EnemyModel * attacker,
                     EnemyModel * defender,
                     AttackModel * attack
                     );
    void applyAttackAllEnemies(PlayerCharacterStatsBattle * attacker, AttackModel * attack);
    void applyAttackAllAllies(PlayerCharacterStatsBattle * attacker, AttackModel * attack);
    void applyAttackAllEnemies(EnemyModel * attacker, AttackModel * attack);
    void applyAttackAllAllies(EnemyModel * attacker, AttackModel * attack);

    void checkIfNeedToSwapDeadCharacters();

    bool isTheBattleDone();
    bool isGameOver();
    int getNumberOfEnemies();
    void setBattleIsDoneManual(bool status);
    void setGameIsOverManual(bool status);

    void displayMessage(std::string message);
    void forceClearDisplayMessage();

    void addAboveHeadBattleMessage(bool enemy, int index, std::string key, std::string text, int duration, int element);

    void incrementPartyGauge(bool isAttacking);

    int getPartyGaugeValue();
    void changePartyGaugeValue(int amount);

    void activateSuper(int focusCharacter);

    void setEnemyToAccess(int index);
    EnemyModel * getEnemyToAccess();

    int getLastXPEarned();

    int getNumberOfPotions();
    int getNumberOfRemedies();
    void useAPotion();
    void useARemedy();
    int getNumberOfEthers();
    int getNumberOfJars();
    void useAEther();
    void useAJar();

    void addAdvanceDialogLine(std::string line);
    std::queue<std::string> * getAdvanceDialogLines();

    int getSpeedValueToGet200PointsPerSecond();

    void setMusicController(MusicControllerAbstract * musicController);

    bool getIsFleeable();

    std::string getCutsceneToPlayOnBattleExit();

private:
    //factory for building the enounter
    EncounterFactory * encounterFact;

    MusicControllerAbstract * musicController;

    int focusPartyMember = 0;
    float timelineP1Pos = 0; // scale of 0-1200. 1000 being the attack time?
    float timelineP2Pos = 0;
    const float timeLineOffset = -618;

    int indexOfEnemyAccesing = 0;

    int * partyGaugeValue;
    const int partyGaugeIncrementAttack = 20;
    const int partyGaugeIncrementHit = 40;

    int * numberOfPotions;
    int * numberOfRemedies;
    int * numberOfEthers;
    int * numberOfJars;
    int * goldCount;

    //vector of enemies
    std::vector<EnemyModel*> enemies;
    int numberOfEnemies = 0;

    std::string backgroundImageKey;

    std::string messageToDisplay;
    const double durationOfMessage = 3000;
    long long theTimeNow;
    long long timeOfLastEvent;
    double elapsed_millies;

    std::vector<PlayerCharacterStatsBattle*> characters;
    BattleMenuState * battleMenuState;

    bool battleIsDone = false;
    bool gameOver = false;
    int lastXPEarned = 0;
    bool enteredBattleOverState = false;

    std::vector<AboveHeadBattleMessage> aboveHeadBattleMessages;
    std::vector<AboveHeadBattleMessage> aboveHeadBattleMessagesText;

    std::queue<std::string> advanceDialogLines;

    std::vector<MonsterManualEntry> * monsterManual;

    bool isFleeable;

    std::string cutsceneToPlayOnBattleExit;

    void checkIfEnemiesAreDead();

    int getElementR(int ele);
    int getElementG(int ele);
    int getElementB(int ele);

    int speedValueToGet200PointsPerSecond;
    void stealSomething();
};

#endif // BATTLEMODEL_H
