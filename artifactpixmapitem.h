#ifndef ARTIFACTPIXMAPITEM_H
#define ARTIFACTPIXMAPITEM_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QToolTip>
#include <QGraphicsSceneMouseEvent>


class ArtifactPixmapItem : public QGraphicsPixmapItem
{
public:
    ArtifactPixmapItem(const QPixmap& pixmap, const QString& name, const QString& characteristics);
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
private:
    QString name_;
    QString characteristics_;
};

#endif // ARTIFACTPIXMAPITEM_H
