#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <QGraphicsRectItem>
#include <QGraphicsItemGroup>
#include <QBrush>

class HealthBar: public QGraphicsItemGroup
{
public:
    HealthBar(int X, int Y);
    void updateHealthBar(int health);
private:
    QGraphicsRectItem *backgroundHealthBar;
    QGraphicsRectItem *healthBar;
};

#endif // HEALTHBAR_H
