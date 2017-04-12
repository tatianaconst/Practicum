#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "wallmodeldelegate.h"
#include "scene.h"
#include "raygraphicsitem.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    modelWalls(NULL),
    modelArea(NULL),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
// init walls
    QList<Wall*> walls;
//    walls.append(new Wall("wall1", QPoint(100,100), QPoint(100,200), Wall::Convex, 200));
//    walls.append(new Wall("wall2", QPoint(200,100), QPoint(250,300)));
//    walls.append(new Wall("wall3", QPoint(0,1), QPoint(2,0)));


    walls.append(new Wall("wall1", QPoint(100,100), QPoint(500,100)));
    walls.append(new Wall("wall1", QPoint(500,100), QPoint(500,500)));
    walls.append(new Wall("wall1", QPoint(500,500), QPoint(100,500)));
    walls.append(new Wall("wall1", QPoint(100,500), QPoint(100,100)));


//
    modelWalls = new WallModel(walls, this);
    ui->treeViewWalls->setModel(modelWalls);
//    ui->treeView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->treeViewWalls->setItemDelegate(new WallModelDelegate(modelWalls, ui->treeViewWalls));
    ui->treeViewWalls->setAlternatingRowColors(true);
    ui->treeViewWalls->header()->resizeSection(0, 125);
    ui->treeViewWalls->header()->resizeSection(1, 100);
    ui->treeViewWalls->header()->resizeSection(2, 20);

    modelArea = new AreaModel(this);
    ui->treeViewArea->setModel(modelArea);
    ui->treeViewArea->setAlternatingRowColors(true);
    ui->treeViewArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QList<int> sizes;
    sizes << 100;
    sizes << height() - 100;
    ui->splitter->setSizes(sizes);



    AreaGraphicsItem *area = new AreaGraphicsItem(modelArea);
    ray = new RayGraphicsItem(modelWalls, modelArea);
    ui->doubleSpinBoxRayX->setValue(300);
    ui->doubleSpinBoxRayY->setValue(150);
    ui->doubleSpinBoxRayAngle->setValue(175);
    fillRayParams();

    connect(ui->doubleSpinBoxRayX, SIGNAL(valueChanged(double)), this, SLOT(fillRayParams()));
    connect(ui->doubleSpinBoxRayY, SIGNAL(valueChanged(double)), this, SLOT(fillRayParams()));
    connect(ui->doubleSpinBoxRayAngle, SIGNAL(valueChanged(double)), this, SLOT(fillRayParams()));



    Scene *scene = new Scene(this);
    scene->setWalls(walls);
    //scene->setArea(modelArea);
    scene->addItem(area);
    scene->addItem(ray);
    ui->graphicsView->setScene(scene);




// TODO:
    connect(modelWalls, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
            this, SLOT(onChangeInWalls(QModelIndex,QModelIndex,QVector<int>)));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonAddLine_clicked()
{
    modelArea->append(Figure(QLine()));
}

void MainWindow::on_pushButtonAddEllipse_clicked()
{
    modelArea->append(Figure(200,200,10,10));
}

void MainWindow::on_pushButtonClear_clicked()
{
    modelArea->clear();
}

void MainWindow::onChangeInWalls(const QModelIndex &topLeft,
                                 const QModelIndex &bottomRight,

                                 const QVector<int> &/*roles*/)
{
    // on change in walls just update scene's graphics item
    QList<int> changedRows;
    if (topLeft.parent().isValid()) {
        // change in text
        changedRows << topLeft.parent().row();
    }
    else {
        // change in color?
        int row = topLeft.row();
        while (row <= bottomRight.row()) {
            changedRows << row;

            ++row;
        }
    }

    foreach (int wallIndex, changedRows) {
        // call scene update wallIndex
        // TODO
    }
}

void MainWindow::onChangeInArea(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    // TODO
}

void MainWindow::on_pushButtonBuild_clicked()
{
    ray->calcBuild();
}

void MainWindow::on_pushButtonStep_clicked()
{
    ray->calcStep();
}

void MainWindow::fillRayParams()
{
    ray->setStartPoint(QPointF(ui->doubleSpinBoxRayX->value(), ui->doubleSpinBoxRayY->value()));
    ray->setStartAngle(ui->doubleSpinBoxRayAngle->value());
}
