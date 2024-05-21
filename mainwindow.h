#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "hero.h"
#include "clickablepixmapitem.h"

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

private slots:
    void on_pushButton_Play_clicked();

    void playBackground();

    void on_pushButton_clicked();

    void on_characterIcon1_clicked();

    void on_characterIcon2_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsScene *scene2;
    QMovie *background;
    Hero *warrior;
    Hero *enemy;
    QGraphicsPixmapItem *itemBackground;
    ClickablePixmapItem *characterIcon1;
    ClickablePixmapItem *characterIcon2;
    QGraphicsPixmapItem *backgroundScene2;
    QMovie *anim;
    QGraphicsPixmapItem *itemAnim;
};
#endif // MAINWINDOW_H
