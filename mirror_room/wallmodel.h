#ifndef WALLMODEL_H
#define WALLMODEL_H

#include "wall.h"

#include <QAbstractItemModel>


class WallModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum AttributeParentRow
    {
        ColorColumn = 0,
        TitleColumn = 1,

        AttributeParentRowCnt
    };

    enum AttributeRow
    {
        LeftRow = 0,
        RightRow,
        CoeffRow,
        WallTypeRow,
        RadiusRow,

        AttributeRowCnt
    };

    enum AttributeColumn
    {
        AttributeName = 0,
        AttributeValue
    };


    WallModel(const QList<Wall*> &initWalls, QObject *parent = 0);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole);

    Qt::ItemFlags flags(const QModelIndex& index) const;

    QList<Wall *> getWalls();
    void clear();
private:
    void setWalls(const QList<Wall*> &initWalls);
    QList<Wall*> walls;

    friend QDataStream &operator<<(QDataStream &ds, const WallModel &m);
    friend QDataStream &operator>>(QDataStream &ds, WallModel &m);
};

QDataStream &operator<<(QDataStream &ds, const WallModel &m);
QDataStream &operator>>(QDataStream &ds, WallModel &m);

#endif // WALLMODEL_H
