#ifndef RAYGRAPHICSITEM_H
#define RAYGRAPHICSITEM_H

#include <QGraphicsObject>
#include <QPainter>
#include <QPainterPath>
#include "wallmodel.h"
#include "areagraphicsitem.h"

class RayGraphicsItem : public QGraphicsObject
{
    Q_OBJECT

public:
    RayGraphicsItem(WallModel *pmodel, AreaModel *gmodel, QGraphicsItem *parent = NULL);
    void setStartPoint(QPointF const &p);
    void setStartAngle(qreal const &ang);
protected:
    virtual QRectF boundingRect() const;
    virtual QPainterPath shape() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*);
public slots:
    void calcInit();
    bool calcStep();
    void calcBuild();
private:
    QPainterPath path;
    qreal sAngle, curAngle;
    QPointF sPoint, curPoint;
    int iter;
    qreal saturation;
    WallModel *wModel;
    AreaModel *aModel;
    QPainterPath fulPath, stepPath;
};

#endif // RAYGRAPHICSITEM_H
