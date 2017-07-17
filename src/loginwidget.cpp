#include "loginwidget.h"
#include "ui_loginwidget.h"
#include <QDebug>

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget),
    loginingAnime(nullptr),
    msgBar(nullptr),
    usernameCol(nullptr),
    certifyCol(nullptr),
    dateCol(nullptr),
    nowCol(nullptr),
    systemColor(QtWin::realColorizationColor())
{
    ui->setupUi(this);
    ui->backButton->setVisible(false);

    setAttribute(Qt::WA_NoSystemBackground, false);
    setStyleSheet(QString("LoginWidget{ background: %1; }").arg(systemColor.name()));

    setFixedSize(width(),height());

    loginingAnime = new WaitingAnime(QRect(20,260,321,31),Qt::white,this);
    loginingAnime->setStyleSheet(QString("QGraphicsView{ border: 0;background: %1; }").arg(systemColor.name()));

    msgBar = new MessageBar(this,30);

    QRect colRect = QRect(20,225,330,45);
    QRect colRightRect = QRect(20 + width(),225,330,45);
    QDateTime nowDateTime = QDateTime::currentDateTime().addSecs(600);

    usernameCol = new ButtonEdit(colRect,QIcon(":/ico/next"),this,"USER NAME...");
    dateCol = new ButtonDateEdit(colRightRect,QIcon(":/ico/register"),nowDateTime,nowDateTime.addDays(30),systemColor.lighter(150).name(),this,"EXPIRE DATE...");
    certifyCol = new ButtonEdit(colRightRect,QIcon(":/ico/login"),this,"USER CERTIFY...");

    nowCol = usernameCol;

    connect(usernameCol,SIGNAL(buttonClicked(bool)),this,SLOT(usernameButtonClicked(bool)));
    connect(usernameCol,SIGNAL(endMoveBy()),this,SLOT(colMoveEnd()));

    connect(dateCol,SIGNAL(buttonClicked(bool)),this,SLOT(dateButtonClicked(bool)));
    connect(certifyCol,SIGNAL(buttonClicked(bool)),this,SLOT(certifyButtonClicked(bool)));

}

LoginWidget::~LoginWidget()
{
    delete ui;
    delete loginingAnime;
    delete msgBar;
    delete usernameCol;
    delete dateCol;

}

void LoginWidget::usernameButtonClicked(bool)
{
    if(checkColBlank(usernameCol,"cannot leave username blank")) return;

    loginingAnime->start();

    bool userIsExist = false;
    try
    {
        userIsExist = user::is_exist(usernameCol->refEdit().text());
    }
    catch(user_error& err)
    {
        forceStopColProcess(usernameCol,(err.tag == user_error::network_error)?
                            "network error, please check your connection." : err.reason);
        return;
    }

    ui->backButton->setVisible(true);

    if(userIsExist) nextColProcess(usernameCol,certifyCol,"please input your certify");
    else nextColProcess(usernameCol,dateCol,"now to create the user...");
}

void LoginWidget::colMoveEnd()
{
    loginingAnime->stop();
}

void LoginWidget::dateButtonClicked(bool)
{
    if(checkColBlank(dateCol,"cannot leave expire date blank")) return;

    loginingAnime->start();
    ui->backButton->setVisible(false);

    user* userPtr = nullptr;
    try
    {
        userPtr = new user(usernameCol->refEdit().text(),dateCol->dateTime());
    }
    catch(user_error& err)
    {
        forceStopColProcess(dateCol,(err.tag == user_error::network_error)?
                            "network error, please check your connection." : err.reason);
        return;
    }

    nextColProcess(dateCol,nullptr,QString("your certify: <b>%1</b> , welcome...").arg(userPtr->get_certify()),10000);
    qDebug() << *userPtr;

}

void LoginWidget::certifyButtonClicked(bool)
{
    if(checkColBlank(certifyCol,"cannot leave user certify blank")) return;

    uint certify = certifyCol->refEdit().text().toUInt();
    if(certify == 0)
    {
        forceStopColProcess(certifyCol,"cannot input the invaild certify");
        return;
    }

    loginingAnime->start();
    ui->backButton->setVisible(false);

    user* userPtr = nullptr;
    try
    {
        userPtr = new user(usernameCol->refEdit().text(),certify);
    }
    catch(user_error& err)
    {
        forceStopColProcess(certifyCol,(err.tag == user_error::network_error)?
                            "network error, please check your connection." : err.reason);
        return;
    }

    nextColProcess(certifyCol,nullptr,"welcome back to WHATSCHAT...");
    qDebug() << *userPtr;

}

void LoginWidget::forceStopColProcess(ButtonEdit * const col, const QString &warningString)
{
    msgBar->warning(warningString);
    col->clickedProcessEnd();
    loginingAnime->stop();
    if(nowCol != usernameCol) ui->backButton->setVisible(true);
}

bool LoginWidget::checkColBlank(ButtonEdit * const col, const QString &warningString)
{
    if(col->refEdit().text() == "")
    {
        forceStopColProcess(col,warningString);
        return true;
    }

    return false;
}

void LoginWidget::nextColProcess(ButtonEdit * const _nowCol, ButtonEdit * const nextCol, const QString& infoString, uint interval)
{
    if(infoString != "") msgBar->information(infoString,systemColor.darker(150),Qt::white,interval);

    if(_nowCol != nullptr) _nowCol->startMoveBy({(float)width(),0});
    if(nextCol != nullptr) nextCol->startMoveBy({(float)width(),0});

    nowCol = nextCol;
}

void LoginWidget::backColProcess(ButtonEdit * const _nowCol, ButtonEdit * const backCol, const QString& infoString, uint interval)
{
    if(infoString != "") msgBar->information(infoString,systemColor.darker(150),Qt::white,interval);

    if(_nowCol != nullptr)
    {
        _nowCol->startMoveBy({(float)(-width()),0});
        _nowCol->setEditText("");
    }
    if(backCol != nullptr)
    {
        backCol->startMoveBy({(float)(-width()),0});
        backCol->clickedProcessEnd();
    }

    nowCol = backCol;
}


void LoginWidget::on_backButton_clicked(bool)
{
    backColProcess(nowCol,usernameCol);
    ui->backButton->setVisible(false);
}
