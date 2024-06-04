#include "mygraphicspixmapitem.h"

MyGraphicsPixmapItem::MyGraphicsPixmapItem(QGraphicsScene *Scene, QString iconPath, QString stats, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), infoBox(nullptr), infoText(nullptr), characterImage(nullptr) // Инициализировано
{
    characterIconPath = iconPath;
    characterStats = stats;
    scene = Scene;
    infoBox = new QGraphicsRectItem(0, 0, 1920 / 2, 100); //428 / 2
    infoBox->setBrush(Qt::black);
    infoBox->setOpacity(0.3);
    setAcceptHoverEvents(true);

    QRectF sceneRect = scene->sceneRect();
    qreal x = sceneRect.width() / 2 - infoBox->rect().width() / 2;
    qreal y = 0;
    infoBox->setPos(x, y);
    //scene->addItem(infoBox);

}

MyGraphicsPixmapItem::MyGraphicsPixmapItem(const QPixmap &pixmap, QGraphicsItem *parent)
    : QGraphicsPixmapItem(pixmap, parent), infoBox(nullptr), infoText(nullptr), characterImage(nullptr) // Инициализировано
{
    setAcceptHoverEvents(true);
}

void MyGraphicsPixmapItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if(!scene->items().isEmpty())
    {
        scene->clear();
        scene->update();
    }

    if (!infoBox)
    {
        scene->addItem(infoBox);
    }


    QPixmap characterIcon(characterIconPath);
    characterImage = new QGraphicsPixmapItem(characterIcon.scaled(200, 200, Qt::KeepAspectRatio));
    characterImage->setScale(0.75);
    //characterImage->setPos(infoBox->rect().center() - QPointF(characterIcon.width() / 2, characterIcon.height() / 2));
    characterImage->setPos(scene->sceneRect().width() / 2 - infoBox->rect().width() / 2, 0);
    scene->addItem(characterImage);
    textItem = new QGraphicsTextItem(characterStats);
    textItem->setPos(infoBox->rect().topRight() + QPointF(10, 0));
    scene->addItem(textItem);

    QGraphicsPixmapItem::hoverEnterEvent(event);
}


