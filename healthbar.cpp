#include "healthbar.h"

HealthBar::HealthBar(int X, int Y)
{
    backgroundHealthBar = new QGraphicsRectItem();
    backgroundHealthBar->setRect(0, 0, 100, 10);
    backgroundHealthBar->setBrush(Qt::black);
    addToGroup(backgroundHealthBar);

    healthBar = new QGraphicsRectItem(0, 0, 100, 10);
    healthBar->setBrush(Qt::green);
    addToGroup(healthBar);

    setPos(X, Y);
}

void HealthBar::updateHealthBar(int health)
{
    healthBar->setRect(0, 0, health, 10);
}
