#include "snake.h"
#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsItem>
#include <QDebug>
#include <QKeyEvent>
#include <stdlib.h>
#include <iostream>
#include <QPointF >
using namespace std;
//#include "bullet.h"
//#include "enemy.h"

#include "food.h"
Snake::Snake()
{
    {
    }
}
Snake::Snake(QString t)
{
    tipo = t;
    //
    isVivo = true;
    ready = false;
    BodyPart *p = new BodyPart();
    p->lastAction = "Left";
    QString image;

    p->setPixmap(QPixmap("://images/"+tipo+"Left.png"));
    p->setPos(32*4+floor(32 * (rand() % 12)), 32*4+floor(32 * (rand() % 12)));
    myBody.emplace_back(p);

    /*
    bulletsound = new QMediaPlayer();
    bulletsound->setMedia(QUrl("qrc:/sounds/Laser.mp3"));*/
}
void Snake::die()
{
    cout << "Morri" << endl;
    isVivo = false;
}
void Snake::move(string decisao)
{
    if (!ready)
        return;
    vector<string> ant;

    for (BodyPart *part : myBody)
    {
        //cout << part->pos().x() << ";" << part->pos().y() << "(" << part->lastAction << ")"
            // << " - ";
    }
    cout << endl;
    for (size_t i = myBody.size() - 1; i > 0; i--)
    {
        myBody.at(i)->setPos(myBody.at(i - 1)->pos());
    }
    myBody.at(0)->lastAction = decisao;
    isVivo = myBody.at(0)->move(decisao);
    myBody.at(0)->setPixmap(QPixmap("://images/"+tipo+QString::fromStdString(decisao)+".png"));
    QList<QGraphicsItem *> colliding_item = myBody.at(0)->collidingItems();
    for (int i = 0, n = colliding_item.size(); i < n; i++)
    {
        if (typeid(*(colliding_item[i])) == typeid(BodyPart))
        {
            bool achou = true;
            for (BodyPart *part : myBody)
            {
                if (part == colliding_item[i])
                {
                    achou = false;
                }
            }
            if (achou)
                die();
        }
    }
}
void Snake::addNew()
{
    string lastA = myBody.at(myBody.size() - 1)->lastAction;
    QPointF lastP = myBody.at(myBody.size() - 1)->pos();
    BodyPart *p = new BodyPart();

    p->setPixmap(QPixmap("://images/"+tipo+"Body.png"));
    //p->setRect(0,0,32,32);
    p->setPos(lastP);
    p->lastAction = lastA;
    p->setFlag(QGraphicsItem::ItemIsFocusable);
    p->setFocus();
    myBody.emplace_back(p);
}
