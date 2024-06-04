#include "hero.h"

Hero::Hero(QString PathToIcon, QString attack, double attackScale, QString PathToAttackIcon, QString idle, double idleScale, QString PathToAvatar, int Damage, int Health, int Rotation, int HealthBarX, int HealthBarY, int DifferenceX, int DifferenceY, QGraphicsScene *sceneForTips)
{
    //damage = 10;
    damage = Damage;
    health = Health;
    baseHealth = Health;
    rotation = Rotation;
    healthBarX = HealthBarX;
    healthBarY = HealthBarY;
    pathToAvatar = PathToAvatar;
    differenceX = DifferenceX;
    differenceY = DifferenceY;
    pathToHeroIcon = PathToIcon;
    pathToAttackIcon = PathToAttackIcon;
    animationAttack = new QMovie(attack, QByteArray(), this);
    animationIdle = new QMovie (idle, QByteArray(), this);
    itemAttack = new QGraphicsPixmapItem();
    //itemIdle = new QGraphicsPixmapItem();
    QString stats = "Здоровье: " + QString::number(health) + '\n' + "Урон: " + QString::number(damage);
    itemIdle = new MyGraphicsPixmapItem(sceneForTips, idle, stats);
    timerAttack = new QTimer();
    timerDiying = new QTimer();

    opacityEffect = new QGraphicsOpacityEffect(this);


    isAlive = true;


    itemIdle->setTransformOriginPoint(itemIdle->boundingRect().width() / 2, itemIdle->boundingRect().height() / 2);
    //

    itemIdle->setScale(idleScale); //0.5
    itemAttack->setScale(attackScale);//0.62

    connect(animationAttack, &QMovie::finished, this, &Hero::applyDamage);
    connect(animationAttack, &QMovie::frameChanged, this, &Hero::playAttack);
    connect(animationIdle, &QMovie::frameChanged, this, &Hero::playIdle);
    connect(timerAttack, &QTimer::timeout, this, &Hero::startAttackAnimation);
    connect(timerDiying, &QTimer::timeout, this, &Hero::heroDie);
}

Hero::Hero()
{

}

void Hero::setPosition(int X, int Y)
{
    x = X;
    y = Y;
    itemIdle->setPos(x, y);
    int newHealth = baseHealth;
    for(int i = 0; i < artifacts.size(); i++)
    {
        newHealth = artifacts[i]->makeHealthBuff(newHealth);
    }
    health = newHealth;
    healthBar = new HealthBar(x + healthBarX, y + healthBarY, health);
    //healthBar->setPos(x + healthBarX, y + healthBarY);

}

void Hero::getDamage(int damage)
{
    if(health - damage > 0)
    {
        health -= damage;

        itemIdle->setGraphicsEffect(opacityEffect);
        QPropertyAnimation *animation = new QPropertyAnimation(opacityEffect, "opacity");
        animation->setDuration(1000); // увеличьте продолжительность анимации
        animation->setStartValue(1);
        animation->setKeyValueAt(0.1, 0);
        animation->setKeyValueAt(0.2, 1);
        animation->setKeyValueAt(0.3, 0);
        animation->setKeyValueAt(0.4, 1);
        animation->setKeyValueAt(0.5, 0);
        animation->setKeyValueAt(0.6, 1);
        animation->setKeyValueAt(0.7, 0);
        animation->setKeyValueAt(0.8, 1);
        animation->setKeyValueAt(0.9, 0);
        animation->setEndValue(1);
        animation->start(QAbstractAnimation::DeleteWhenStopped);
        //healthBar->setRect(0, 0, health, 10);
        healthBar->updateHealthBar(health);
    }
    else
    {
        itemIdle->setGraphicsEffect(opacityEffect);
        QPropertyAnimation *animation = new QPropertyAnimation(opacityEffect, "opacity");
        animation->setDuration(1000); // увеличьте продолжительность анимации
        animation->setStartValue(1);
        animation->setKeyValueAt(0.1, 0);
        animation->setKeyValueAt(0.2, 1);
        animation->setKeyValueAt(0.3, 0);
        animation->setKeyValueAt(0.4, 1);
        animation->setKeyValueAt(0.5, 0);
        animation->setKeyValueAt(0.6, 1);
        animation->setKeyValueAt(0.7, 0);
        animation->setKeyValueAt(0.8, 1);
        animation->setKeyValueAt(0.9, 0);
        animation->setEndValue(1);
        animation->start(QAbstractAnimation::DeleteWhenStopped);

        health = 0;
        healthBar->updateHealthBar(health);
        isAlive = false;

        timerDiying->start(1000);
    }
}

