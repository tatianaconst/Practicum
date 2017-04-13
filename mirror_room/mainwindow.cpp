#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "wallmodeldelegate.h"
#include "scene.h"
#include "raygraphicsitem.h"
#include "extensions.h"

#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    scene(NULL),
    ray(NULL),
    modelWalls(NULL),
    modelArea(NULL),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
// init walls
//    QList<Wall*> walls;
//    walls.append(new Wall("wall1", QPoint(100,100), QPoint(100,200), Wall::Convex, 200));
//    walls.append(new Wall("wall2", QPoint(200,100), QPoint(250,300)));
//    walls.append(new Wall("wall3", QPoint(0,1), QPoint(2,0)));


//    walls.append(new Wall("wall1", QPoint(100,100), QPoint(500,100)));
//    walls.append(new Wall("wall1", QPoint(500,100), QPoint(500,500)));
//    walls.append(new Wall("wall1", QPoint(500,500), QPoint(100,500)));
//    walls.append(new Wall("wall1", QPoint(100,500), QPoint(100,100)));


//    setModelWalls(walls);
//    setModelArea(QList<Figure>());
//

    QList<int> sizes;
    sizes << 100;
    sizes << height() - 100;
    ui->splitter->setSizes(sizes);

    connect(ui->doubleSpinBoxRayX, SIGNAL(valueChanged(double)), this, SLOT(fillRayParams()));
    connect(ui->doubleSpinBoxRayY, SIGNAL(valueChanged(double)), this, SLOT(fillRayParams()));
    connect(ui->doubleSpinBoxRayAngle, SIGNAL(valueChanged(double)), this, SLOT(fillRayParams()));

    WizardWelcome wiz(this);

    QList<Wall*> walls;
    QList<Figure> figures;
    if (wiz.exec() == QWizard::Accepted) {
        if (wiz.isLoad()) {
            QFile file(wiz.filename());

            if (!file.open(QFile::ReadOnly)) {
                qWarning(QString("error on openning file \'%1\' - load from dump failed")
                         .arg(file.fileName()).toLocal8Bit().data());
                return;
            }

            QDataStream ds(&file);

            int wallCount;
            ds >> wallCount;
            for (int i=0; i < wallCount; ++i) {
                Wall *wall = new Wall();
                ds >> *wall;
                walls.append(wall);
            }

            ds >> figures;
            setModelArea(figures);
            setModelWalls(walls);
            ray = new RayGraphicsItem(modelWalls, modelArea);
            ds >> *ray;
            finish();
//            ds >> *ray;

            setSpinBoxes(ray->getSPoint().x(), ray->getSPoint().y(), ray->getSAngle());
        }
        else {

            qDebug() << "wallcount" << wiz.wallCount();
            // TODO
            for (int i=0; i < wiz.wallCount(); ++i) {
                walls.append(new Wall(QString("wall %1").arg(i),
                                      QPoint(100,100),
                                      QPoint(200, 200),
                                      Wall::Straight,
                                      0,
                                      wiz.coef()));
            }

            setModelArea(figures);
            setModelWalls(walls);

            finish();
        }
    }
    else
        Q_ASSERT(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::finish()
{
    Q_ASSERT_X(scene==NULL, "MainWindow::finish", "scene not NULL");

    AreaGraphicsItem *area = new AreaGraphicsItem(modelArea);
    scene = new Scene(this);
    scene->setWalls(modelWalls->getWalls());
    scene->addItem(area);
    if (!ray)
        ray = new RayGraphicsItem(modelWalls, modelArea);
    scene->addItem(ray);
    ui->graphicsView->setScene(scene);

    // TEST
//    ui->doubleSpinBoxRayX->setValue(300);
//    ui->doubleSpinBoxRayY->setValue(150);
//    ui->doubleSpinBoxRayAngle->setValue(175);
//    fillRayParams();
    // TEST
}

void MainWindow::setSpinBoxes(qreal x, qreal y, qreal angle)
{
    ui->doubleSpinBoxRayX->setValue(x);
    ui->doubleSpinBoxRayY->setValue(y);
    ui->doubleSpinBoxRayAngle->setValue(angle);
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
    if (!ray)
        return;
    ray->setStartPoint(QPointF(ui->doubleSpinBoxRayX->value(), ui->doubleSpinBoxRayY->value()));
    ray->setStartAngle(ui->doubleSpinBoxRayAngle->value());
}

void MainWindow::on_actionSave_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Сохранение конфигурации эксперимента"),
                                                    "",
                                                    "Mirror Experiment Configuration (*.mec);;");
    if (!filename.isEmpty()) {
        QFile file(filename);

        if (!file.open(QFile::WriteOnly)) {
            qWarning(QString("error on openning file \'%1\' - dump failed").arg(filename).toLocal8Bit().data());
            return;
        }
        QDataStream ds(&file);

        ds << *modelWalls;
        ds << *modelArea;
        ds << *ray;
    }
}


void MainWindow::setModelWalls(const QList<Wall *> &walls)
{
    modelWalls = new WallModel(walls, this);
    ui->treeViewWalls->setModel(modelWalls);
    ui->treeViewWalls->setItemDelegate(new WallModelDelegate(modelWalls, ui->treeViewWalls));
    ui->treeViewWalls->setAlternatingRowColors(true);
    ui->treeViewWalls->header()->resizeSection(0, 125);
    ui->treeViewWalls->header()->resizeSection(1, 100);
    ui->treeViewWalls->header()->resizeSection(2, 20);
}

void MainWindow::setModelArea(const QList<Figure> &figures)
{
    modelArea = new AreaModel(this);
    foreach (Figure figure, figures)
        modelArea->append(figure);

    ui->treeViewArea->setModel(modelArea);
    ui->treeViewArea->setAlternatingRowColors(true);
    ui->treeViewArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MainWindow::on_pushButtonRe_clicked()
{
    ray->setStartAngle(ui->doubleSpinBoxRayAngle->value());
    ray->setStartPoint(QPointF(ui->doubleSpinBoxRayX->value(), ui->doubleSpinBoxRayY->value()));
    ray->calcInit();
}
