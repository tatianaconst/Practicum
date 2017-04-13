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
public slots:
    void setCenter(const QPoint &value);
    void setRight(const QPoint &value);
    void setLeft(const QPoint &value);
public:
//    Wall(const Wall &W);
    Wall();
    Wall(const QString &titleVal,
         const QPoint &leftVal,
         const QPoint &rightVal,
         const WallType &typeVal = Straight,
         const qreal &radiusVal = 0,
         const qreal &coeffVal = 0,
         const QColor &colorVal = Qt::gray
         );

    void connectLeft(Wall *leftNeighbor);
    void connectRight(Wall *rightNeighbor);
    QPoint getCenter() const;

    WallType getType() const;
    void setType(const WallType &value);

    QString getTitle() const;
    void setTitle(const QString &value);

    QPoint getRight() const;

    QPoint getLeft() const;

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
    void leftChangedToNeighbor(const QPoint &p);
    void rightChangedToNeighbor(const QPoint &p);

    void titleChanged();
    void colorChanged();
    void leftChanged();
    void rightChanged();
    void radiusChanged();
    void coefChanged();
    void typeChanged();

    void changed();

private:
    friend QDataStream &operator<<(QDataStream &ds, const Wall &w);
    friend QDataStream &operator>>(QDataStream &ds, Wall &w);
};

QDataStream &operator<<(QDataStream &ds, const Wall &w);
QDataStream &operator>>(QDataStream &ds, Wall &w);

#endif // WALL_H
