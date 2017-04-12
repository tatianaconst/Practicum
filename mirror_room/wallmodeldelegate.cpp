#include "wallmodeldelegate.h"

#include <QColorDialog>
#include <QPushButton>
#include <QComboBox>
#include <QDebug>

WallModelDelegate::WallModelDelegate(WallModel *modelInstance, QObject *parent)
    : QItemDelegate(parent), model(modelInstance)
{

}

QWidget *WallModelDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid())
        return NULL;
    if (!index.parent().isValid()) {
        if (index.column() == WallModel::ColorColumn) {
//            QWidget *colored = new QWidget(parent);
//            colored->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            QColor color(model->data(index, Qt::BackgroundColorRole).value<QColor>());
            QColorDialog dlg;
            if (dlg.exec() == QDialog::Accepted) {
                color = dlg.selectedColor();
                qDebug() << "setColor" << color;
            }
//            QPalette pal(colored->palette());
//            pal.setColor(QPalette::Background, color);
//            colored->setPalette(pal);
            model->setData(index, color, Qt::EditRole);
//            setModelData(colored, model, index);
            return NULL;
        }
    }
    else {
        if (index.row() == WallModel::WallTypeRow) {
            QComboBox *combobox = new QComboBox(parent);

            combobox->insertItem(Wall::Straight, Wall::WallTypeToString(Wall::Straight));
            combobox->insertItem(Wall::Convex, Wall::WallTypeToString(Wall::Convex));
            combobox->insertItem(Wall::Arched, Wall::WallTypeToString(Wall::Arched));
            return combobox;
        }
    }
    return QItemDelegate::createEditor(parent, option, index);
}

void WallModelDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (!index.isValid())
        return;
    if (!index.parent().isValid()) {
        if (index.column() == WallModel::ColorColumn) {
            return;
        }
    }
    else {
        if (index.row() == WallModel::WallTypeRow) {
            QComboBox *combobox = qobject_cast<QComboBox*>(editor);
            if (!combobox) {
                qWarning("WallModelDelegate::setEditorData combobox is NULL");
                return;
            }
            qDebug() << "setEditorData" << model->data(index, Qt::DisplayRole).toString();
            combobox->setCurrentText(model->data(index, Qt::DisplayRole).toString());
            return ;
        }
    }
    QItemDelegate::setEditorData(editor, index);
    return;
}

void WallModelDelegate::setModelData(QWidget *editor,
                                     QAbstractItemModel *model,
                                     const QModelIndex &index) const
{
    if (!index.isValid())
        return;
    if (!index.parent().isValid()) {
        if (index.column() == WallModel::ColorColumn) {
//            QPushButton *coloredButton = qobject_cast<QPushButton*>(editor);
//            if (!coloredButton) {
//                qWarning("WallModelDelegate::setEditorData coloredButton is NULL");
//                return;
//            }
//            QColor backgroundColor = editor->palette().color(QPalette::Background);
//            qDebug() << "setBGColor" << backgroundColor;
//            model->setData(index, backgroundColor, Qt::EditRole);
            return;
        }
    }
    else {
        if (index.row() == WallModel::WallTypeRow) {
            QComboBox *combobox = qobject_cast<QComboBox*>(editor);
            if (!combobox) {
                qWarning("WallModelDelegate::setEditorData combobox is NULL");
                return;
            }
            qDebug() << "currentIndex" << combobox->currentIndex();
            model->setData(index, combobox->currentIndex(), Qt::EditRole);
            return;
        }
    }
    QItemDelegate::setModelData(editor, model, index);
    return;
}
