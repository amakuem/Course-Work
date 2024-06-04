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
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0, 0, ui->graphicsView->width() - 10, ui->graphicsView->height() - 10);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->stackedWidget->setCurrentWidget(ui->startMenu);

    scene2 = new QGraphicsScene();
    ui->graphicsView_2->setScene(scene2);
    scene2->setSceneRect(0, 0, 1910, 418);   // Создаем прямоугольную область посередине graphicsView_2
    QColor color("#2c272b");
    scene2->setBackgroundBrush(color);

    sceneForGifMenu = new QGraphicsScene();
    sceneForColorMenu = new QGraphicsScene();
    ui->viewGifBack->setScene(sceneForGifMenu);
    sceneForGifMenu->setSceneRect(0, 0, ui->viewGifBack->width() - 10, ui->viewGifBack->height() - 10);
    ui->viewGifBack->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->viewGifBack->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->viewSolourBack->setScene(sceneForColorMenu);
    ui->viewSolourBack->setStyleSheet("border: 1px solid #2c272b;");
    sceneForColorMenu->setBackgroundBrush(color);

    scene3 = new QGraphicsScene();
    ui->graphicsView_3->setScene(scene3);
    scene3->setSceneRect(0, 0, 1920, 1080);

    scene4 = new QGraphicsScene();
    ui->graphicsView_4->setScene(scene4);
    scene4->setSceneRect(0, 0, ui->graphicsView_4->width(), ui->graphicsView_4->height());
    ui->graphicsView_4->setViewportUpdateMode(QGraphicsView::NoViewportUpdate);

    //установка фона
    background = new QMovie(":/backgrounds/background/forest.gif", QByteArray(), this);
    itemBackground = new QGraphicsPixmapItem();
    scene->addItem(itemBackground);
    sceneForGifMenu->addItem(itemBackground);

    positions = QList<bool>() << false << false << false;

    //создание персонажей
    player = new Player();
    warrior = new Hero(":/heroes/hero/warrior/warriorFace.png", ":/heroes/hero/warrior/warriorAttack.gif", 0.62, ":/heroes/hero/warrior/sword.png",":/heroes/hero/warrior/warriorIdle.gif", 0.5,":/heroes/hero/warrior/warriorAvatar.png", 29, 316, 1, 100, 255, -75, 30, scene2);
    warrior->setPosition(-10, 372);

    rogach = new Hero(":/heroes/hero/rogach/rogachFace.png", ":/heroes/hero/rogach/rogachAttack.gif", 0.75, ":/heroes/hero/rogach/spear.png",":/heroes/hero/rogach/rogachIdle.gif", 0.75,":/heroes/hero/rogach/rogachAvatar.png", 52, 247, 1, 100, 265, -25, 0, scene2);
    rogach->setPosition(-10, 360);

    kungFuGirl = new Hero(":/heroes/hero/kungFuGirl/kungFuGirlFace.png", ":/heroes/hero/kungFuGirl/kungFuGirAttack.gif", 0.5, ":/heroes/hero/kungFuGirl/fist.png",":/heroes/hero/kungFuGirl/kungFuGirIdle.gif", 0.5, ":/heroes/hero/kungFuGirl/kungFuGirlAvatar.png", 73, 152, 1, 100, 265, -25, 0, scene2);
    kungFuGirl->setPosition(-10, 360);

    //создание артефактов
    allArtifacts.append(new Artifact("Skull", ":/items/item/skull.jpg", 50, 0.15, 368));
    allArtifacts.append(new Artifact("Electro Sphere", ":/items/item/electroSphere.jpg", 0, 0.05, 108));
    allArtifacts.append(new Artifact("Fire Sphere", ":/items/item/fireSphere.jpg", 0, 0.10, 153));
    allArtifacts.append(new Artifact("Health Amulet", ":/items/item/healthAmulet.jpg", 50, 0, 63));

    //проба !!! обязательно удалить
    // warrior->addArtifact(new Artifact("Skull", ":/items/item/skull.jpg", 50, 0.15, 368));
    // warrior->addArtifact(new Artifact("Electro Sphere", ":/items/item/electroSphere.jpg", 0, 0.05, 108));
    // warrior->addArtifact(new Artifact("Electro Sphere", ":/items/item/electroSphere.jpg", 0, 0.05, 108));
    //warrior->addArtifact(new Artifact("Electro Sphere", ":/items/item/electroSphere.jpg", 0, 0.05, 108));
    //

    //создание игрока
    player = new Player();
    player->addHero(warrior);
    player->addHero(rogach);
    player->addHero(kungFuGirl);

    game = new Game(scene, scene2, player);

    coins = new QGraphicsPixmapItem();
    coins->setPixmap(QPixmap(":/items/item/coins.png").scaled(100, 100, Qt::KeepAspectRatio));
    coins->setScale(0.5);

    dmgHero1 = new QLabel(this);
    dmgHero1->setStyleSheet("QLabel { font-family: \"Bahnschrift SemiLight SemiConde\"; font-size: 22pt; }");
    dmgHero2 = new QLabel(this);
    dmgHero2->setStyleSheet("QLabel { font-family: \"Bahnschrift SemiLight SemiConde\"; font-size: 22pt; }");
    dmgHero3 = new QLabel(this);
    dmgHero3->setStyleSheet("QLabel { font-family: \"Bahnschrift SemiLight SemiConde\"; font-size: 22pt; }");

    dmgHeroes.append(dmgHero1);
    dmgHeroes.append(dmgHero2);
    dmgHeroes.append(dmgHero3);

    //store
    ui->tableWidget->setRowCount(allArtifacts.size());
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for(int i = 0; i < allArtifacts.size(); i++)
    {
        ui->tableWidget->setRowHeight(i, 78);
        ui->tableWidget->setColumnWidth(i, 78);
    }

    player->setMoney(333);

    ui->graphicsView_4->hide();
    ui->pushButton_Back->hide();
    ui->pushButton_Cancel->hide();

    //background->start();
    connect(background, &QMovie::frameChanged, this, &MainWindow::playBackground);
    connect(game, &Game::gameFinished, this, &MainWindow::handleGameFinished);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::handleLabelDeletion);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Play_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->menu);
    background->start();
    warrior->startAnimation();
    rogach->startAnimation();
    kungFuGirl->startAnimation();
}

