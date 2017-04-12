#ifndef WALLMODELDELEGATE_H
#define WALLMODELDELEGATE_H

#include "wallmodel.h"
#include <QItemDelegate>

class WallModelDelegate : public QItemDelegate
{
    WallModel *model;
public:
    WallModelDelegate(WallModel *modelInstance, QObject *parent = Q_NULLPTR);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
};

#endif // WALLMODELDELEGATE_H
