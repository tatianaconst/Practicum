#ifndef WALLGRAPHICSITEM_H
#define WALLGRAPHICSITEM_H

#include <QGraphicsObject>
#include "wall.h"

class WallGraphicsItem : public QGraphicsObject
{
    Q_OBJECT

    Wall *wall;
    QPainterPath path;
public:
    WallGraphicsItem(Wall *pWall, QGraphicsItem *parent = NULL);

public slots:
    void calcPath();
    void updateItem();

protected:
    virtual QRectF boundingRect() const;
    virtual QPainterPath shape() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*);

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
};

#endif // WALLGRAPHICSITEM_H
