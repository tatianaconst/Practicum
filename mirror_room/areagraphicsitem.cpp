#include "areagraphicsitem.h"
#include <QPainterPath>
#include <QPainter>
#include <QDebug>

AreaGraphicsItem::AreaGraphicsItem(AreaModel *pmodel, QGraphicsItem *parent)
    :QGraphicsObject(parent)
{
    Q_ASSERT(pmodel!=NULL);
    model = pmodel;
}

QRectF AreaGraphicsItem::boundingRect() const
{
    return QRectF(0,0,1000,1000);
}

void AreaGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
//    painter->setPen(QPen(QBrush(Qt::black), 1));
//    painter->setBrush(QBrush(Qt::red));
    QColor areaColor;
    areaColor.setNamedColor("#98FF5C");
    painter->fillPath(model->getPath(),QBrush(areaColor));
}
