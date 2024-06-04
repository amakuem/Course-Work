#include "game.h"

Game::Game(QGraphicsScene* Scene, QGraphicsScene * sceneForTips, Player *Player)
{
    scene = Scene;
    player = Player;
    int m = 0;
    m = 0;
    isPlayerTurn = false;
    timerEnemyAttackEnd = new QTimer();
    timerPlayerAttacEnd = new QTimer();

    damageHero1 = 0;
    damageHero2 = 0;
    damageHero3 = 0;

    connect(timerEnemyAttackEnd, &QTimer::timeout, this, &Game::startGame);
    connect(timerPlayerAttacEnd, &QTimer::timeout, this, &Game::startGame);
}

void Game::startGame()
{
    if(timerEnemyAttackEnd->isActive())
    {
        timerEnemyAttackEnd->stop();
    }
    if(timerPlayerAttacEnd->isActive())
    {
        timerPlayerAttacEnd->stop();
    }
    if(checkIsEnemysAlive() && checkIsHeroesAllive())
    {
        if(!isPlayerTurn)
        {
            enemyAttack();

        }
        else
        {
            skillChooser();
        }
    }
    else
    {
        totalDamage = damageHero1 + damageHero2 + damageHero3;
        QString status;
        if(checkIsEnemysAlive())
        {
            status = "YOU LOSE";
        }
        else if(checkIsHeroesAllive())
        {
            status = "YOU WIN";
        }

        for(int i = 0; i < 3; i++)
        {
            if(scene->items().contains(enemys[i]->getItemIdle()))
            {
                scene->removeItem(enemys[i]->getItemIdle());
                scene->removeItem(enemys[i]->getItemAttack());
                scene->removeItem(enemys[i]->getHealthBar());
            }
            if(i < player->getHeroInBattleFieldSize())
            {
                player->getHeroInBattleField(i)->fullRecovery();
            }
        }
        enemys.clear();
        isPlayerTurn = false;

        emit gameFinished(status, totalDamage, damageHero1, damageHero2, damageHero3);

        damageHero1 = 0;
        damageHero2 = 0;
        damageHero3 = 0;
        totalDamage = 0;
    }
}

bool Game::checkIsEnemysAlive()
{
    for(int i = 0; i < 3; i++)
    {
        if(enemys[i]->getIsAlive())
        {
            return true;
        }
        else
        {
            scene->removeItem(enemys[i]->getItemIdle());
            scene->removeItem(enemys[i]->getItemAttack());
            scene->removeItem(enemys[i]->getHealthBar());
        }
    }
    return false;
}

bool Game::checkIsHeroesAllive()
{
    for(int i = 0; i < player->getHeroInBattleFieldSize(); i++)
    {
        if(player->getHeroInBattleField(i)->getIsAlive())
        {
            return true;
        }
        else
        {
            scene->removeItem(player->getHeroInBattleField(i)->getItemIdle());
            scene->removeItem(player->getHeroInBattleField(i)->getItemAttack());
            scene->removeItem(player->getHeroInBattleField(i)->getHealthBar());
        }
    }
    return false;
}

void Game::enemyAttack()
{
    int index = QRandomGenerator::global()->bounded(3);
    while(!enemys[index]->getIsAlive())
    {
        index = QRandomGenerator::global()->bounded(3);
    }

    for(int i = player->getHeroInBattleFieldSize() - 1; i >= 0; i--)
    {
        if(player->getHeroInBattleField(i)->getIsAlive())
        {
            enemys[index]->attack(player->getHeroInBattleField(i), player->getHeroInBattleField(i)->getPositionX() + 100);
            break;
        }
    }

    isPlayerTurn = true;
    timerEnemyAttackEnd->start(5000);//5000
}

