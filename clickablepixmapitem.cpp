#include "clickablepixmapitem.h"

ClickablePixmapItem::ClickablePixmapItem(QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent)
{
}

ClickablePixmapItem::ClickablePixmapItem(const QPixmap &pixmap, QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(pixmap, parent)
{
}

void ClickablePixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
}
