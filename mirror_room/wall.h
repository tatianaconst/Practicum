#ifndef WALL_H
#define WALL_H

#include <QString>
#include <QColor>
#include <QPoint>
#include <QObject>



class Wall: public QObject
{
    Q_OBJECT

    QString title;
    QColor color;

    QPoint left;
    QPoint right;
    qreal radius;
    qreal coeff;
    QPoint center;
    qreal startAngle, spanAngle;
public:
    enum WallType
    {
        Straight = 0,   // Прямая
        Convex = 1,     // Выпуклая
        Arched = 2      // Вогнутая
    };
    static QString WallTypeToString(const Wall::WallType &type);
    static Wall::WallType WallTypeFromString(const QString &typeStr);
private:

    WallType type;

    void init();
public:
//    Wall(const Wall &W);
    Wall(const QString &titleVal,
         const QPoint &leftVal,
         const QPoint &rightVal,
         const WallType &typeVal = Straight,
         const qreal &radiusVal = 0,
         const qreal &coeffVal = 0,
         const QColor &colorVal = Qt::gray
         );

    QPoint getCenter() const;
    void setCenter(const QPoint &value);

    WallType getType() const;
    void setType(const WallType &value);

    QString getTitle() const;
    void setTitle(const QString &value);

    QPoint getRight() const;
    void setRight(const QPoint &value);

    QPoint getLeft() const;
    void setLeft(const QPoint &value);

    qreal getRadius() const;
    void setRadius(const qreal &value);

    qreal getCoeff() const;
    void setCoeff(const qreal &value);


    QColor getColor() const;
    void setColor(const QColor &value);

    QString typeString() const;
    void setTypeFromString(const QString &typeStr);

    qreal getStartAngle() const;

    qreal getSpanAngle() const;
    void setSpanAngle(const qreal &value);

    void setStartAngle(const qreal &value);

signals:
    void titleChanged();
    void colorChanged();
    void leftChanged();
    void rightChanged();
    void radiusChanged();
    void coefChanged();
    void typeChanged();

    void changed();
};


#endif // WALL_H
