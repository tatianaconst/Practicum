#include "raygraphicsitem.h"
#include <QMessageBox>
#include <QtMath>
#include <QPoint>
#include <QDebug>
#include <QVector2D>
#include <QLineF>

//RayGraphicsItem::RayGraphicsItem(QGraphicsItem *parent)
//    :QGraphicsObject(parent), saturation(1)
//{

//}

RayGraphicsItem::RayGraphicsItem(WallModel *pmodel, AreaModel *gmodel, QGraphicsItem *parent)
    :QGraphicsObject(parent), saturation(1)
{
    Q_ASSERT(pmodel!=NULL);
    Q_ASSERT(gmodel!=NULL);
    wModel = pmodel;
    aModel = gmodel;

    connect(wModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(calcInit()));
    connect(wModel, SIGNAL(rowsInserted(QModelIndex,int,int)), this, SLOT(calcInit()));
    connect(wModel, SIGNAL(rowsRemoved(QModelIndex,int,int)), this, SLOT(calcInit()));
}

void RayGraphicsItem::setStartPoint(const QPointF &p)
{
    sPoint = p;
    curPoint = p;
}

void RayGraphicsItem::setStartAngle(const qreal &ang)
{
    sAngle = /*360 - */ang;
    curAngle = sAngle;
}

//void RayGraphicsItem::setWallModel(WallModel *model)
//{
//    wModel = model;

//    connect(wModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(calcInit()));
//    connect(wModel, SIGNAL(rowsInserted(QModelIndex,int,int)), this, SLOT(calcInit()));
//    connect(wModel, SIGNAL(rowsRemoved(QModelIndex,int,int)), this, SLOT(calcInit()));
//}

//void RayGraphicsItem::setAreaModel(AreaModel *model)
//{
//    aModel = model;
//}

QRectF RayGraphicsItem::boundingRect() const
{
    return QRectF(0,0,1000,1000);
}

void RayGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    QColor rayColor;
    rayColor.setNamedColor("#E45001");
    painter->setPen(QPen(QBrush(rayColor), 2));
//    painter->setBrush(QBrush(Qt::red));
    for (int i=0; i < rayLines.size(); ++i)
        painter->drawLine(rayLines[i]);
//    painter->drawPath(path);
}

void RayGraphicsItem::calcInit()
{
    iter = 0;
    curPoint = sPoint;
    curAngle = sAngle;
    rayLines.clear();
    stepLine = QLineF();
    update();
}

extern qreal angle(qreal x1, qreal y1, qreal x2, qreal y2);

#define MY_EPS_557  0.001
bool inRay(const QPointF &p, qreal x1,qreal y1, qreal x2, qreal y2)
{
    return (p.x() <= qMax(x1, x2) + MY_EPS_557
            && p.x() >= qMin(x1, x2) - MY_EPS_557
            && p.y() <= qMax(y1, y2) + MY_EPS_557
            && p.y() >= qMin(y1, y2) - MY_EPS_557);
}
bool inRay(const QPointF &p, const QLineF &line)
{
    return inRay(p, line.p1().x(), line.p1().y(), line.p2().x(), line.p2().y());
}


qreal toFrom0To360(qreal angle)
{
    qreal result = angle;
    while (result >= 360 - MY_EPS_557)
        result -= 360;
    while (result <= 0)
        result += 360;
    return result;
}

bool intersects(const QLineF &line, qreal cx, qreal cy, qreal r, QPointF *point)
{
    qreal x1 = line.p1().x();
    qreal y1 = line.p1().y();
    qreal x2 = line.p2().x();
    qreal y2 = line.p2().y();

    qreal k = (y2-y1)/(x2-x1);
    qreal b = y1 - x1* (y2-y1)/(x2-x1);

    qreal A = k*k + 1;
    qreal B = 2*k*b - 2*k*cy - 2*cx;
    qreal C = b*b - 2*b*cy + cy*cy + cx*cx - r*r;

    if (B*B - 4*A*C<MY_EPS_557)
        return false; // not intersected

    qreal sx1 = (-B + qSqrt(B*B - 4*A*C)) / 2 / A;
    qreal sy1 = k*sx1 + b;

    if (point)
        *point = QPointF(sx1, sy1);
    return inRay(*point, line);
}


qreal toFrom0To2Pi(qreal angle)
{
    qreal result = angle;
    while (result >= 2 * M_PI - MY_EPS_557)
        result -= 2 * M_PI;
    while (result <= 0)
        result += 2 * M_PI;
    return result;
}