void MainWindow::playBackground()
{
    QPixmap pixmap = background->currentPixmap();
    pixmap = pixmap.scaled(ui->graphicsView->width() - 10, ui->graphicsView->height() - 10, Qt::IgnoreAspectRatio);
    itemBackground->setPixmap(pixmap);

}

void MainWindow::on_characterIcon1_clicked()
{
    if (!scene->items().contains(warrior->getItemIdle())) {
        int pos = positions.indexOf(false);
        if (pos != -1)
        {
            player->getHero(0)->setPosition(pos * 200, player->getHero(0)->getPositionY());
            scene->addItem(player->getHero(0)->getItemIdle());
            scene->addItem(player->getHero(0)->getHealthBar());
            characterIcon1->setOpacity(0.5);
            positions[pos] = true;
        }
    } else {
        scene->removeItem(player->getHero(0)->getItemIdle());
        scene->removeItem(player->getHero(0)->getHealthBar());
        characterIcon1->setOpacity(1.0);
        int pos = player->getHero(0)->getPositionX() / 200;
        player->getHero(0)->setPosition(-10, player->getHero(0)->getPositionY());
        positions[pos] = false;
    }

}

void MainWindow::on_characterIcon2_clicked()
{
    if (!scene->items().contains(rogach->getItemIdle())) {
        int pos = positions.indexOf(false);
        if (pos != -1)
        {
            player->getHero(1)->setPosition(pos * 200, player->getHero(1)->getPositionY());
            scene->addItem(player->getHero(1)->getItemIdle());
            scene->addItem(player->getHero(1)->getHealthBar());
            characterIcon2->setOpacity(0.5);
            positions[pos] = true;
        }
    }
    else
    {
        scene->removeItem(player->getHero(1)->getItemIdle());
        scene->removeItem(player->getHero(1)->getHealthBar());
        characterIcon2->setOpacity(1.0);
        int pos = player->getHero(1)->getPositionX() / 200;
        player->getHero(1)->setPosition(-10, player->getHero(1)->getPositionY());
        positions[pos] = false;
    }
}

