#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// -- TEST INCLUDE
#include "wallmodel.h"
#include "areamodel.h"
#include "raygraphicsitem.h"

// -- END TEST INCLUDE


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_pushButtonAddLine_clicked();
    void on_pushButtonAddEllipse_clicked();
    void on_pushButtonClear_clicked();

    void onChangeInWalls(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);
    void onChangeInArea(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);

    void on_pushButtonBuild_clicked();

    void on_pushButtonStep_clicked();

    void fillRayParams();

private:
    RayGraphicsItem *ray;
    WallModel *modelWalls;
    AreaModel *modelArea;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
