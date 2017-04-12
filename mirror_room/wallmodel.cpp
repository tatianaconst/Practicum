#include "wallmodel.h"
#include "wallmodeldelegate.h"

#include <QVector>
#include <QDebug>

WallModel::WallModel(const QList<Wall*> &initWalls, QObject *parent)
    : QAbstractItemModel(parent)
{
    if (initWalls.size()) {
        beginInsertRows(QModelIndex(),0, initWalls.size() - 1);
        walls = initWalls;
        endInsertRows();
    }
}

QVariant WallModel::headerData(int section, Qt::Orientation /*orientation*/, int /*role*/) const
{
    // FIXME: Implement me!
    switch (section)
    {
    case 0:
        return QString::fromUtf8("Цвет/Аттрибут");
    case 1:
        return QString::fromUtf8("Стена/Значение");
    }
    return QVariant();
}


QModelIndex WallModel::index(int row, int column, const QModelIndex &parent) const
{
//    if (!hasIndex(row, column, parent))
//        return QModelIndex();

    if (!parent.isValid()) {
//        qDebug() << "created first" << row << column;
        return createIndex(row, column, row * 2);
    }
    else {
        return createIndex(row, column, parent.row() * 2 + 1);
    }
}

QModelIndex WallModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    if (index.internalId() % 2 == 0) {
        return QModelIndex();
    }

    return WallModel::index(index.internalId()/2, 0, QModelIndex());
}

int WallModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return walls.size();

    if (parent.parent().isValid())
        return 0;
    return AttributeRowCnt;
}

int WallModel::columnCount(const QModelIndex &parent) const
{
//    if (!parent.isValid())
//        return 1;

//    if (parent.isValid() && !parent.parent().isValid()) {
//        return 3;
//    }
    return 3;
}

QVariant WallModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (!index.parent().isValid()) {
        if (role == Qt::BackgroundColorRole && index.column() == ColorColumn) {
            return walls.at(index.row())->getColor();
        }
        if (role == Qt::DisplayRole) {
            switch(index.column()) {
            case TitleColumn:
                return walls.at(index.row())->getTitle();
            case ColorColumn:
                return QVariant();
            default:
//                qWarning("WallModel::data");
                return QVariant();
            }
        }
    }
    else {
        if (role == Qt::DisplayRole) {
            switch(index.row()) {
            case LeftRow:
                switch(index.column()) {
                case AttributeName:
                    return QString::fromUtf8("Левая т.");
                case AttributeValue:
                    return walls.at(index.parent().row())->getLeft().x();
                case AttributeValue + 1:
                    return walls.at(index.parent().row())->getLeft().y();
                default:
                    qWarning("WARNING: WallModel::data");
                    return QVariant();
                }

            case RightRow:
                switch(index.column()) {
                case AttributeName:
                    return QString::fromUtf8("Правая т.");
                case AttributeValue:
                    return walls.at(index.parent().row())->getRight().x();
                case AttributeValue + 1:
                    return walls.at(index.parent().row())->getRight().y();
                default:
                    qWarning("WARNING: WallModel::data");
                    return QVariant();
                }
            case WallTypeRow:
                switch(index.column()) {
                case AttributeName:
                    return QString::fromUtf8("Тип стены");
                case AttributeValue:
                    return walls.at(index.parent().row())->typeString();
                default:
//                    qWarning("WARNING: WallModel::data");
                    return QVariant();
                }

            case RadiusRow:
                switch(index.column()) {
                case AttributeName:
                    return QString::fromUtf8("Радиус");
                case AttributeValue:
                    return walls.at(index.parent().row())->getRadius();
                default:
//                    qWarning("WARNING: WallModel::data");
                    return QVariant();
                }

            case CoeffRow:
                switch(index.column()) {
                case AttributeName:
                    return QString::fromUtf8("Коэффициент");
                case AttributeValue:
                    return walls.at(index.parent().row())->getCoeff();
                default:
//                    qWarning("WARNING: WallModel::data");
                    return QVariant();
                }

            default:
//                qWarning("WallModel::data second");
                return QVariant();
            }
        }
    }
    // FIXME: Implement me!
    return QVariant();
}

bool WallModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        if (role == Qt::EditRole) {
            if (!index.parent().isValid()) {
                switch(index.column()) {
                case ColorColumn:
                    walls[index.row()]->setColor(value.value<QColor>());
                    break;
                default:
                    return false;
                }
            }
            else {
                switch(index.row()) {
                case LeftRow:
                    switch(index.column()) {
                    case AttributeValue:
                        walls[index.parent().row()]->setLeft(QPoint(value.toInt(), walls[index.parent().row()]->getLeft().y()));
                        break;
                    case AttributeValue + 1:
                        walls[index.parent().row()]->setLeft(QPoint(walls[index.parent().row()]->getLeft().x(), value.toInt()));
                        break;
                    }
                    break;
                case RightRow:
                    switch(index.column()) {
                    case AttributeValue:
                        walls[index.parent().row()]->setRight(QPoint(value.toInt(), walls[index.parent().row()]->getRight().y()));
                        break;
                    case AttributeValue + 1:
                        walls[index.parent().row()]->setRight(QPoint(walls[index.parent().row()]->getRight().x(), value.toInt()));
                        break;
                    }
                    break;
                case WallTypeRow:
                    switch(index.column()) {
                    case AttributeValue:
                        qDebug() << "model set type" << value.toInt();
                        Wall::WallType newType = static_cast<Wall::WallType>(value.toInt());
                        walls[index.parent().row()]->setType(newType);
                        if (newType == Wall::Straight)
                            walls[index.parent().row()]->setRadius(0);
                        break;
                    }
                    break;
                case RadiusRow:
                    switch(index.column()) {
                    case AttributeValue:
                        walls[index.parent().row()]->setRadius(value.toDouble());
                        break;
                    }
                    break;
                case CoeffRow:
                    switch(index.column()) {
                    case AttributeValue:
                        walls[index.parent().row()]->setCoeff(value.toDouble());
                        break;
                    }
                    break;
                default:
                    qWarning("WallModel::setData");
                    return false;
                }
            }
        }

        emit dataChanged(index, index, QVector<int>() << (int)Qt::EditRole);
        return true;
    }
    return false;
}

Qt::ItemFlags WallModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    if (index.parent().isValid()) {
        if (walls[index.parent().row()]->getType() == Wall::Straight) {
            if (index.row() == RadiusRow)
                return Qt::NoItemFlags;
        }
        if (index.column() == AttributeName)
            return Qt::ItemIsEnabled;
        if (index.column() == 2 && (
                    index.row() != LeftRow
                    && index.row() != RightRow))
            return Qt::ItemIsEnabled;
    }
    else {
        if (index.column() == TitleColumn)
            return Qt::ItemIsEnabled;
    }

    return Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

QList<Wall *> WallModel::getWalls()
{
    return walls;
}