void MainWindow::on_characterIcon3_clicked()
{
    if (!scene->items().contains(kungFuGirl->getItemIdle())) {

        int pos = positions.indexOf(false);
        if (pos != -1)
        {
            player->getHero(2)->setPosition(pos * 200, player->getHero(2)->getPositionY());
            scene->addItem(player->getHero(2)->getItemIdle());
            scene->addItem(player->getHero(2)->getHealthBar());
            characterIcon3->setOpacity(0.5);
            positions[pos] = true;
        }
    }
    else
    {
        scene->removeItem(player->getHero(2)->getItemIdle());
        scene->removeItem(player->getHero(2)->getHealthBar());
        characterIcon3->setOpacity(1.0);
        int pos = player->getHero(2)->getPositionX() / 200;
        player->getHero(2)->setPosition(-10, player->getHero(2)->getPositionY());
        positions[pos] = false;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    scene2->clear();
    ui->pushButton_2->hide();

    for(int i = 0; i < 3; i++)
    {
        if(player->getHero(0)->getPositionX() == i * 200)
        {
            player->addHeroInBattleField(player->getHero(0));
        }
        else if(player->getHero(1)->getPositionX() == i * 200)
        {
            player->addHeroInBattleField(player->getHero(1));
        }
        else if(player->getHero(2)->getPositionX() == i * 200)
        {
            player->addHeroInBattleField((player->getHero(2)));
        }
    }

    for(int i = 0; i < player->getHeroInBattleFieldSize(); i++)
    {
        scene->addItem(player->getHeroInBattleField(i)->getItemAttack());
    }
    game->setEnemies();
    game->startGame();
}

void MainWindow::handleGameFinished(QString status, double totalDamage, double damageHero1, double damageHero2, double damageHero3)
{
    int interval = 152;
    int iconY = 252;//352


    ui->stackedWidget->setCurrentWidget(ui->gameFinishMenu);
    ui->label_2->setText(status);
    ui->label_3->setText("TOTAL DAMAGE: " + QString::number(totalDamage));
    QVector<int> tempDamage;
    tempDamage.append(damageHero1);
    tempDamage.append(damageHero2);
    tempDamage.append(damageHero3);

    QVector<int> damage;
    for(int i = 0; i < player->getHeroInBattleFieldSize(); i++)
    {
        damage.append(tempDamage[i]);
    }


    if(player->getHeroInBattleFieldSize() >= 2)
    {
        quickSort(damage, 0, damage.size() - 1);
    }
    for(int i = 0; i < player->getHeroInBattleFieldSize(); i++)
    {
        player->getHeroInBattleField(i)->setPosition(-10, player->getHeroInBattleField(i)->getPositionY());

        //создание статистики
        QGraphicsPixmapItem *icon = new QGraphicsPixmapItem();
        icon->setPixmap(QPixmap(player->getHeroInBattleField(i)->getPathToHeroIcon()).scaled(100, 100, Qt::KeepAspectRatio));
        scene3->addItem(icon);
        icon->setScale(0.75);
        icon->setPos(499, iconY);

        QGraphicsRectItem *damageRect = new QGraphicsRectItem();
        damageRect->setRect(0, 0, (damage[i]/totalDamage) * 500, 75);
        damageRect->setPos(599, iconY);
        damageRect->setBrush(Qt::red);
        scene3->addItem(damageRect);

        //QLabel *label = new QLabel(this);
        //label->setFixedSize(200, 40);
        dmgHeroes[i]->setText(QString::number(damage[i]));
        dmgHeroes[i]->setGeometry(QRect(damageRect->pos().x() + damageRect->rect().width() + 15, iconY + 15, 200, 40));
        //label->setStyleSheet("QLabel { font-family: \"Bahnschrift SemiLight SemiConde\"; font-size: 22pt; }");
        dmgHeroes[i]->show();

        iconY += interval;
    }
    scene3->addItem(coins);
    //coins->show();
    coins->setPos(756, 644);


    label = new QLabel(this);
    //label->setFixedSize(200, 40);
    if(status == "YOU LOSE")
    {
        label->setText("0");
    }
    else
    {
        label->setText("333");
        player->setMoney(333);
    }

    label->setGeometry(QRect(799, 649, 200, 40));
    label->setStyleSheet("QLabel { font-family: \"Bahnschrift SemiLight SemiConde\"; font-size: 20pt; }");
    label->show();

    //label->deleteLater();
    player->battleEnd();
    positions = QList<bool>() << false << false << false;
}

void MainWindow::quickSort(QVector<int> &damage, int low, int high)
{
    if (low < high)
    {
        int pi = partition(damage, low, high);
        quickSort(damage, low, pi - 1);
        quickSort(damage, pi + 1, high);
    }
}

int MainWindow::partition(QVector<int> &damage, int low, int high)
{
    int pivot = damage[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (damage[j] > pivot) {
            ++i;
            std::swap(damage[i], damage[j]);
            player->swapHeroesInBattleField(i, j);
        }
    }
    std::swap(damage[i + 1], damage[high]);
    player->swapHeroesInBattleField(i + 1, high);
    return i + 1;
}

void MainWindow::on_pushButton_clicked()
{
    scene3->removeItem(coins);
    scene3->clear();
    ui->stackedWidget->setCurrentWidget(ui->menu);
    sceneForGifMenu->addItem(itemBackground);
}

void MainWindow::handleLabelDeletion()
{
    // Удаление label
    label->deleteLater();
    // Другие действия по удалению
    for(int i = 0; i < dmgHeroes.size(); i++)
    {
        dmgHeroes[i]->hide();
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->graphicsView_4->show();
    //scene4->addItem(QPixmap(player->getHero(0)->getPathToHeroIcon()).scaled(100, 100, Qt::KeepAspectRatio));


}

void MainWindow::greedyAlgorithm()
{
    QVector<double> coefficents;

    for(int i = 0; i < allArtifacts.size(); i++)
    {
        coefficents.append((allArtifacts[i]->getDamageBuff() * 100) / allArtifacts[i]->getCost());
    }



    double totalCost = 0.0;
    bestArtifactsOption.clear();

    for (int i = 1; i < coefficents.size(); i++) {
        double currentCoef = coefficents[i];
        Artifact * currentArtifact = allArtifacts[i];
        for (int j = i - 1; j >= -1; j--) {
            if (j >= 0 && coefficents[j] < currentCoef) {

                coefficents[j + 1] = coefficents[j];

                allArtifacts[j + 1] = allArtifacts[j];
            }
            else {
                coefficents[j+1] = currentCoef;

                allArtifacts[j+1] = currentArtifact;
                break;
            }
        }
    }

    for (int i = 0; i < allArtifacts.size(); i++) {
        double artifactCost = allArtifacts[i]->getCost();
        if (totalCost + artifactCost <= player->getMoney())
        {
            bestArtifactsOption.append(allArtifacts[i]);
            totalCost += artifactCost;
        }
        else
        {
            break;
        }
    }
}

void MainWindow::sortShop()
{
    for (int gap = allArtifacts.size() / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < allArtifacts.size(); ++i) {
            int temp = allArtifacts[i]->getCost();
            int j;
            Artifact * tempArt = allArtifacts[i];
            for ( j = i; j >= gap && allArtifacts[j - gap]->getCost() < temp; j -= gap) {
                allArtifacts[j] = allArtifacts[j - gap];

            }
            allArtifacts[j] = tempArt;
        }
    }
}

void MainWindow::on_pushButton_Fight_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->game);

    ui->pushButton_2->show();

    scene->addItem(itemBackground);

    game->restartGame(scene2);

    QGraphicsRectItem *rect = new QGraphicsRectItem();
    rect->setRect(0, 0, ui->graphicsView_2->width() / 2, ui->graphicsView_2->height() / 2);
    rect->setPos(ui->graphicsView_2->width() / 2 - 652, 0);
    rect->setBrush(Qt::black);
    rect->setOpacity(0.3);
    scene2->addItem(rect);

    double interval = (ui->graphicsView_2->width() / 2.0) / 4.0;

    double iconX = ui->graphicsView_2->width() / 2 - 652;

    iconX += interval;

    //game = new Game(scene, scene2, player);
    characterIcon1 = new ClickablePixmapItem();
    characterIcon1->setPixmap(QPixmap(player->getHero(0)->getPathToAvatar()).scaled(100, 100, Qt::KeepAspectRatio));
    scene2->addItem(characterIcon1);
    characterIcon1->setScale(1);
    characterIcon1->setPos(iconX - 50, 25);
    connect(characterIcon1, &ClickablePixmapItem::clicked, this, &MainWindow::on_characterIcon1_clicked);
    iconX += interval;

    characterIcon2 = new ClickablePixmapItem();
    characterIcon2->setPixmap(QPixmap(player->getHero(1)->getPathToAvatar()).scaled(100, 100, Qt::KeepAspectRatio));
    scene2->addItem(characterIcon2);
    characterIcon2->setScale(1);
    characterIcon2->setPos(iconX - 50, 25);
    connect(characterIcon2, &ClickablePixmapItem::clicked, this, &MainWindow::on_characterIcon2_clicked);
    iconX += interval;

    characterIcon3 = new ClickablePixmapItem();
    characterIcon3->setPixmap(QPixmap(player->getHero(2)->getPathToAvatar()).scaled(100, 100, Qt::KeepAspectRatio));
    scene2->addItem(characterIcon3);
    characterIcon3->setScale(1.5);
    characterIcon3->setPos(iconX - 100, -35);//-60
    connect(characterIcon3, &ClickablePixmapItem::clicked, this, &MainWindow::on_characterIcon3_clicked);
    iconX += interval;
}


