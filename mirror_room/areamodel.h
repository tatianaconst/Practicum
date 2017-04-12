#ifndef AREAMODEL_H
#define AREAMODEL_H

#include <QAbstractItemModel>
#include <QPainterPath>


struct Figure
{
    enum FigureType
    {
        FLine,
        FEllipse
    };

    Figure(int xcv, int ycv, int rxv, int ryv)
        : type(FEllipse), xc(xcv), yc(ycv), rx(rxv), ry(ryv) {}
    Figure(const QLine &line)
        : type(FLine), line(line) {xc=yc=rx=ry=0;}

    static QString FigureTypeToString(const FigureType &type);
    static FigureType FigureTypeFromString(const QString &str);

    FigureType type;
    QLine line;
    // ellipse
    int xc;
    int yc;
    int rx;
    int ry;
};

class AreaModel : public QAbstractItemModel
{
    Q_OBJECT


    enum AttributeTypes
    {
        AttributeName,
        AttributeFirstValue
    };

    enum ColumnTypes
    {
        IndexColumn,
        FigureTypeColumn
    };

    enum RowTypesLine
    {
        LeftRow,
        RightRow,

        RowTypesLineCount
    };

    enum RowTypeEllipse
    {
        CenterRow,
        RxRow,
        RyRow,

        RowTypeEllipseCount
    };
private slots:
    void calcPath();
signals:
    void areaPathChanged();
public:
    explicit AreaModel(QObject *parent = 0);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    void append(const Figure &figure);
    void clear();

    const QList<Figure> &getFigures() const { return figures;}

    QPainterPath getPath();
private:
    QList<Figure> figures;
    QPainterPath path;
};

#endif // AREAMODEL_H
