#include "healthbar.h"

HealthBar::HealthBar(int X, int Y, int MaxHealth)
{
    backgroundHealthBar = new QGraphicsRectItem();
    backgroundHealthBar->setRect(0, 0, 100, 8);
    backgroundHealthBar->setBrush(Qt::black);
    addToGroup(backgroundHealthBar);

    healthBar = new QGraphicsRectItem(0, 0, 100, 8);
    healthBar->setBrush(Qt::green);
    addToGroup(healthBar);

    maxHealth = MaxHealth;

    setPos(X, Y);
}

void HealthBar::updateHealthBar(double health)
{
    healthBar->setRect(0, 0, (health/maxHealth) * 100, 8);
}

int HealthBar::getMaxedHealth()
{
    return maxHealth;
}