void MainWindow::on_pushButton_Shop_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->shop);
    QPixmap label_6(":/items/item/coins.png");
    ui->label_6->setPixmap(label_6);
    ui->label_5->setText(QString::number(player->getMoney()));

    updateTableWidget();
}


void MainWindow::on_pushButton_Buy_clicked()
{
    ui->pushButton_Cancel->show();

    int index = ui->tableWidget->currentRow();
    if(allArtifacts[index]->getCost() <= player->getMoney())
    {
        ui->graphicsView_4->show();

        double interval = ui->graphicsView_4->width() / 4.0;

        double intervalArtifacts = 33;

        double iconX = 0;

        iconX += interval;

        shopIcon1 = new ClickablePixmapItem();
        shopIcon1->setPixmap(QPixmap(player->getHero(0)->getPathToHeroIcon()).scaled(100, 100, Qt::KeepAspectRatio));
        scene4->addItem(shopIcon1);
        shopIcon1->setScale(0.75);
        shopIcon1->setPos(iconX - 50, 100);
        connect(shopIcon1, &ClickablePixmapItem::clicked, this, &MainWindow::on_shopIcon1_clicked);

        QGraphicsRectItem *rect1 = new QGraphicsRectItem();
        rect1->setRect(0, 0, 100, 33);
        rect1->setPos(iconX - 50 - 12.5, 175);
        QColor color("#2c272b");
        rect1->setBrush(color);
        //rect1->setOpacity(0.3);
        scene4->addItem(rect1);

        int m = 0;

        for(int i = 0; i < player->getHero(0)->getArtifactsSize(); i++)
        {
            artifactsCharacter1.append(new ArtifactPixmapItem(QPixmap(player->getHero(0)->getArtifact(i)->getPathToArtifactIcon()).scaled(100, 100, Qt::KeepAspectRatio), player->getHero(0)->getArtifact(i)->getNameOfArtifact(), player->getHero(0)->getArtifact(i)->getStatsOfArtifact()));

            artifactsCharacter1[i]->setScale(0.32);
            artifactsCharacter1[i]->setPos(iconX - 50 - 12.5 + intervalArtifacts * m, 175);
            scene4->addItem(artifactsCharacter1[i]);
            m++;
        }

        m = 0;
        iconX += interval;

        shopIcon2 = new ClickablePixmapItem();
        shopIcon2->setPixmap(QPixmap(player->getHero(1)->getPathToHeroIcon()).scaled(100, 100, Qt::KeepAspectRatio));
        scene4->addItem(shopIcon2);
        shopIcon2->setScale(0.75);
        shopIcon2->setPos(iconX - 50, 100);
        connect(shopIcon2, &ClickablePixmapItem::clicked, this, &MainWindow::on_shopIcon2_clicked);

        QGraphicsRectItem *rect2 = new QGraphicsRectItem();
        rect2->setRect(0, 0, 100, 33);
        rect2->setPos(iconX - 50 - 12.5, 175);
        rect2->setBrush(color);
        //rect1->setOpacity(0.3);
        scene4->addItem(rect2);

        for(int i = 0; i < player->getHero(1)->getArtifactsSize(); i++)
        {
            artifactsCharacter2.append(new ArtifactPixmapItem(QPixmap(player->getHero(1)->getArtifact(i)->getPathToArtifactIcon()).scaled(100, 100, Qt::KeepAspectRatio), player->getHero(1)->getArtifact(i)->getNameOfArtifact(), player->getHero(1)->getArtifact(i)->getStatsOfArtifact()));

            artifactsCharacter2[i]->setScale(0.32);
            artifactsCharacter2[i]->setPos(iconX - 50 - 12.5 + intervalArtifacts * m, 175);
            scene4->addItem(artifactsCharacter2[i]);
            m++;
        }

        m = 0;
        iconX += interval;

        shopIcon3 = new ClickablePixmapItem();
        shopIcon3->setPixmap(QPixmap(player->getHero(2)->getPathToHeroIcon()).scaled(100, 100, Qt::KeepAspectRatio));
        scene4->addItem(shopIcon3);
        shopIcon3->setScale(0.75);
        shopIcon3->setPos(iconX - 50, 100);//-60
        connect(shopIcon3, &ClickablePixmapItem::clicked, this, &MainWindow::on_shopIcon3_clicked);

        QGraphicsRectItem *rect3 = new QGraphicsRectItem();
        rect3->setRect(0, 0, 100, 33);
        rect3->setPos(iconX - 50 - 12.5, 175);
        rect3->setBrush(color);
        //rect1->setOpacity(0.3);
        scene4->addItem(rect3);

        for(int i = 0; i < player->getHero(2)->getArtifactsSize(); i++)
        {
            artifactsCharacter3.append(new ArtifactPixmapItem(QPixmap(player->getHero(2)->getArtifact(i)->getPathToArtifactIcon()).scaled(100, 100, Qt::KeepAspectRatio), player->getHero(2)->getArtifact(i)->getNameOfArtifact(), player->getHero(2)->getArtifact(i)->getStatsOfArtifact()));

            artifactsCharacter3[i]->setScale(0.32);
            artifactsCharacter3[i]->setPos(iconX - 50 - 12.5 + intervalArtifacts * m, 175);
            scene4->addItem(artifactsCharacter3[i]);
            m++;
        }

        m = 0;
        iconX += interval;



    }
}

