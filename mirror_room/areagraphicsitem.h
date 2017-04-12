#ifndef AREAGRAPHICSITEM_H
#define AREAGRAPHICSITEM_H

#include "areamodel.h"
#include <QGraphicsObject>


class AreaGraphicsItem : public QGraphicsObject
{
    Q_OBJECT

public:
    AreaGraphicsItem(AreaModel *pmodel, QGraphicsItem *parent = NULL);


protected:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*);

private:
    AreaModel *model;
};

#endif // AREAGRAPHICSITEM_H
