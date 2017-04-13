#ifndef SCENE_H
#define SCENE_H

#include "wall.h"
#include "wallgraphicsitem.h"
#include "areamodel.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = 0);

//    void clear();
    void setWalls(const QList<Wall *> &walls);
    void setArea(AreaModel *model);
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:

};

#endif // SCENE_H
