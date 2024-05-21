#ifndef PLAYER_H
#define PLAYER_H

#include "hero.h"

class Player
{
public:
    Player();
private:
    QVector<Hero*> heroes[3];
    unsigned int money;

};

#endif // PLAYER_H
