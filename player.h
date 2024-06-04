#ifndef PLAYER_H
#define PLAYER_H

#include "hero.h"
#include <QVector>

class Player
{
public:
    Player();
    bool addHero(Hero *hero);
    void addHeroInBattleField(Hero *hero);
    void deleteHeroInBattleField(int index);
    Hero *getHero(int index);
    Hero *getHeroInBattleField(int index);
    int getHeroInBattleFieldSize();
    void swapHeroesInBattleField(int i, int j);
    void setMoney(int addMoney);
    unsigned int  getMoney();
    void battleEnd();
private:
    QVector<Hero*> heroesInBattleField;
    QVector<Hero*> heroes;
    unsigned int money;
};

#endif // PLAYER_H