QLineF reflected(const QLineF &line, const QLineF &normal)
{
    QVector2D lineVec(line.p2().x()-line.p1().x(), line.p2().y()-line.p1().y());
    QVector2D normalVec(normal.p2().x()-normal.p1().x(), normal.p2().y()-normal.p1().y());
    normalVec.normalize();
    QVector2D reflectVec = lineVec - 2 * QVector2D::dotProduct(lineVec, normalVec) * normalVec;
    return QLineF(line.p2(), QPointF(line.p2().x() + reflectVec.x(),
                                     line.p2().y() + reflectVec.y()));
}

bool RayGraphicsItem::calcStep()
{
    qDebug() << sPoint << curPoint;
    if (++iter >= 10000000000) {
        QMessageBox::information(NULL, QString::fromUtf8("Ошибка построения"), QString::fromUtf8("Превышено количество итераций"));
        return false;
    }
    if (saturation < 0.01) {
        QMessageBox::information(NULL, QString::fromUtf8("Ошибка построения"), QString::fromUtf8("Недостаточная яркость луча"));
        return false;
    }
    stepPath = QPainterPath();
    stepPath.moveTo(curPoint.rx(), curPoint.ry());
    QPointF p(curPoint.rx() + 1000 * qCos(curAngle / 180 * M_PI), curPoint.ry() + 1000 * qSin(-curAngle / 180 * M_PI));
    stepPath.lineTo(p.rx(), p.ry());
    stepLine = QLineF(QPointF(curPoint.rx(), curPoint.ry()), p);


//    path += stepPath;

    if (stepPath.intersects(aModel->getPath())) {

    }
    qreal minDist = 1000;
    QPointF minInterPoint;
    Wall *minInterWall;
    foreach(Wall *wall, wModel->getWalls()) {
        if (wall->getType() == Wall::Straight) {
            QLineF rayLine(curPoint, p);
            QLineF wallLine(wall->getLeft(), wall->getRight());
            QPointF interLinePoint;
            QLineF::IntersectType type = rayLine.intersect(wallLine, &interLinePoint);
            if (type != QLineF::BoundedIntersection)
                continue;
            qDebug() << "Intersection" << interLinePoint;
            QLineF temp(curPoint, interLinePoint);
            qreal dist = temp.length();
            if (dist < minDist) {
                minDist = dist;
                minInterPoint = interLinePoint;
                minInterWall = wall;
            }
        }
        else {
            qreal x1 = curPoint.rx();
            qreal y1 = curPoint.ry();
            qreal x2 = p.rx();
            qreal y2 = p.ry();
            qreal cx = wall->getCenter().rx();
            qreal cy = wall->getCenter().ry();
            qreal r = wall->getRadius();

//            qreal k = (y2-y1)/(x2-x1);
//            qreal b = y1 - x1* (y2-y1)/(x2-x1);

//            qreal A = k*k + 1;
//            qreal B = 2*k*b - 2*k*cy - 2*cx;
//            qreal C = b*b - 2*b*cy + cy*cy + cx*cx - r*r;

//            qreal sx1 = (-B + qSqrt(B*B - 4*A*C)) / 2 / A;
//            qreal sy1 = k*sx1 + b;
//            QPointF sPoint1(sx1, sy1);
            QPointF sPoint1;
            bool intersected;
            if ((intersected=intersects(QLineF(x1,y1,x2,y2),cx,cy,r, &sPoint1)))
                qDebug() << "Intersection" << sPoint1;
            if (intersected && inRay(sPoint1, p.x(), p.y(), curPoint.x(), curPoint.y())) {
                qDebug() << "InRayIntersection" << sPoint1;
                qreal xr1 = sPoint1.x() - wall->getCenter().x(),
                      yr1 = sPoint1.y() - wall->getCenter().y();

                QVector2D rad1(xr1,yr1);
                rad1.normalize();

                qreal interPointAngle = qAcos(rad1.x());

                if (qAsin(rad1.y()) < 0)
                    interPointAngle = 2*M_PI - interPointAngle;

                qreal startAngle = toFrom0To2Pi(wall->getStartAngle()/ 180* M_PI);
                qreal spanAngle = wall->getSpanAngle() * M_PI / 180;
                qreal minAngle = qMin(startAngle, startAngle + spanAngle) - MY_EPS_557;
                qreal maxAngle = qMax(startAngle, startAngle + spanAngle) + MY_EPS_557;

                if ((interPointAngle >= minAngle)
                        && (interPointAngle <= maxAngle)) {
                    QLineF temp(curPoint, sPoint1);
                    qreal dist = temp.length();
                    if (dist < minDist) {
                        minDist = dist;
                        minInterPoint = sPoint1;
                        minInterWall = wall;
                    }
                }
            }
            QPointF sPoint2;
            if ((intersected=intersects(QLineF(x1,y1,x2,y2),cx,cy,r, &sPoint2)))
                qDebug() << "Intersection" << sPoint2;
            if (intersected && inRay(sPoint2, p.x(), p.y(), curPoint.x(), curPoint.y())) {
                qDebug() << "InRayIntersection" << sPoint2;
                qreal xr2 = sPoint2.x() - wall->getCenter().x(),
                      yr2 = sPoint2.y() - wall->getCenter().y();

                QVector2D rad2(xr2,yr2);
                rad2.normalize();

                qreal interPointAngle = qAcos(rad2.x());

                if (qAsin(rad2.y()) < 0)
                    interPointAngle = 2*M_PI - interPointAngle;

                qreal startAngle = toFrom0To2Pi(wall->getStartAngle()/ 180* M_PI);
                qreal spanAngle = wall->getSpanAngle() * M_PI / 180;
                qreal minAngle = qMin(startAngle, startAngle + spanAngle) - MY_EPS_557;
                qreal maxAngle = qMax(startAngle, startAngle + spanAngle) + MY_EPS_557;

                if ((interPointAngle >= minAngle)
                        && (interPointAngle <= maxAngle)) {
                    QLineF temp(curPoint, sPoint2);
                    qreal dist = temp.length();
                    if (dist < minDist) {
                        minDist = dist;
                        minInterPoint = sPoint2;
                        minInterWall = wall;
                    }
                }
            }
        }
        qDebug() << "MinPoint" << minInterPoint;







//        QPainterPath wallPath;
//        wallPath.moveTo(wall->getLeft());
//        wallPath.lineTo(wall->getRight());


//        QPainterPath inter = stepPath.intersected(wallPath);
//        if (inter.elementCount() == 0) continue;
//        if (inter.elementCount() > 1) {
//            qDebug() << iter << " : " << curPoint << " : " << curAngle;
//            return false;
//        }
//        QPointF interPoint(inter.elementAt(0).x, inter.elementAt(0).y);
//        QLineF temp(curPoint, interPoint);
//        qreal dist = temp.length();
//        if (dist < minDist) {
//            minDist = dist;
//            minInterPoint = interPoint;
//            minInterWall = wall;
//        }
//        if (minInterWall->getType() == Wall::Straight) {
//            QPointF right = minInterWall->getRight();
//            QPointF left = minInterWall->getLeft();
//            QVector2D wallSec(right.x() - left.x(), right.y() - left.y());
//            qreal x1 = -wallSec.y();
//            qreal y1 = +wallSec.x();
//            QVector2D norm(x1, y1);
//            qreal wallHalfLength = wallSec.length() / 2;
//            norm.normalize();

//            qreal incAngle = angle((qreal)norm.x(), norm.y(), interPoint.x()-curPoint.x(), interPoint.y() - curPoint.y());
//            qreal x=norm.x()*qCos(incAngle)-norm.y()*qSin(incAngle);
//            qreal y=norm.y()*qCos(incAngle)+norm.x()*qSin(incAngle);
//            stepPath = QPainterPath();
//            stepPath.moveTo(curPoint);
//            curPoint = QPointF(x, y);
//            curAngle = incAngle *2;
//            stepPath.lineTo(curPoint);
//            fulPath += stepPath;
//        }
        }
        if (minDist == 1000) {
            QMessageBox::information(NULL, QString::fromUtf8("Ошибка построения"), QString::fromUtf8("Нет пересечений"));
            rayLines.append(stepLine);
            update();
            return false;
        }
        stepLine = QLineF(curPoint, minInterPoint);

        foreach (const Figure &figure, aModel->getFigures()) {
            if (figure.type == Figure::FLine) {
                QPointF point;
                if (stepLine.intersect(figure.line, &point)
                        && inRay(point, stepLine)
                        && inRay(point, figure.line)) {
                    qDebug() << "line" << stepLine << figure.line;

                    QMessageBox::information(NULL, QString::fromUtf8("Путь построен"), QString::fromUtf8("Пересечение с целевой областью"));
                    rayLines.append(stepLine);
                    update();
                    return false;
                }
            }
            else {
                QPointF point;
                if (intersects(stepLine, figure.xc, figure.yc, figure.rx, &point)) {
                    qDebug() << "ellipse" << stepLine << figure.xc << figure.yc << figure.rx;

                    QMessageBox::information(NULL, QString::fromUtf8("Путь построен"), QString::fromUtf8("Пересечение с целевой областью"));
                    rayLines.append(stepLine);
                    update();
                    return false;
                }
            }
        }

        if (minInterWall->getType() == Wall::Straight) {
            QLineF wallLine(minInterWall->getLeft(), minInterWall->getRight());
            QLineF normal1 = wallLine.normalVector();
            QLineF normal2(normal1.p2(), normal1.p1());
            QLineF normal;
            QLineF incidBeam(curPoint, minInterPoint);
            if (incidBeam.angleTo(normal1) > incidBeam.angleTo(normal2))
                normal = normal1;
            else
                normal = normal2;
            //qreal incidAngle = normal.angleTo(incidBeam);
             qreal incidAngle = incidBeam.angle(normal);
            qDebug() << "incidAngle" << incidAngle;
            //incidAngle = 360 - incidAngle;
            qreal angle1 = incidBeam.angle();
            qDebug() << "angle1" << angle1;
            qDebug() << "incidBeam" << incidBeam;
            incidBeam = reflected(incidBeam, normal);
//            incidBeam.setAngle(toFrom0To360(angle1 + 2*incidAngle));
            qDebug() << incidBeam;
            stepPath = QPainterPath();
            stepPath.moveTo(curPoint);
            stepPath.lineTo(incidBeam.p2());
            //stepPath.lineTo(incidBeam.p2());
            curAngle = incidBeam.angle();
//            curPoint = incidBeam.p1();
            incidBeam.setLength(0.2);
            curPoint = incidBeam.p2();
            qDebug() << curPoint;
            sPoint = curPoint;
            sAngle = curAngle;
        }
        else {
            QLineF radLine(minInterPoint, minInterWall->getCenter());
            QLineF incidBeam(minInterPoint, curPoint);
            qreal incidAngle = radLine.angleTo(incidBeam);
            qreal angle1 = incidBeam.angle();
            incidBeam.setAngle(angle1 + 2*incidAngle);
            stepPath = QPainterPath();
            stepPath.moveTo(curPoint);
            stepPath.lineTo(incidBeam.p1());
            //stepPath.lineTo(incidBeam.p2());
            curAngle = incidBeam.angle();
            curPoint = incidBeam.p1();
            incidBeam.setLength(0.2);
            curPoint = incidBeam.p2();
            sPoint = curPoint;
            sAngle = curAngle;
        }
    rayLines.append(stepLine);
//    path += stepPath;
    qDebug() << "rayLines" << rayLines;
    update();
    return true;
}

