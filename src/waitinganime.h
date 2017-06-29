#ifndef WAITINGANIME_H
#define WAITINGANIME_H

#include <QGraphicsView>
#include <QTimeLine>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsItemAnimation>

class WaitingAnime : public QGraphicsView
{
    Q_OBJECT

    QGraphicsEllipseItem* loginingItem;
    QGraphicsItemAnimation* loginingAnimation;
    QGraphicsScene* loginingScene;
    QTimeLine* loginingTimer;

public:
    explicit WaitingAnime(const QRect& rect, const QColor& color = Qt::white, QWidget *parent = nullptr);

    ~WaitingAnime();

signals:

public slots:
    void start();
    void stop();

};

#endif // WAITINGANIME_H
