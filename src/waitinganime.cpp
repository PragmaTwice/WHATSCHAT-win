#include "waitinganime.h"

WaitingAnime::WaitingAnime(const QRect &rect, const QColor &color, QWidget *parent) :
    QGraphicsView(parent),
    loginingItem(nullptr),
    loginingAnimation(nullptr),
    loginingScene(nullptr),
    loginingTimer(nullptr)
{
    this->setGeometry(rect.x(),rect.y(),rect.width(),rect.height());

    constexpr int itemCount = 5;

    loginingItem = new QGraphicsEllipseItem[itemCount];
    for (int i = 0; i < itemCount; ++i)
    {
        loginingItem[i].setRect(-20*(i+1),5,6,6);
        loginingItem[i].setPen(QPen(color));
        loginingItem[i].setBrush(QBrush(color));
    }

    loginingTimer = new QTimeLine(3000);
    loginingTimer->setFrameRange(0, 100);

    loginingAnimation = new QGraphicsItemAnimation[itemCount];
    int stepCount = this->width() + 20*(itemCount + 1);
    for (int i = 0; i < itemCount; ++i)
    {
        loginingAnimation[i].setItem(loginingItem + i);
        loginingAnimation[i].setTimeLine(loginingTimer);

        for (double j = 0; j < stepCount; ++j)
            loginingAnimation[i].setPosAt(j / stepCount, QPointF(j*(1 + i*0.1),0));
    }

    loginingScene = new QGraphicsScene(0,0,this->width(),this->height());
    for (int i = 0; i < itemCount; ++i) loginingScene->addItem(loginingItem + i);

    loginingTimer->setLoopCount(0);

    this->setScene(loginingScene);
    this->setRenderHints(QPainter::Antialiasing);
    this->show();

    this->setVisible(false);
}

WaitingAnime::~WaitingAnime()
{

    delete[] loginingItem;
    delete[] loginingAnimation;
    delete loginingScene;
    delete loginingTimer;
}

void WaitingAnime::start()
{
    this->setVisible(true);

    loginingTimer->start();
}

void WaitingAnime::stop()
{
    this->setVisible(false);

    loginingTimer->stop();
}
