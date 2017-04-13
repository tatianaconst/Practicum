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
//    RayGraphicsItem(QGraphicsItem *parent = NULL);
    RayGraphicsItem(WallModel *pmodel, AreaModel *gmodel, QGraphicsItem *parent = NULL);
    void setStartPoint(QPointF const &p);
    void setStartAngle(qreal const &ang);

//    void setWallModel(WallModel *model);
//    void setAreaModel(AreaModel *model);
    QPointF getSPoint() const;

    qreal getSAngle() const;

protected:
    virtual QRectF boundingRect() const;
    virtual QPainterPath shape() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*);
public slots:
    void calcInit();
    bool calcStep();
    void calcBuild();
private:
    QList<QLineF> rayLines;
    QLineF stepLine;
    qreal sAngle, curAngle;
    QPointF sPoint, curPoint;
    int iter;
    qreal saturation;
    WallModel *wModel;
    AreaModel *aModel;
    QPainterPath fulPath, stepPath;

    friend QDataStream &operator<<(QDataStream &ds, const RayGraphicsItem &m);
    friend QDataStream &operator>>(QDataStream &ds, RayGraphicsItem &m);
};

QDataStream &operator<<(QDataStream &ds, const RayGraphicsItem &m);
QDataStream &operator>>(QDataStream &ds, RayGraphicsItem &m);

#endif // RAYGRAPHICSITEM_H