void Hero::heroDie()
{
    timerDiying->stop();
    itemIdle->hide();
    itemAttack->hide();
    healthBar->hide();
}

void Hero::attack(Hero *hero, int X)
{
    targetHero = hero;
    healthBar->setVisible(false);
    movingToEnemy(X);
    //hero->getDamage(damage);
}

void Hero::playAttack(int frameNumber)
{
    QTransform transform;
    transform.scale(rotation, 1);
    itemAttack->setPixmap(animationAttack->currentPixmap().transformed(transform));
    if(frameNumber == (animationAttack->frameCount()-1)) {
        animationAttack->stop();
        animationAttack->finished();
        timerAttack->stop();
        itemAttack->hide();
        itemIdle->show();
        movingReturn();
    }
}

void Hero::playIdle()
{
    QTransform transform;
    transform.scale(rotation, 1);
    itemIdle->setPixmap(animationIdle->currentPixmap().transformed(transform));
}

void Hero::movingToEnemy(int X)
{

    QTimeLine *timeLine = new QTimeLine(800);
    timeLine->setFrameRange(0, 100);

    QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
    animation->setItem(itemIdle);
    animation->setTimeLine(timeLine);

    animation->setPosAt(0, itemIdle->pos());
    animation->setPosAt(1, QPointF(X, itemIdle->pos().y()));

    timeLine->start();

    timerAttack->start(800);
    // itemAttack->setScale(0.5);
    // itemAttack->setPos(X, y);
    // animationAttack->start();
}

void Hero::movingReturn()
{
    QTimeLine *timeLine = new QTimeLine(800);
    timeLine->setFrameRange(0, 100);

    QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
    animation->setItem(itemIdle);
    animation->setTimeLine(timeLine);

    animation->setPosAt(0, itemIdle->pos());
    animation->setPosAt(1, QPointF(x, itemIdle->pos().y()));

    timeLine->start();
    healthBar->setVisible(true);
}

void Hero::startAnimation()
{
    animationIdle->start();
}

void Hero::startAttackAnimation()
{
    itemIdle->hide();
    itemAttack->show();
    itemAttack->setPos(itemIdle->pos().x() + differenceX, itemIdle->pos().y() + differenceY);// x = -75; y = 30
    animationAttack->start();
}

QGraphicsPixmapItem * Hero::getItemIdle()
{
    return itemIdle;
}

QGraphicsPixmapItem * Hero::getItemAttack()
{
    return itemAttack;
}

int Hero::getPositionX()
{
    return x;
}

int Hero::getPositionY()
{
    return y;
}

void Hero::applyDamage()
{
    if(targetHero) {
        double newDamage = damage;
        for(int i = 0; i < artifacts.size(); i++)
        {
            newDamage += artifacts[i]->makeDamageBuff(newDamage) - damage;
        }
        targetHero->getDamage(newDamage);
        targetHero = nullptr;
    }
}

HealthBar* Hero::getHealthBar()
{
    return healthBar;
}

QString Hero::getPathToAvatar()
{
    return pathToAvatar;
}

bool Hero::getIsAlive()
{
    return isAlive;
}

QString Hero::getPathToAttackIcon()
{
    return pathToAttackIcon;
}

int Hero::getHeroDamageValue()
{
    return damage;
}

QString Hero::getPathToHeroIcon()
{
    return pathToHeroIcon;
}

void Hero::addArtifact(Artifact *artifact)
{
    if (artifacts.size() < 3) {
        artifacts.append(artifact);
    }
}

void Hero::replaceArtifact(Artifact *newArtifact, int index)
{
    artifacts[index] = newArtifact;
}

void Hero::fullRecovery()
{
    health = baseHealth;
    isAlive = true;
    itemIdle->show();
    // //itemAttack->show();
    // int newHealth = baseHealth;
    // for(int i = 0; i < artifacts.size(); i++)
    // {
    //     newHealth = artifacts[i]->makeHealthBuff(newHealth);
    // }
    // health = newHealth;
    //upd
    healthBar->show();
}

int Hero::getArtifactsSize()
{
    return artifacts.size();
}

Artifact *Hero::getArtifact(int index)
{
    return artifacts[index];
}
