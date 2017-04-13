#include "areamodel.h"

#include <QDataStream>
#include <QDebug>

AreaModel::AreaModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    connect(this, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(calcPath()));
    connect(this, SIGNAL(rowsInserted(QModelIndex,int,int)), this, SLOT(calcPath()));
    connect(this, SIGNAL(rowsRemoved(QModelIndex,int,int)), this, SLOT(calcPath()));
}

QVariant AreaModel::headerData(int section, Qt::Orientation /*orientation*/, int /*role*/) const
{
    switch(section) {
    case 0:
        return QString::fromUtf8("ID/Аттрибут");
    case 1:
        return QString::fromUtf8("Тип/Значение");
    case 2:
        return QString::fromUtf8("Значение");
    }

    return QVariant();
}

QModelIndex AreaModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return createIndex(row, column, row * 2);
    }
    else {
        return createIndex(row, column, parent.row() * 2 + 1);
    }
}

QModelIndex AreaModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    if (index.internalId() % 2 == 0) {
        return QModelIndex();
    }

    return AreaModel::index(index.internalId()/2, 0, QModelIndex());
}

int AreaModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return figures.size();

    if (parent.parent().isValid())
        return 0;

    if (figures.at(parent.row()).type == Figure::FLine)
        return 2;
    else
        return 3;
}

int AreaModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 3;
//    if (!parent.isValid())
//        return 0;

    // FIXME: Implement me!
}

QVariant AreaModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        if (!index.parent().isValid()) {
            switch (index.column()) {
            case IndexColumn:
                return index.row();
            case FigureTypeColumn:
                return Figure::FigureTypeToString(figures.at(index.row()).type);
            default:
                return QVariant();
            }
        }
        else {
            const Figure &figure = figures.at(index.parent().row());
            if (figure.type == Figure::FLine) {
                switch (index.row()) {
                case LeftRow:
                    switch (index.column()) {
                    case AttributeName:
                        return QString::fromUtf8("Левая т.");
                    case AttributeFirstValue:
                        return figure.line.x1();
                    case AttributeFirstValue+1:
                        return figure.line.y1();
                    }
                    break;
                case RightRow:
                    switch (index.column()) {
                    case AttributeName:
                        return QString::fromUtf8("Правая т.");
                    case AttributeFirstValue:
                        return figure.line.x2();
                    case AttributeFirstValue+1:
                        return figure.line.y2();
                    }
                    break;
                default:
                    qWarning("AreaModel::data first");
                    return QVariant();
                }
            }
            else if (figure.type == Figure::FEllipse) {
                switch (index.row()) {
                case CenterRow:
                    switch (index.column()) {
                    case AttributeName:
                        return QString::fromUtf8("Центр");
                    case AttributeFirstValue:
                        return figure.xc;
                    case AttributeFirstValue+1:
                        return figure.yc;
                    }
                    break;
                case RxRow:
                    switch (index.column()) {
                    case AttributeName:
                        return QString::fromUtf8("Rx");
                    case AttributeFirstValue:
                        return figure.rx;
                    }
                    break;
                case RyRow:
                    switch (index.column()) {
                    case AttributeName:
                        return QString::fromUtf8("Ry");
                    case AttributeFirstValue:
                        return figure.ry;
                    }
                    break;
                default:
                    qWarning("AreaModel::data second");
                    return QVariant();
                }
            }
        }
    }
    return QVariant();
}