void RayGraphicsItem::calcBuild()
{
//    calcInit();
//    fulPath = QPainterPath();
    while(calcStep()) {
//        fulPath += stepPath;
    }
//    path = fulPath;
//    update();
}

qreal RayGraphicsItem::getSAngle() const
{
    return sAngle;
}

QPointF RayGraphicsItem::getSPoint() const
{
    return sPoint;
}

QPainterPath RayGraphicsItem::shape() const
{
    return stepPath;
}


QDataStream &operator<<(QDataStream &ds, const RayGraphicsItem &r)
{
    ds << r.rayLines;
    ds << r.stepLine;
    ds << r.sAngle;
    ds << r.curAngle;
    ds << r.sPoint;
    ds << r.curPoint;
    ds << r.iter;
    ds << r.saturation;
    ds << r.fulPath;
    ds << r.stepPath;

    return ds;
}

QDataStream &operator>>(QDataStream &ds, RayGraphicsItem &r)
{
    ds >> r.rayLines;
    ds >> r.stepLine;
    ds >> r.sAngle;
    ds >> r.curAngle;
    ds >> r.sPoint;
    ds >> r.curPoint;
    ds >> r.iter;
    ds >> r.saturation;
    ds >> r.fulPath;
    ds >> r.stepPath;

    return ds;
}
