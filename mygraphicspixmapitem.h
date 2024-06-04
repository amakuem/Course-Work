#ifndef MYGRAPHICSPIXMAPITEM_H
#define MYGRAPHICSPIXMAPITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsSceneHoverEvent>
#include <QBrush>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsItemGroup>

class MyGraphicsPixmapItem : public QGraphicsPixmapItem
{
public:
    MyGraphicsPixmapItem(QGraphicsScene *Scene, QString iconPath, QString stats, QGraphicsItem *parent = nullptr);
    MyGraphicsPixmapItem(const QPixmap &pixmap, QGraphicsItem *parent = nullptr);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    //void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

private:
    QGraphicsScene *scene;
    QString characterIconPath; // Путь к иконке персонажа
    QString characterStats;
    QGraphicsRectItem *infoBox;
    QGraphicsTextItem *infoText;
    QGraphicsPixmapItem *characterImage; // Добавлено
    QGraphicsTextItem *textItem;
};
#endif // MYGRAPHICSPIXMAPITEM_H
