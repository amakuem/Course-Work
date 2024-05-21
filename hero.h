#ifndef HERO_H
#define HERO_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QMovie>
#include <QTimer>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QGraphicsScene>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include "healthbar.h"
#include "mygraphicspixmapitem.h"

class Hero:public QWidget
{
public:
    Hero(QString attack, QString idle, int Damage, int Rotation, int HealthBarX, int HealthBarY);
    void attack(Hero *hero, int X);
    void getDamage(int damage);
    void setPosition(int X, int Y);
    int getPositionX();
    int getPositionY();
    void startAnimation();
    void movingToEnemy(int X);
    void movingReturn();
    QGraphicsPixmapItem *getItemIdle();
    QGraphicsPixmapItem *getItemAttack();
    HealthBar *getHealthBar();
private slots:
    void playAttack(int frameNumber);
    void applyDamage();
    void playIdle();
    void startAttackAnimation();
private:
    QMovie *animationAttack;
    QMovie *animationIdle;
    QGraphicsPixmapItem *itemAttack;
    //QGraphicsPixmapItem *itemIdle;
    MyGraphicsPixmapItem *itemIdle;
    QGraphicsOpacityEffect *opacityEffect;
    int health;
    int damage;
    int x;
    int y;
    int healthBarX;
    int healthBarY;
    double idleScale;
    double attackScale;
    int differenceX;
    int differenceY;
    bool isAlive;
    QTimer *timerAttack;
    QTimer *timerGetDamage;
    short rotation;
    Hero *targetHero;
    HealthBar *healthBar;
};

#endif // HERO_H
