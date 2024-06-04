#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStandardItemModel>
#include <QTableWidgetItem>
#include <algorithm>
#include "hero.h"
#include "clickablepixmapitem.h"
#include "player.h"
#include "game.h"
#include "artifact.h"
#include "artifactpixmapitem.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void handleGameFinished(QString status, double totalDamage, double damageHero1, double damageHero2, double damageHero3);

private slots:
    void on_pushButton_Play_clicked();

    void playBackground();

    void on_characterIcon1_clicked();

    void on_characterIcon2_clicked();

    void on_pushButton_2_clicked();

    void on_characterIcon3_clicked();

    void quickSort(QVector<int> &vec, int low, int high);

    int partition(QVector<int> &vec, int low, int high);

    void on_pushButton_clicked();

    void handleLabelDeletion();

    void on_pushButton_3_clicked();

    void greedyAlgorithm();

    void sortShop();

    void on_pushButton_Fight_clicked();

    void on_pushButton_Shop_clicked();

    void on_pushButton_Buy_clicked();

    void on_shopIcon1_clicked();

    void on_shopIcon2_clicked();

    void on_shopIcon3_clicked();

    void on_currentHeroArtifact1_clicked();

    void on_currentHeroArtifact2_clicked();

    void on_currentHeroArtifact3_clicked();

    void on_pushButton_Sort_clicked();

    void updateTableWidget();

    void on_pushButton_AutoChoose_clicked();

    void on_pushButton_Back_clicked();

    void on_pushButton_LeaveShop_clicked();

    void on_pushButton_Cancel_clicked();

    void on_pushButton_LeaveGame_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsScene *scene2;
    QGraphicsScene *scene3;
    QGraphicsScene *scene4;

    int currentHeroIndex;

    QGraphicsScene *sceneForGifMenu;
    QGraphicsScene *sceneForColorMenu;

    QMovie *background;
    Hero *warrior;
    Hero *rogach;
    Hero *enemy;
    Hero *kungFuGirl;
    QGraphicsPixmapItem *itemBackground;
    ClickablePixmapItem *characterIcon1;
    ClickablePixmapItem *characterIcon2;
    ClickablePixmapItem *characterIcon3;

    ClickablePixmapItem *currentHeroArtifact1;
    ClickablePixmapItem *currentHeroArtifact2;
    ClickablePixmapItem *currentHeroArtifact3;

    ClickablePixmapItem *shopIcon1;
    QVector<ArtifactPixmapItem *> artifactsCharacter1;
    ClickablePixmapItem *shopIcon2;
    QVector<ArtifactPixmapItem *> artifactsCharacter2;
    ClickablePixmapItem *shopIcon3;
    QVector<ArtifactPixmapItem *> artifactsCharacter3;

    QGraphicsPixmapItem *backgroundScene2;
    QGraphicsPixmapItem *coins;
    QMovie *anim;
    QGraphicsPixmapItem *itemAnim;
    Player *player;
    Game *game;
    QList<bool> positions;
    QVector<Artifact *> allArtifacts;
    QVector<Artifact *> bestArtifactsOption;

    QLabel *label;

    QLabel *dmgHero1;
    QLabel *dmgHero2;
    QLabel *dmgHero3;
    QLabel *numberOfCoins;
    QVector<QLabel *> dmgHeroes;

    QStandardItemModel* model;
    QTableWidgetItem *imageItem;
    QTableWidgetItem *nameItem;
    QTableWidgetItem *priceItem;

};
#endif // MAINWINDOW_H