void MainWindow::on_shopIcon1_clicked()
{
    currentHeroIndex = 0;
    if(player->getHero(0)->getArtifactsSize() < 3)
    {
        player->getHero(0)->addArtifact(allArtifacts[ui->tableWidget->currentRow()]);
        player->setMoney((-1) * allArtifacts[ui->tableWidget->currentRow()]->getCost());
        ui->label_5->setText(QString::number(player->getMoney()));
        scene4->clear();
        scene4->update();
        ui->graphicsView_4->hide();
        artifactsCharacter1.clear();
        artifactsCharacter2.clear();
        artifactsCharacter3.clear();
        ui->pushButton_Cancel->hide();
    }
    else
    {
        scene4->clear();
        scene4->update();


        double interval = ui->graphicsView_4->width() / 4.0;

        double iconX = 0;

        iconX += interval;

        currentHeroArtifact1 = new ClickablePixmapItem();
        currentHeroArtifact1->setPixmap(QPixmap(player->getHero(0)->getArtifact(0)->getPathToArtifactIcon()).scaled(100, 100, Qt::KeepAspectRatio));
        scene4->addItem(currentHeroArtifact1);
        currentHeroArtifact1->setScale(0.75);
        currentHeroArtifact1->setPos(iconX - 50, 100);
        connect(currentHeroArtifact1, &ClickablePixmapItem::clicked, this, &MainWindow::on_currentHeroArtifact1_clicked);
        iconX += interval;

        currentHeroArtifact2 = new ClickablePixmapItem();
        currentHeroArtifact2->setPixmap(QPixmap(player->getHero(0)->getArtifact(1)->getPathToArtifactIcon()).scaled(100, 100, Qt::KeepAspectRatio));
        scene4->addItem(currentHeroArtifact2);
        currentHeroArtifact2->setScale(0.75);
        currentHeroArtifact2->setPos(iconX - 50, 100);
        connect(currentHeroArtifact2, &ClickablePixmapItem::clicked, this, &MainWindow::on_currentHeroArtifact2_clicked);
        iconX += interval;

        currentHeroArtifact3 = new ClickablePixmapItem();
        currentHeroArtifact3->setPixmap(QPixmap(player->getHero(0)->getArtifact(2)->getPathToArtifactIcon()).scaled(100, 100, Qt::KeepAspectRatio));
        scene4->addItem(currentHeroArtifact3);
        currentHeroArtifact3->setScale(0.75);
        currentHeroArtifact3->setPos(iconX - 50, 100);
        connect(currentHeroArtifact3, &ClickablePixmapItem::clicked, this, &MainWindow::on_currentHeroArtifact3_clicked);
        iconX += interval;
    }
}

