#include "hero.h"

Hero::Hero(QString attack, QString idle, int Damage, int Rotation, int HealthBarX, int HealthBarY)
{
    //damage = 10;
    damage = Damage;
    health = 100;
    rotation = Rotation;
    healthBarX = HealthBarX;
    healthBarY = HealthBarY;
    animationAttack = new QMovie(attack, QByteArray(), this);
    animationIdle = new QMovie (idle, QByteArray(), this);
    itemAttack = new QGraphicsPixmapItem();
    //itemIdle = new QGraphicsPixmapItem();
    QString stats = "Здоровье: " + QString::number(health) + '\n' + "Урон: " + QString::number(damage);
    itemIdle = new MyGraphicsPixmapItem(idle, stats);
    timerAttack = new QTimer();

    opacityEffect = new QGraphicsOpacityEffect(this);


    isAlive = true;

    itemIdle->setScale(0.5);
    itemAttack->setScale(0.62);

    connect(animationAttack, &QMovie::finished, this, &Hero::applyDamage);
    connect(animationAttack, &QMovie::frameChanged, this, &Hero::playAttack);
    connect(animationIdle, &QMovie::frameChanged, this, &Hero::playIdle);
    connect(timerAttack, &QTimer::timeout, this, &Hero::startAttackAnimation);
}

void Hero::setPosition(int X, int Y)
{
    x = X;
    y = Y;
    itemIdle->setPos(x, y);
    healthBar = new HealthBar(x + healthBarX, y + healthBarY);
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
        health = 0;
        isAlive = false;
    }
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
    // Создайте объект QTimeLine
    QTimeLine *timeLine = new QTimeLine(800);
    timeLine->setFrameRange(0, 100);

    // Создайте объект QGraphicsItemAnimation
    QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
    animation->setItem(itemIdle);
    animation->setTimeLine(timeLine);

    // Установите начальную и конечную позиции для анимации
    animation->setPosAt(0, itemIdle->pos());
    animation->setPosAt(1, QPointF(X, itemIdle->pos().y()));

    // Начните анимацию
    timeLine->start();

    timerAttack->start(800);
    // itemAttack->setScale(0.5);
    // itemAttack->setPos(X, y);
    // animationAttack->start();
}

void Hero::movingReturn()
{
    // Создайте объект QTimeLine
    QTimeLine *timeLine = new QTimeLine(800);
    timeLine->setFrameRange(0, 100);

    // Создайте объект QGraphicsItemAnimation
    QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
    animation->setItem(itemIdle);
    animation->setTimeLine(timeLine);

    // Установите начальную и конечную позиции для анимации
    animation->setPosAt(0, itemIdle->pos());
    animation->setPosAt(1, QPointF(x, itemIdle->pos().y()));

    // Начните анимацию
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
    itemAttack->setPos(itemIdle->pos().x() - 75, itemIdle->pos().y() + 30);
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
        targetHero->getDamage(damage);
        targetHero = nullptr;
    }
}

HealthBar* Hero::getHealthBar()
{
    return healthBar;
}
