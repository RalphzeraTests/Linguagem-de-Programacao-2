#ifndef GAME_H
#define GAME_H
#include "snake.h"
#include "food.h"
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QString>
#include <QTimer>
#include <QMediaPlayer>
#include <iostream>
using namespace std;

class Estado
{
public:
    Estado(){};
    ~Estado() {}
    vector<Food *> food;
};

class GameEnv : public QGraphicsView
{
private:
    QMediaPlayer *musicBg;
    QGraphicsPixmapItem *startBg;

    Snake *player;
    Snake *enemy;
    Estado state;
    vector<QString> tipo;
    QString inimigoAgent;
    int rodada;
    QTimer *timer;
    bool ready;

private:
    void newGame();
    void gameExecution();
    void refresh();
    void clean();
    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event)
    {
        ready = false;
        timer->stop();
        delete player;
        delete enemy;
        for (int i = 0; i < scene->items().size(); i++)
        {
            scene->items().at(i)->setEnabled(false);
        }
        delete musicBg;
        hide();
        return;
    }
    void mousePressEvent(QMouseEvent *event)
    {
        //if(ready) player->addNew();
        if (!ready)
        {
            QMediaPlayer *music = new QMediaPlayer(this);
            music->setMedia(QUrl("qrc:/GameStart.wav"));
            music->play();
            delete startBg;
            ready = true;
        }
    }

public:
    GameEnv(QWidget *parent = 0);
    QGraphicsScene *scene;


public:
    void gameExecution(int r);

private:
    void movePlayer()
    {

        player->move();
    }
    void agent()
    {
        cout << inimigoAgent.toStdString() << endl;
        if (ready)
        {

            if (inimigoAgent == "Normal")
            {
                agentNormal(state);
            }
            else
            {
                agentBoss(state);
            }
        }
    }
    void agentNormal(Estado estado)
    {

        if (estado.food.at(0)->y() > enemy->myBody.at(0)->y())
        {
            enemy->move("Down");
            return;
        }
        else
        {
            if (estado.food.at(0)->y() < enemy->myBody.at(0)->y())
            {
                enemy->move("Up");
                return;
            }
            else
            {
                if (estado.food.at(0)->x() > enemy->myBody.at(0)->x())
                {
                    enemy->move("Right");
                    return;
                }
            }
        }
        enemy->move("Left");
    }
    void agentBoss(Estado estado)
    {
        cout << "Enemy" << endl;
        enemy->move("Up");
    }
};

#endif // GAME_H