void MainWindow::on_shopIcon2_clicked()
{
    currentHeroIndex = 1;
    if(player->getHero(1)->getArtifactsSize() < 3)
    {
        player->getHero(1)->addArtifact(allArtifacts[ui->tableWidget->currentRow()]);
        player->setMoney((-1) * allArtifacts[ui->tableWidget->currentRow()]->getCost());
        ui->label_5->setText(QString::number(player->getMoney()));
        scene4->clear();
        scene4->update();
        ui->graphicsView_4->hide();
        artifactsCharacter1.clear();
        artifactsCharacter2.clear();
        artifactsCharacter3.clear();
        ui->pushButton_Cancel->hide();
    }
    else
    {
        scene4->clear();
        scene4->update();


        double interval = ui->graphicsView_4->width() / 4.0;

        double iconX = 0;

        iconX += interval;

        currentHeroArtifact1 = new ClickablePixmapItem();
        currentHeroArtifact1->setPixmap(QPixmap(player->getHero(1)->getArtifact(0)->getPathToArtifactIcon()).scaled(100, 100, Qt::KeepAspectRatio));
        scene4->addItem(currentHeroArtifact1);
        currentHeroArtifact1->setScale(0.75);
        currentHeroArtifact1->setPos(iconX - 50, 100);
        connect(currentHeroArtifact1, &ClickablePixmapItem::clicked, this, &MainWindow::on_currentHeroArtifact1_clicked);
        iconX += interval;

        currentHeroArtifact2 = new ClickablePixmapItem();
        currentHeroArtifact2->setPixmap(QPixmap(player->getHero(1)->getArtifact(1)->getPathToArtifactIcon()).scaled(100, 100, Qt::KeepAspectRatio));
        scene4->addItem(currentHeroArtifact2);
        currentHeroArtifact2->setScale(0.75);
        currentHeroArtifact2->setPos(iconX - 50, 100);
        connect(currentHeroArtifact2, &ClickablePixmapItem::clicked, this, &MainWindow::on_currentHeroArtifact2_clicked);
        iconX += interval;

        currentHeroArtifact3 = new ClickablePixmapItem();
        currentHeroArtifact3->setPixmap(QPixmap(player->getHero(1)->getArtifact(2)->getPathToArtifactIcon()).scaled(100, 100, Qt::KeepAspectRatio));
        scene4->addItem(currentHeroArtifact3);
        currentHeroArtifact3->setScale(0.75);
        currentHeroArtifact3->setPos(iconX - 50, 100);
        connect(currentHeroArtifact3, &ClickablePixmapItem::clicked, this, &MainWindow::on_currentHeroArtifact3_clicked);
        iconX += interval;
    }
}

