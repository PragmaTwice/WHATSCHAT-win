#include "messagebar.h"

MessageBar::MessageBar(QWidget *parent, uint height) :
    QLabel(parent),
    up_anime(nullptr),
    down_anime(nullptr),
    timer(nullptr)
{
    QRect up_geom(0,parent->height() - height,parent->width(),height);
    QRect down_geom(0,parent->height(),parent->width(),height);
    setGeometry(down_geom);

    setFont(QFont("Segoe UI", height*0.4));
    setAlignment(Qt::AlignCenter);

    up_anime = new QPropertyAnimation(this, "geometry");
    up_anime->setDuration(height*10);
    up_anime->setStartValue(down_geom);
    up_anime->setEndValue(up_geom);

    down_anime = new QPropertyAnimation(this, "geometry");
    down_anime->setDuration(height*10);
    down_anime->setStartValue(up_geom);
    down_anime->setEndValue(down_geom);

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(messageOut()));

    connect(up_anime,SIGNAL(finished()),this,SLOT(slot_messageInFinished()));
    connect(down_anime,SIGNAL(finished()),this,SLOT(slot_messageOutFinished()));

}

MessageBar::~MessageBar()
{
    delete up_anime;
    delete down_anime;
    delete timer;
}

void MessageBar::messageOut()
{
    if(timer->isActive()) timer->stop();
    down_anime->start();
}

void MessageBar::slot_messageInFinished()
{
    emit messageInFinished();
}

void MessageBar::slot_messageOutFinished()
{
    emit messageOutFinished();
}

void MessageBar::message(const QString &content, const QColor &back_color, const QColor &text_color, uint interval)
{
    messageIn(content,back_color,text_color);

    timer->start(interval);

}

void MessageBar::messageIn(const QString &content, const QColor &back_color, const QColor &text_color)
{
    setStyleSheet(QString("border: 0;background: %1;color: %2").arg(back_color.name()).arg(text_color.name()));
    setText("<p>"+content+"</p>");

    up_anime->start();
}

void MessageBar::information(const QString &content, const QColor &back_color, const QColor &text_color, uint interval)
{
    message(QString("<img src='qrc:/ico/information' width='%1' height='%1'/>&nbsp; ").arg(height()/1.5) + content,back_color,text_color,interval);
}

void MessageBar::warning(const QString &content, const QColor &back_color, const QColor &text_color, uint interval)
{
    message(QString("<img src='qrc:/ico/warning' width='%1' height='%1'/>&nbsp; ").arg(height()/1.5) + content,back_color,text_color,interval);
}
