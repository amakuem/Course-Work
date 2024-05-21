#ifndef MYGRAPHICSPIXMAPITEM_H
#define MYGRAPHICSPIXMAPITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsSceneHoverEvent>
#include <QBrush>
#include <QGraphicsScene>

class MyGraphicsPixmapItem : public QGraphicsPixmapItem
{
public:
    MyGraphicsPixmapItem(QString iconPath, QString stats, QGraphicsItem *parent = nullptr);
    MyGraphicsPixmapItem(const QPixmap &pixmap, QGraphicsItem *parent = nullptr);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    //void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

private:
    QString characterIconPath; // Путь к иконке персонажа
    QString characterStats;
    QGraphicsRectItem *infoBox;
    QGraphicsTextItem *infoText;
    QGraphicsPixmapItem *characterImage; // Добавлено
};
#endif // MYGRAPHICSPIXMAPITEM_H