void MainWindow::on_shopIcon3_clicked()
{
    currentHeroIndex = 2;
    if(player->getHero(2)->getArtifactsSize() < 3)
    {
        player->getHero(2)->addArtifact(allArtifacts[ui->tableWidget->currentRow()]);
        player->setMoney((-1) * allArtifacts[ui->tableWidget->currentRow()]->getCost());
        ui->label_5->setText(QString::number(player->getMoney()));
        scene4->clear();
        scene4->update();
        ui->graphicsView_4->hide();
        artifactsCharacter1.clear();
        artifactsCharacter2.clear();
        artifactsCharacter3.clear();
        ui->pushButton_Cancel->hide();

    }
    else
    {
        scene4->clear();
        scene4->update();


        double interval = ui->graphicsView_4->width() / 4.0;

        double iconX = 0;

        iconX += interval;

        currentHeroArtifact1 = new ClickablePixmapItem();
        currentHeroArtifact1->setPixmap(QPixmap(player->getHero(2)->getArtifact(0)->getPathToArtifactIcon()).scaled(100, 100, Qt::KeepAspectRatio));
        scene4->addItem(currentHeroArtifact1);
        currentHeroArtifact1->setScale(0.75);
        currentHeroArtifact1->setPos(iconX - 50, 100);
        connect(currentHeroArtifact1, &ClickablePixmapItem::clicked, this, &MainWindow::on_currentHeroArtifact1_clicked);
        iconX += interval;

        currentHeroArtifact2 = new ClickablePixmapItem();
        currentHeroArtifact2->setPixmap(QPixmap(player->getHero(2)->getArtifact(1)->getPathToArtifactIcon()).scaled(100, 100, Qt::KeepAspectRatio));
        scene4->addItem(currentHeroArtifact2);
        currentHeroArtifact2->setScale(0.75);
        currentHeroArtifact2->setPos(iconX - 50, 100);
        connect(currentHeroArtifact2, &ClickablePixmapItem::clicked, this, &MainWindow::on_currentHeroArtifact2_clicked);
        iconX += interval;

        currentHeroArtifact3 = new ClickablePixmapItem();
        currentHeroArtifact3->setPixmap(QPixmap(player->getHero(2)->getArtifact(2)->getPathToArtifactIcon()).scaled(100, 100, Qt::KeepAspectRatio));
        scene4->addItem(currentHeroArtifact3);
        currentHeroArtifact3->setScale(0.75);
        currentHeroArtifact3->setPos(iconX - 50, 100);
        connect(currentHeroArtifact3, &ClickablePixmapItem::clicked, this, &MainWindow::on_currentHeroArtifact3_clicked);
        iconX += interval;
    }
}

void MainWindow::on_currentHeroArtifact1_clicked()
{
    player->getHero(currentHeroIndex)->replaceArtifact(allArtifacts[ui->tableWidget->currentRow()], 0);
    player->setMoney((-1) * allArtifacts[ui->tableWidget->currentRow()]->getCost());
    ui->label_5->setText(QString::number(player->getMoney()));
    scene4->clear();
    scene4->update();
    ui->graphicsView_4->hide();
    artifactsCharacter1.clear();
    artifactsCharacter2.clear();
    artifactsCharacter3.clear();
    ui->pushButton_Cancel->hide();
}

