#include "artifactpixmapitem.h"

ArtifactPixmapItem::ArtifactPixmapItem(const QPixmap& pixmap, const QString& name, const QString& characteristics)
    : QGraphicsPixmapItem(pixmap), name_(name), characteristics_(characteristics)
{
    setAcceptHoverEvents(true);
}

void ArtifactPixmapItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    setToolTip(QString("%1\n%2").arg(name_).arg(characteristics_));
    QGraphicsPixmapItem::hoverEnterEvent(event);
}

void ArtifactPixmapItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    setToolTip("");
    QGraphicsPixmapItem::hoverLeaveEvent(event);
}
