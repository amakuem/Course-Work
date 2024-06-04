#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <QGraphicsRectItem>
#include <QGraphicsItemGroup>
#include <QBrush>

class HealthBar: public QGraphicsItemGroup
{
public:
    HealthBar(int X, int Y, int MaxHealth);
    void updateHealthBar(double health);
    int getMaxedHealth();
private:
    QGraphicsRectItem *backgroundHealthBar;
    QGraphicsRectItem *healthBar;
    double maxHealth;
};

#endif // HEALTHBAR_H