void MainWindow::on_currentHeroArtifact2_clicked()
{
    player->getHero(currentHeroIndex)->replaceArtifact(allArtifacts[ui->tableWidget->currentRow()], 1);
    player->setMoney((-1) * allArtifacts[ui->tableWidget->currentRow()]->getCost());
    ui->label_5->setText(QString::number(player->getMoney()));
    scene4->clear();
    scene4->update();
    ui->graphicsView_4->hide();
    artifactsCharacter1.clear();
    artifactsCharacter2.clear();
    artifactsCharacter3.clear();
    ui->pushButton_Cancel->hide();
}

void MainWindow::on_currentHeroArtifact3_clicked()
{
    player->getHero(currentHeroIndex)->replaceArtifact(allArtifacts[ui->tableWidget->currentRow()], 2);
    player->setMoney((-1) * allArtifacts[ui->tableWidget->currentRow()]->getCost());
    ui->label_5->setText(QString::number(player->getMoney()));
    scene4->clear();
    scene4->update();
    ui->graphicsView_4->hide();
    artifactsCharacter1.clear();
    artifactsCharacter2.clear();
    artifactsCharacter3.clear();
    ui->pushButton_Cancel->hide();
}

void MainWindow::on_pushButton_Sort_clicked()
{
    sortShop();
    updateTableWidget();

}

void MainWindow::updateTableWidget()
{
    ui->tableWidget->setRowCount(allArtifacts.size());
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for(int i = 0; i < allArtifacts.size(); i++)
    {
        ui->tableWidget->setRowHeight(i, 78);
        ui->tableWidget->setColumnWidth(i, 78);
    }

    for(int i = 0; i < allArtifacts.size(); i++)
    {

        imageItem = new QTableWidgetItem;
        nameItem = new QTableWidgetItem;
        priceItem = new QTableWidgetItem;

        imageItem->setData(Qt::DecorationRole, QPixmap(allArtifacts[i]->getPathToArtifactIcon()));
        ui->tableWidget->setItem(i, 0, imageItem);
        ui->tableWidget->item(i, 0)->setToolTip(allArtifacts[i]->getNameOfArtifact() + "\n" + allArtifacts[i]->getStatsOfArtifact());

        nameItem->setText(allArtifacts[i]->getNameOfArtifact());
        ui->tableWidget->setItem(i, 1, nameItem);

        priceItem->setText(QString::number(allArtifacts[i]->getCost()));
        ui->tableWidget->setItem(i, 2, priceItem);
    }

}


void MainWindow::on_pushButton_AutoChoose_clicked()
{
    ui->pushButton_Back->show();
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    greedyAlgorithm();

    ui->pushButton_Sort->setDisabled(true);


    ui->tableWidget->setRowCount(bestArtifactsOption.size());
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for(int i = 0; i < bestArtifactsOption.size(); i++)
    {
        ui->tableWidget->setRowHeight(i, 78);
        ui->tableWidget->setColumnWidth(i, 78);
    }

    for(int i = 0; i < bestArtifactsOption.size(); i++)
    {

        imageItem = new QTableWidgetItem;
        nameItem = new QTableWidgetItem;
        priceItem = new QTableWidgetItem;

        imageItem->setData(Qt::DecorationRole, QPixmap(bestArtifactsOption[i]->getPathToArtifactIcon()));
        ui->tableWidget->setItem(i, 0, imageItem);
        ui->tableWidget->item(i, 0)->setToolTip(bestArtifactsOption[i]->getNameOfArtifact() + "\n" + bestArtifactsOption[i]->getStatsOfArtifact());

        nameItem->setText(bestArtifactsOption[i]->getNameOfArtifact());
        ui->tableWidget->setItem(i, 1, nameItem);

        priceItem->setText(QString::number(bestArtifactsOption[i]->getCost()));
        ui->tableWidget->setItem(i, 2, priceItem);
    }
}


void MainWindow::on_pushButton_Back_clicked()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    ui->pushButton_Sort->setDisabled(false);
    updateTableWidget();
    ui->pushButton_Back->hide();
}


void MainWindow::on_pushButton_LeaveShop_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->menu);
}


void MainWindow::on_pushButton_Cancel_clicked()
{
    scene4->clear();
    scene4->update();
    ui->graphicsView_4->hide();
    artifactsCharacter1.clear();
    artifactsCharacter2.clear();
    artifactsCharacter3.clear();

    ui->pushButton_Cancel->hide();
}


void MainWindow::on_pushButton_LeaveGame_clicked()
{
    QApplication::exit(0);
}

