#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    loginingAnime(nullptr),
    msgBar(nullptr),
    usernameCol(nullptr)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_NoSystemBackground, false);
    setStyleSheet(QString("Widget{ background: %1; }").arg(QtWin::realColorizationColor().name()));

    setFixedSize(width(),height());

    loginingAnime = new WaitingAnime(QRect(20,260,321,31),Qt::white,this);
    loginingAnime->setStyleSheet(QString("QGraphicsView{ border: 0;background: %1; }").arg(QtWin::realColorizationColor().name()));

    msgBar = new MessageBar(this,30);

    usernameCol = new ButtonEdit(QRect(20,225,330,45),QIcon(":/ico/login"),this,"USER NAME...");

    connect(usernameCol,SIGNAL(buttonClicked(bool)),this,SLOT(usernameButtonClicked(bool)));

}

Widget::~Widget()
{
    delete ui;
    delete loginingAnime;
    delete msgBar;
    delete usernameCol;

}

void Widget::usernameButtonClicked(bool)
{
    if(usernameCol->refEdit().text() == "")
    {
        msgBar->warning("cannot leave username blank");
        usernameCol->clickedProcessEnd();
        return;
    }

    msgBar->information("hello, i am WHATSCHAT", QtWin::realColorizationColor().darker(150));
    loginingAnime->start();
}
