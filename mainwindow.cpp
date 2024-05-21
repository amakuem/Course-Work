#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView_2->setStyleSheet("border: 1px solid #2c272b;");
    scene = new QGraphicsScene();
    backgroundScene2 = new QGraphicsPixmapItem();
    backgroundScene2->setPixmap(QPixmap(":/backgrounds/background/down.gif"));
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0, 0, ui->graphicsView->width() - 10, ui->graphicsView->height() - 10);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene2 = new QGraphicsScene();
    ui->graphicsView_2->setScene(scene2);
    scene2->setSceneRect(0, 0, 1910, 418);   // Создаем прямоугольную область посередине graphicsView_2
    QColor color("#2c272b");
    scene2->setBackgroundBrush(color);
    //scene2->addItem(backgroundScene2);
    //ui->graphicsView_2->fitInView(backgroundScene2, Qt::IgnoreAspectRatio);

    QGraphicsRectItem *rect = new QGraphicsRectItem();
    rect->setRect(0, 0, ui->graphicsView_2->width() / 2, ui->graphicsView_2->height() / 2);
    rect->setPos(ui->graphicsView_2->width() / 2 - 652, 0);
    scene2->addItem(rect);
    //

    characterIcon1 = new ClickablePixmapItem();
    characterIcon1->setPixmap(QPixmap(":/heroes/hero/warrior/warriorAvatar.png"));
    scene2->addItem(characterIcon1);
    characterIcon1->setScale(0.25);
    characterIcon1->setPos(rect->x(), rect->y());
    connect(characterIcon1, &ClickablePixmapItem::clicked, this, &MainWindow::on_characterIcon1_clicked);

    characterIcon2 = new ClickablePixmapItem();
    characterIcon2->setPixmap(QPixmap(":/heroes/hero/enemy/krolAvatar.png"));
    scene2->addItem(characterIcon2);
    characterIcon2->setScale(0.4);
    characterIcon2->setPos(rect->x() + characterIcon1->boundingRect().width() - 100, rect->y());
    connect(characterIcon2, &ClickablePixmapItem::clicked, this, &MainWindow::on_characterIcon2_clicked);

    background = new QMovie(":/backgrounds/background/forest.gif", QByteArray(), this);
    itemBackground = new QGraphicsPixmapItem();
    scene->addItem(itemBackground);

    warrior = new Hero(":/heroes/hero/warrior/warriorAttack.gif",":/heroes/hero/warrior/warriorIdle.gif", 10, 1, 100, 255);
    //scene->addItem(warrior->getItemIdle());
    warrior->setPosition(220, 372);
    //scene->addItem(warrior->getHealthBar());



    enemy = new Hero(":/heroes/hero/enemy/krolAttack.gif", ":/heroes/hero/enemy/krolIdle.gif", 10, -1, 38, 118);
    //scene->addItem(enemy->getItemIdle());
    enemy->setPosition(1020, 510);
    //scene->addItem(enemy->getHealthBar());

    //Установка объектов для атаки
    //scene->addItem(warrior->getItemAttack());


    connect(background, &QMovie::frameChanged, this, &MainWindow::playBackground);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Play_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->game);
    background->start();
    warrior->startAnimation();
    enemy->startAnimation();
}

void MainWindow::playBackground()
{
    QPixmap pixmap = background->currentPixmap();
    pixmap = pixmap.scaled(ui->graphicsView->width() - 10, ui->graphicsView->height() - 10, Qt::IgnoreAspectRatio);
    itemBackground->setPixmap(pixmap);

}

void MainWindow::on_pushButton_clicked()
{
    warrior->attack(enemy, enemy->getPositionX() - 100);
}

void MainWindow::on_characterIcon1_clicked()
{
    // Проверяем, находится ли персонаж уже на сцене
    if (!scene->items().contains(warrior->getItemIdle())) {
        // Если нет, добавляем его на сцену
        scene->addItem(warrior->getItemIdle());
        scene->addItem(warrior->getHealthBar());
        // Изменяем цвет иконки персонажа
        characterIcon1->setOpacity(0.5);
    } else {
        // Если персонаж уже на сцене, удаляем его
        scene->removeItem(warrior->getItemIdle());
        scene->removeItem(warrior->getHealthBar());
        // Возвращаем цвет иконки персонажа к нормальному
        characterIcon1->setOpacity(1.0);
    }
}

void MainWindow::on_characterIcon2_clicked()
{
    // Проверяем, находится ли персонаж уже на сцене
    if (!scene->items().contains(enemy->getItemIdle())) {
        // Если нет, добавляем его на сцену
        scene->addItem(enemy->getItemIdle());
        scene->addItem(enemy->getHealthBar());
        // Изменяем цвет иконки персонажа
        characterIcon2->setOpacity(0.5);
    } else {
        // Если персонаж уже на сцене, удаляем его
        scene->removeItem(enemy->getItemIdle());
        scene->removeItem(enemy->getHealthBar());
        // Возвращаем цвет иконки персонажа к нормальному
        characterIcon2->setOpacity(1.0);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    scene2->clear();
    ui->pushButton_2->hide();
    scene->addItem(warrior->getItemAttack());
}

