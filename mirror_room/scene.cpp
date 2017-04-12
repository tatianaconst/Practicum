#include "scene.h"
#include "areagraphicsitem.h"

#include <QDebug>

Scene::Scene(QObject *parent)
{
    setSceneRect(0, 0, 1000, 1000);
}

//void Scene::clear()
//{

//}

void Scene::setWalls(QList<Wall *> &walls)
{
    foreach (Wall *pWall, walls)
        addItem(new WallGraphicsItem(pWall));
}

void Scene::setArea(AreaModel *model)
{
    addItem(new AreaGraphicsItem(model));
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "pressed at" << event->scenePos();
    QGraphicsScene::mousePressEvent(event);
}
