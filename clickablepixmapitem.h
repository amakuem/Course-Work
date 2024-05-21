#ifndef CLICKABLEPIXMAPITEM_H
#define CLICKABLEPIXMAPITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class ClickablePixmapItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    ClickablePixmapItem(QGraphicsItem *parent = nullptr);
    ClickablePixmapItem(const QPixmap &pixmap, QGraphicsItem *parent = nullptr);

signals:
    void clicked();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // CLICKABLEPIXMAPITEM_H
