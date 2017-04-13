#include "wizardwelcome.h"
#include "ui_wizardwelcome.h"

#include <QFileDialog>
#include <QMessageBox>

WizardWelcome::WizardWelcome(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::WizardWelcome)
{
    ui->setupUi(this);


    QList<QWizard::WizardButton> button_layout;
    button_layout << QWizard::Stretch
                  << QWizard::BackButton
                  << QWizard::NextButton
                  << QWizard::FinishButton;
    setButtonLayout(button_layout);
}

WizardWelcome::~WizardWelcome()
{
    delete ui;
}

void WizardWelcome::initializePage(int id)
{
    switch (id) {
    case 1:
        {
            ui->labelWallCount->setVisible(true);
            ui->labelCoeff->setVisible(true);
            ui->lineEditWallCount->setVisible(true);
            ui->lineEditCoeff->setVisible(true);
            ui->labelFilename->setVisible(true);
            ui->lineEditFilename->setVisible(true);
            ui->pushButtonSearch->setVisible(true);
        }


        // hide not needed
        if (ui->radioButtonLoad->isChecked()) {
            ui->labelWallCount->setVisible(false);
            ui->labelCoeff->setVisible(false);
            ui->lineEditWallCount->setVisible(false);
            ui->lineEditCoeff->setVisible(false);
        }
        else if (ui->radioButtonNew->isChecked()){
            ui->labelFilename->setVisible(false);
            ui->lineEditFilename->setVisible(false);
            ui->pushButtonSearch->setVisible(false);
        }
        break;
    default:
        break;
    }
    QWizard::initializePage(id);
}

bool WizardWelcome::validateCurrentPage()
{
    if (currentId() == 1) {
        if (ui->radioButtonLoad->isChecked()) {
            QFile file(ui->lineEditFilename->text());
            if (!file.exists()) {
                QMessageBox::warning(this,QString::fromUtf8("Файл не найден"),
                                     QString::fromUtf8("Файл %1 не существует").arg(file.fileName()));
                return false;
            }
        }
    }
    return QWizard::validateCurrentPage();
}

void WizardWelcome::done(int result)
{
//    if (ui->radioButtonLoad->isChecked()) {

//        QFile file(ui->lineEditFilename->text());

//        if (!file.open(QFile::ReadOnly)) {
//            qWarning(QString("error on openning file \'%1\' - load from dump failed")
//                     .arg(file.fileName()).toLocal8Bit().data());
//            return;
//        }

//        QDataStream ds(&file);

//        QList<Wall*> walls;
//        QList<Figure> figures;
//        RayGraphicsItem *ray = mainwindow.getRayRef();

//        int wallCount;
//        ds >> wallCount;
//        for (int i=0; i < wallCount; ++i) {
//            Wall *wall = new Wall();
//            ds >> *wall;
//            walls.append(wall);
//        }

//        ds >> figures;
//        ds >> *ray;

//        mainwindow.setModelWalls(walls);
//        mainwindow.setModelArea(figures);
//        mainwindow.setSpinBoxes(ray->getSPoint().x(), ray->getSPoint().y(), ray->getSAngle());
//        mainwindow.finish();
//    }
//    else if (ui->radioButtonNew->isChecked()) {
//        // TODO
//        // QList<Wall*> walls;  mainwindow.setWallModel(walls)
//    }
    if (validateCurrentPage())
        QWizard::done(result);
}

bool WizardWelcome::isLoad() const
{
    return ui->radioButtonLoad->isChecked();
}

QString WizardWelcome::filename() const
{
    return ui->lineEditFilename->text();
}

int WizardWelcome::wallCount() const
{
    return ui->lineEditWallCount->text().toInt();
}

qreal WizardWelcome::coef() const
{
    return ui->lineEditCoeff->text().toDouble();
}

void WizardWelcome::on_pushButtonSearch_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Загрузка конфигурации эксперимента"),
                                                    "./",
                                                    "Mirror experiment configure (*.mec);;");
    ui->lineEditFilename->setText(filename);
//        QFile file(filename);

//        if (!file.open(QFile::ReadOnly)) {
//            qWarning(QString("error on openning file \'%1\' - load from dump failed").arg(filename).toLocal8Bit().data());
//            return;
//        }

//        QDataStream ds(&file);

//        ds >> *modelWalls;
//        ds >> *modelArea;
//        ds >> *ray;

//        ray->setWallModel(modelWalls);
}
