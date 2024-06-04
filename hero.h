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
#include "artifact.h"

class Hero:public QWidget
{
public:
    Hero(QString PathToIcon, QString attack,double attackScale, QString PathToAttackIcon, QString idle, double idleScale, QString PathToAvatar,int Damage, int Health,int Rotation, int HealthBarX, int HealthBarY, int differenceX, int differenceY, QGraphicsScene *sceneForTips);
    Hero();
    void attack(Hero *hero, int X);
    void getDamage(int damage);
    void setPosition(int X, int Y);
    void fullRecovery();

    int getPositionX();
    int getPositionY();

    void startAnimation();
    void movingToEnemy(int X);
    void movingReturn();

    QGraphicsPixmapItem *getItemIdle();
    QGraphicsPixmapItem *getItemAttack();
    HealthBar *getHealthBar();
    QString getPathToAvatar();
    bool getIsAlive();
    QString getPathToAttackIcon();
    int getHeroDamageValue();
    QString getPathToHeroIcon();

    void addArtifact(Artifact *artifact);
    void replaceArtifact(Artifact *newArtifact, int index);
    int getArtifactsSize();
    Artifact *getArtifact(int index);
private slots:
    void playAttack(int frameNumber);
    void applyDamage();
    void playIdle();
    void startAttackAnimation();
    void heroDie();
private:
    QMovie *animationAttack;
    QMovie *animationIdle;
    QGraphicsPixmapItem *itemAttack;
    //QGraphicsPixmapItem *itemIdle;
    MyGraphicsPixmapItem *itemIdle;
    QGraphicsOpacityEffect *opacityEffect;
    int baseHealth;
    int health;
    double damage;
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
    QTimer *timerDiying;
    short rotation;
    Hero *targetHero;
    HealthBar *healthBar;
    QString pathToAvatar;
    QString pathToAttackIcon;
    QString pathToHeroIcon;
    QVector<Artifact *> artifacts;
};

#endif // HERO_H
