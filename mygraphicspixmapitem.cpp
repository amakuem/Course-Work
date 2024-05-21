#include "mygraphicspixmapitem.h"

MyGraphicsPixmapItem::MyGraphicsPixmapItem(QString iconPath, QString stats, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), infoBox(nullptr), infoText(nullptr), characterImage(nullptr) // Инициализировано
{
    characterIconPath = iconPath;
    characterStats = stats;
    setAcceptHoverEvents(true);
}

MyGraphicsPixmapItem::MyGraphicsPixmapItem(const QPixmap &pixmap, QGraphicsItem *parent)
    : QGraphicsPixmapItem(pixmap, parent), infoBox(nullptr), infoText(nullptr), characterImage(nullptr) // Инициализировано
{
    setAcceptHoverEvents(true);
}

void MyGraphicsPixmapItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if (!infoBox) {
        infoBox = new QGraphicsRectItem(this);
        infoBox->setRect(0, 0, 800, 180);
        infoBox->setBrush(QBrush(Qt::black));
    }
    if (!infoText) {
        infoText = new QGraphicsTextItem(infoBox);
        infoText->setPlainText(this->characterStats); // Используйте характеристики персонажа
        infoText->setDefaultTextColor(Qt::white);
        infoText->setPos(100, 50); // Регулируйте позицию по мере необходимости
    }

    if (!characterImage) {
        characterImage = new QGraphicsPixmapItem(infoBox);
        characterImage->setPixmap(QPixmap(this->characterIconPath)); // Используйте путь к иконке персонажа
        characterImage->setPos(50, 50); // Регулируйте позицию по мере необходимости
    }
    // if (!infoText) {
    //     infoText = new QGraphicsTextItem(infoBox);
    //     infoText->setPlainText("Character info"); // Замените на фактическую информацию о персонаже
    //     infoText->setDefaultTextColor(Qt::white);
    // }

    // if (!characterImage) {
    //     characterImage = new QGraphicsPixmapItem(infoBox);
    //     characterImage->setPixmap(QPixmap(":/new/gif/kirbiAttack.gif")); // Замените на путь к изображению персонажа
    //     characterImage->setPos(-100, -100); // Регулируйте позицию по мере необходимости

    //     // Создаем рамку вокруг изображения
    //     QGraphicsRectItem *border = new QGraphicsRectItem(characterImage->boundingRect(), characterImage);
    //     border->setPen(QPen(Qt::white)); // Устанавливаем цвет рамки на белый
    // }

    qreal x = scene()->width() / 2 - infoBox->rect().width() / 2 - 150;
    qreal y = scene()->height() - infoBox->rect().height();
    infoBox->setPos(x, y);

    infoBox->show();
    infoText->show();
    characterImage->show(); // Добавлено

    QGraphicsPixmapItem::hoverEnterEvent(event);
}

// void MyGraphicsPixmapItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
// {
//     if (infoBox) {
//         infoBox->hide();
//     }

//     if (infoText) {
//         infoText->hide();
//     }

//     QGraphicsPixmapItem::hoverLeaveEvent(event);
// }

