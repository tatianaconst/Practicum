#include "wall.h"

//Wall::Wall()
//    : radius(0)
//{
//    init();
//}

QPoint Wall::getRight() const
{
    return right;
}

void Wall::setRight(const QPoint &value)
{
    if (right == value)
        return;

    right = value;
    emit rightChanged();
}

QPoint Wall::getLeft() const
{
    return left;
}

void Wall::setLeft(const QPoint &value)
{
    if (left == value)
        return;

    left = value;
    emit leftChanged();
}

qreal Wall::getRadius() const
{
    return radius;
}

void Wall::setRadius(const qreal &value)
{
    if (radius == value)
        return;

    radius = value;
    emit radiusChanged();
}

qreal Wall::getCoeff() const
{
    return coeff;
}

void Wall::setCoeff(const qreal &value)
{
    if (coeff == value)
        return;

    coeff = value;
    emit coefChanged();
}

Wall::WallType Wall::getType() const
{
    return type;
}

void Wall::setType(const Wall::WallType &value)
{
    if (type == value)
        return;

    type = value;
    emit typeChanged();
}


QString Wall::typeString() const
{
    return WallTypeToString(type);
}

void Wall::setTypeFromString(const QString &typeStr)
{
    type = WallTypeFromString(typeStr);
    emit typeChanged();
}

void Wall::init()
{
    connect(this, SIGNAL(titleChanged()), this, SIGNAL(changed()));
    connect(this, SIGNAL(colorChanged()), this, SIGNAL(changed()));
    connect(this, SIGNAL(leftChanged()), this, SIGNAL(changed()));
    connect(this, SIGNAL(rightChanged()), this, SIGNAL(changed()));
    connect(this, SIGNAL(radiusChanged()), this, SIGNAL(changed()));
    connect(this, SIGNAL(coefChanged()), this, SIGNAL(changed()));
    connect(this, SIGNAL(typeChanged()), this, SIGNAL(changed()));
}


Wall::Wall(const QString &titleVal,
           const QPoint &leftVal,
           const QPoint &rightVal,
           const WallType &typeVal,
           const qreal &radiusVal,
           const qreal &coeffVal,
           const QColor &colorVal)
{
    init();
    title = titleVal;
    left = leftVal;
    right = rightVal;
    type = typeVal;
    radius = radiusVal;
    coeff = coeffVal;
    color = colorVal;
}

QPoint Wall::getCenter() const
{
    return center;
}

void Wall::setCenter(const QPoint &value)
{
    center = value;
}

QString Wall::getTitle() const
{
    return title;
}

void Wall::setTitle(const QString &value)
{
    if (title == value)
        return;
    title = value;

    emit titleChanged();
}

QColor Wall::getColor() const
{
    return color;
}

void Wall::setColor(const QColor &value)
{
    if (color == value)
        return;
    color = value;

//    emit colorChanged();
}

Wall::WallType Wall::WallTypeFromString(const QString &typeStr)
{
    Wall::WallType type = Straight;
    if (typeStr == QString::fromUtf8("Выпуклая")) {
        type = Convex;
    }
    else if (typeStr == QString::fromUtf8("Выгнутая")) {
        type = Arched;
    }
    return type;
}

qreal Wall::getStartAngle() const
{
    return startAngle;
}

qreal Wall::getSpanAngle() const
{
    return spanAngle;
}

void Wall::setSpanAngle(const qreal &value)
{
    spanAngle = value;
}

void Wall::setStartAngle(const qreal &value)
{
    startAngle = value;
}

QString Wall::WallTypeToString(const Wall::WallType &type)
{
    switch(type) {
    case Straight:
        return QString::fromUtf8("Прямая");
    case Convex:
        return QString::fromUtf8("Выпуклая");
    case Arched:
        return QString::fromUtf8("Выгнутая");
    }
    qWarning("Wall::WallTypeToString");
    return QString();
}
