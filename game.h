#ifndef GAME_H
#define GAME_H

#include <QRandomGenerator>
#include <QTimer>
#include "hero.h"
#include "player.h"
#include "clickablepixmapitem.h"

class Game: public QWidget
{
    Q_OBJECT
public:
    Game(QGraphicsScene* Scene, QGraphicsScene *sceneForTips, Player *Player);
    bool checkIsEnemysAlive();
    bool checkIsHeroesAllive();
    void startGame();
    void enemyAttack();
    void skillChooser();
    void setEnemies();
    void restartGame(QGraphicsScene *sceneForTips);
signals:
    void gameFinished(QString status, double totalDamage, double damageHero1, double damageHero2, double damageHero3);
private slots:
    void on_attackIcon1_clicked();
    void on_attackIcon2_clicked();
    void on_attackIcon3_clicked();
private:

    int pos1X;
    double damageHero1;
    double damageHero2;
    double damageHero3;
    double totalDamage;
    QVector <Hero*> enemys;
    QGraphicsScene *scene;
    Player *player;
    bool isPlayerTurn;
    QGraphicsRectItem *rect;
    ClickablePixmapItem *attackIcon1;
    ClickablePixmapItem *attackIcon2;
    ClickablePixmapItem *attackIcon3;
    QTimer *timerEnemyAttackEnd;
    QTimer *timerPlayerAttacEnd;
};

#endif // GAME_H
