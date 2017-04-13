#ifndef WIZARDWELCOME_H
#define WIZARDWELCOME_H

//#include "mainwindow.h"

#include <QWizard>

namespace Ui {
class WizardWelcome;
}

class WizardWelcome : public QWizard
{
    Q_OBJECT

public:
    explicit WizardWelcome(QWidget *parent = 0);
    ~WizardWelcome();

    void initializePage(int id);
    bool validateCurrentPage();
    void done(int result);

    bool isLoad() const;
    QString filename() const;
    int wallCount() const;
    qreal coef() const;

private slots:
    void on_pushButtonSearch_clicked();

private:
    Ui::WizardWelcome *ui;
//    MainWindow mainwindow;
};

#endif // WIZARDWELCOME_H
