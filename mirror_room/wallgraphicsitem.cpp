#include "wallgraphicsitem.h"

#include <QVector2D>
#include <QtMath>
#include <QPainter>

#include <QDebug>

WallGraphicsItem::WallGraphicsItem(Wall *pWall, QGraphicsItem *parent)
    : QGraphicsObject(parent)
{
    Q_ASSERT(pWall != NULL);
    wall = pWall;
    calcPath();

    connect(wall, SIGNAL(changed()), this, SLOT(calcPath()));
    connect(wall, SIGNAL(changed()), this, SLOT(updateItem()));

    setAcceptHoverEvents(true);
}

qreal angle(qreal x1, qreal y1, qreal x2, qreal y2)
{
    return (((x1 * y2 - y1 * x2) <0 ) ? -1 : 1) *qAcos((x1*x2 + y1*y2)/ qSqrt(x1*x1 + y1*y1) / qSqrt(x2*x2+y2*y2));;
}
void WallGraphicsItem::calcPath()
{
    QPainterPath result;
    QPoint left = wall->getLeft();
    QPoint right = wall->getRight();
    if (wall->getType() == Wall::Straight) {
        result.moveTo(left);
        result.lineTo(right);
    }
    else {
        qreal radius = wall->getRadius();

        QPointF chordCenter((left.x() + right.x()) *1. / 2, (left.y() + right.y()) * 1. / 2);
        QVector2D chord(right.x() - left.x(), right.y() - left.y());
        qreal x2 = ((wall->getType() == Wall::Arched) ? -chord.y() : +chord.y());
        qreal y2 = ((wall->getType() == Wall::Arched) ? +chord.x() : -chord.x());
        QVector2D rad(x2, y2);
        qreal chordHalfLength = chord.length() / 2;
        rad.normalize();
        rad *= radius * qSin(qAcos(chordHalfLength/ radius));
        qDebug() << "radius" << rad;
        QPoint center(chordCenter.x() + rad.x(), chordCenter.y() + rad.y());
        wall->setCenter(center);
//        qreal startAngle = M_PI/2 +qAsin((center.x() - right.x()) * 1./radius);

        qDebug() << "center" << center;
        qreal startAngle = /*-*/angle(right.x() - center.x(), right.y() - center.y(),
                                 1, 0);
        qreal spanAngle(2 * qAsin(chordHalfLength / radius));
        startAngle *= 180.0 / M_PI /** 16*/;
        wall->setStartAngle(startAngle);
        spanAngle *= 180.0 / M_PI  /** 16*/;
        if (wall->getType() == Wall::Convex)
            spanAngle *= -1;
        wall->setSpanAngle(spanAngle);
        qDebug() << "startAngle" << startAngle;
        qDebug() << "spanAngle" << spanAngle;
        qDebug() << "rect" << QRectF(center.x()-radius, center.y()-radius, 2*radius, 2*radius);
        QRectF outerRect(center.x()-radius, center.y()-radius, 2*radius, 2*radius);
        result.arcMoveTo(outerRect, startAngle);
        result.arcTo(outerRect, startAngle, spanAngle);
    }
    path = result;
    qDebug() << "calcPath" << path << "for" << wall->getTitle();
}

void WallGraphicsItem::updateItem()
{
    update();
}

QRectF WallGraphicsItem::boundingRect() const
{
    return QRectF(0, 0, 1000, 1000);
}

QPainterPath WallGraphicsItem::shape() const
{
    return path;
}

void WallGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter->setPen(QPen(QBrush(Qt::black), 2));
    painter->drawPath(path);
}

void WallGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
//    qDebug() << "Hi, I am" << wall->getTitle() << "!";
    QGraphicsItem::hoverEnterEvent(event);
}
