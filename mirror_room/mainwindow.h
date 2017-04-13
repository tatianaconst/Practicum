#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// -- TEST INCLUDE
#include "wallmodel.h"
#include "areamodel.h"
#include "raygraphicsitem.h"
#include "scene.h"
#include "wizardwelcome.h"

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

    void setModelWalls(const QList<Wall*> &walls);
    void setModelArea(const QList<Figure> &figures);
    RayGraphicsItem *getRayRef() { return ray;}
public slots:
    void finish();
    void setSpinBoxes(qreal x, qreal y, qreal angle);

private slots:

    void on_pushButtonAddLine_clicked();
    void on_pushButtonAddEllipse_clicked();
    void on_pushButtonClear_clicked();

    void on_pushButtonBuild_clicked();

    void on_pushButtonStep_clicked();

    void fillRayParams();

    void on_actionSave_triggered();


    void on_pushButtonRe_clicked();

private:
    Scene *scene;
    RayGraphicsItem *ray;
    WallModel *modelWalls;
    AreaModel *modelArea;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