void Game::skillChooser()
{
    rect = new QGraphicsRectItem();
    rect->setRect(0, 0, 498, 200);
    rect->setPos(1920 / 2 - 452, 0);
    rect->setBrush(Qt::black);
    rect->setOpacity(0.3);
    scene->addItem(rect);

    double iconX = 508;

    int numAliveHeroes = 0;
    for (int i = 0; i < player->getHeroInBattleFieldSize(); ++i)
    {
        if (player->getHeroInBattleField(i)->getIsAlive())
            ++numAliveHeroes;
    }

    pos1X = 498 / (numAliveHeroes + 1);

    iconX += pos1X;
    if(player->getHeroInBattleField(0)->getIsAlive())
    {
        attackIcon1 = new ClickablePixmapItem();
        attackIcon1->setPixmap(QPixmap(player->getHeroInBattleField(0)->getPathToAttackIcon()).scaled(100, 100, Qt::KeepAspectRatio));
        scene->addItem(attackIcon1);
        attackIcon1->setScale(0.75);
        attackIcon1->setPos(iconX - 50, 50);
        connect(attackIcon1, &ClickablePixmapItem::clicked, this, &Game::on_attackIcon1_clicked);
        iconX += pos1X;
    }

    if(player->getHeroInBattleFieldSize() >= 2)
    {
        if(player->getHeroInBattleField(1)->getIsAlive())
        {
            attackIcon2 = new ClickablePixmapItem();
            attackIcon2->setPixmap(QPixmap(player->getHeroInBattleField(1)->getPathToAttackIcon()).scaled(100, 100, Qt::KeepAspectRatio));
            scene->addItem(attackIcon2);
            attackIcon2->setScale(0.75);
            attackIcon2->setPos(iconX - 50, 50);
            connect(attackIcon2, &ClickablePixmapItem::clicked, this, &Game::on_attackIcon2_clicked);
            iconX += pos1X;
        }
    }

    if(player->getHeroInBattleFieldSize() == 3)
    {
        if(player->getHeroInBattleField(2)->getIsAlive())
        {
            attackIcon3 = new ClickablePixmapItem();
            attackIcon3->setPixmap(QPixmap(player->getHeroInBattleField(2)->getPathToAttackIcon()).scaled(100, 100, Qt::KeepAspectRatio));
            scene->addItem(attackIcon3);
            attackIcon3->setScale(0.75);
            attackIcon3->setPos(iconX - 50, 50);
            connect(attackIcon3, &ClickablePixmapItem::clicked, this, &Game::on_attackIcon3_clicked);
        }
    }

}

void Game::on_attackIcon1_clicked()
{
    for(int i = 0; i < 3; i++)
    {
        if(enemys[i]->getIsAlive())
        {
            player->getHeroInBattleField(0)->attack(enemys[i], enemys[i]->getPositionX() - 100);
            break;
        }
    }

    scene->removeItem(rect);
    scene->removeItem(attackIcon1);
    if(scene->items().contains(attackIcon2))
    {
        scene->removeItem(attackIcon2);
    }
    if(scene->items().contains(attackIcon3))
    {
        scene->removeItem(attackIcon3);
    }

    isPlayerTurn = false;
    damageHero1 += player->getHeroInBattleField(0)->getHeroDamageValue();
    timerPlayerAttacEnd->start(5000);
}

void Game::on_attackIcon2_clicked()
{
    for(int i = 0; i < 3; i++)
    {
        if(enemys[i]->getIsAlive())
        {
            player->getHeroInBattleField(1)->attack(enemys[i], enemys[i]->getPositionX() - 100);
            break;
        }
    }

    scene->removeItem(rect);
    scene->removeItem(attackIcon1);
    if(scene->items().contains(attackIcon2))
    {
        scene->removeItem(attackIcon2);
    }
    if(scene->items().contains(attackIcon3))
    {
        scene->removeItem(attackIcon3);
    }

    isPlayerTurn = false;
    damageHero2 += player->getHeroInBattleField(1)->getHeroDamageValue();
    timerPlayerAttacEnd->start(5000);
}

void Game::on_attackIcon3_clicked()
{
    for(int i = 0; i < 3; i++)
    {
        if(enemys[i]->getIsAlive())
        {
            player->getHeroInBattleField(2)->attack(enemys[i], enemys[i]->getPositionX() - 100);
            break;
        }
    }

    scene->removeItem(rect);
    scene->removeItem(attackIcon1);
    if(scene->items().contains(attackIcon2))
    {
        scene->removeItem(attackIcon2);
    }
    if(scene->items().contains(attackIcon3))
    {
        scene->removeItem(attackIcon3);
    }

    isPlayerTurn = false;
    damageHero3 += player->getHeroInBattleField(2)->getHeroDamageValue();
    timerPlayerAttacEnd->start(5000);
}

void Game::setEnemies()
{
    for(int i = 0; i < 3; i++)
    {
        scene->addItem(enemys[i]->getItemAttack());
    }
}

void Game::restartGame(QGraphicsScene *sceneForTips)
{
    int m = 0;
    for(int i = 0; i < 3; i++)
    {
        // scene->removeItem(enemys[i]->getItemIdle());
        // scene->removeItem(enemys[i]->getHealthBar());
        Hero *enemy = new Hero(":/heroes/hero/enemy/krolIdle.gif", ":/heroes/hero/enemy/krolAttack.gif", 0.62, ":/heroes/hero/enemy/krolAttack.gif",":/heroes/hero/enemy/krolIdle.gif", 0.5, ":/heroes/hero/enemy/krolAvatar.png", 100, 223,-1, 38, 118, 0, -100, sceneForTips);
        enemys.append(enemy);
        enemys[i]->setPosition(900 + m * 200, 510);
        scene->addItem(enemys[i]->getItemIdle());
        scene->addItem(enemys[i]->getHealthBar());
        enemys[i]->startAnimation();
        m++;
    }
}
