#include "player.h"

Player::Player()
{
    money = 0;
}

bool Player::addHero( Hero *hero) {
    if (heroes.size() < 3) {
        heroes.append(hero);
        return true;
    } else {
        return false;
    }
}

void Player::addHeroInBattleField(Hero *hero)
{
    if (heroesInBattleField.size() < 3) {
        heroesInBattleField.append(hero);
    }
}
Hero *Player::getHero(int index)
{
    return heroes[index];
}

void Player::deleteHeroInBattleField(int index)
{
    //heroesInBattleField[heroesInBattleField.size() - 1] = nullptr;
    heroesInBattleField.remove(index);
}

Hero *Player::getHeroInBattleField(int index)
{
    return heroesInBattleField[index];
}

int Player::getHeroInBattleFieldSize()
{
    return heroesInBattleField.size();
}

void Player::swapHeroesInBattleField(int i, int j)
{
    Hero *temp = new Hero();
    temp = heroesInBattleField[i];
    heroesInBattleField[i] = heroesInBattleField[j];
    heroesInBattleField[j] = temp;
}

void Player::setMoney(int addMoney)
{
    money += addMoney;
}

unsigned int Player::getMoney()
{
    return money;
}

void Player::battleEnd()
{
    heroesInBattleField.clear();
}
