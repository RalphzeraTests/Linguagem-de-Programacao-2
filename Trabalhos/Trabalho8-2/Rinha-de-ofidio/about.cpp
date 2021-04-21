#include "about.hpp"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    QMovie *movie = new QMovie(":/images/About.gif");
    ui->AboutLabel->setMovie(movie);
    movie->start();
}

About::~About()
{
    delete ui;
}