bool AreaModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        if (!index.parent().isValid()) {
            return false;
        }
        else {
            Figure &figure = figures[index.parent().row()];
            if (figure.type == Figure::FLine) {
                switch (index.row()) {
                case LeftRow:
                    switch (index.column()) {
                    case AttributeName:
                        return false;
                    case AttributeFirstValue:
                        figure.line.setP1(QPoint(value.toInt(), figure.line.y1()));
                    case AttributeFirstValue+1:
                        figure.line.setP1(QPoint(figure.line.x1(), value.toInt()));
                    }
                    break;
                case RightRow:
                    switch (index.column()) {
                    case AttributeName:
                        return false;
                    case AttributeFirstValue:
                        figure.line.setP2(QPoint(value.toInt(), figure.line.y2()));
                    case AttributeFirstValue+1:
                        figure.line.setP2(QPoint(figure.line.x2(), value.toInt()));
                    }
                    break;
                }
            }
            else if (figure.type == Figure::FEllipse) {
                switch (index.row()) {
                case CenterRow:
                    switch (index.column()) {
                    case AttributeName:
                        return false;
                    case AttributeFirstValue:
                        figure.xc = value.toInt();
                    case AttributeFirstValue+1:
                        figure.yc = value.toInt();
                    }
                    break;
                case RxRow:
                    switch (index.column()) {
                    case AttributeName:
                        return false;
                    case AttributeFirstValue:
                        figure.rx = value.toInt();
                    }
                    break;
                case RyRow:
                    switch (index.column()) {
                    case AttributeName:
                        return false;
                    case AttributeFirstValue:
                        figure.ry = value.toInt();
                    }
                    break;
                }
            }
        }
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags AreaModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    if (!index.parent().isValid()) {
        return Qt::ItemIsEnabled;
    }
    else {
        const Figure &figure = figures.at(index.parent().row());
        if (figure.type == Figure::FLine) {
            switch (index.row()) {
            case LeftRow:
                switch (index.column()) {
                case AttributeName:
                    return Qt::ItemIsEnabled;
                }
                break;
            case RightRow:
                switch (index.column()) {
                case AttributeName:
                    return Qt::ItemIsEnabled;
                }
                break;
            default:
                break;
            }
        }
        else if (figure.type == Figure::FEllipse) {
            switch (index.row()) {
            case CenterRow:
                switch (index.column()) {
                case AttributeName:
                    return Qt::ItemIsEnabled;
                }
                break;
            case RxRow:
                switch (index.column()) {
                case AttributeName:
                    return Qt::ItemIsEnabled;
                case AttributeFirstValue + 1:
                    return Qt::ItemIsEnabled;
                }
                break;
            case RyRow:
                switch (index.column()) {
                case AttributeName:
                    return Qt::ItemIsEnabled;
                case AttributeFirstValue + 1:
                    return Qt::ItemIsEnabled;
                }
                break;
            default:
                break;
            }
        }
    }

    return Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

void AreaModel::append(const Figure &figure)
{
    beginInsertRows(QModelIndex(), figures.size(), figures.size());
    figures.append(figure);
    endInsertRows();
}

void AreaModel::clear()
{
    if (figures.isEmpty())
        return;

    beginRemoveRows(QModelIndex(),0,figures.size());
    figures.clear();
    endRemoveRows();
}

QPainterPath AreaModel::getPath()
{
    return path;
}

QString Figure::FigureTypeToString(const Figure::FigureType &type)
{
    switch (type) {
    case FLine:
        return QString::fromUtf8("Отрезок");
    case FEllipse:
        return QString::fromUtf8("Эллипс");
    default:
        return QString();
    }
}

Figure::FigureType Figure::FigureTypeFromString(const QString &str)
{
    if (str == QString::fromUtf8("Эллипс"))
        return FEllipse;
    return FLine;
}

void AreaModel::calcPath()
{
    qDebug() << "calcPathAreaModel";
    QPainterPath result;
    bool firstLine = true;
    foreach (const Figure &figure, figures) {

        if (figure.type == Figure::FEllipse) {
            firstLine = true;
            result.addEllipse(QPointF(figure.xc, figure.yc), figure.rx, figure.ry);
        }
        else {
            if(firstLine)
                result.moveTo(figure.line.p1());
            else
                result.lineTo(figure.line.p1());
            firstLine = false;
            result.lineTo(figure.line.p2());
        }
    }
    result.closeSubpath();
    path = result;
    path.setFillRule(Qt::WindingFill);
    qDebug() << result;
    emit areaPathChanged();
}

QDataStream &operator<<(QDataStream &ds, const AreaModel &m)
{
    ds << m.figures;

    return ds;
}

QDataStream &operator>>(QDataStream &ds, AreaModel &m)
{
    ds >> m.figures;
    m.calcPath();

    return ds;
}

QDataStream &operator<<(QDataStream &ds, const Figure &f)
{
    ds << f.type;
    ds << f.line;
    ds << f.xc;
    ds << f.yc;
    ds << f.rx;
    ds << f.ry;

    return ds;
}

QDataStream &operator>>(QDataStream &ds, Figure &f)
{
    int ftype;
    ds >> ftype;
    f.type = static_cast<Figure::FigureType>(ftype);
    ds >> f.line;
    ds >> f.xc;
    ds >> f.yc;
    ds >> f.rx;
    ds >> f.ry;

    return ds;
}
