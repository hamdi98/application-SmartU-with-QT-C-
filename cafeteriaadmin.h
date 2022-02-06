#ifndef CAFETERIAADMIN_H
#define CAFETERIAADMIN_H

#include <QFrame>
#include "produit.h"
#include "connection.h"
#include <QMessageBox>
#include <QtCore>
#include <QtGui>
#include<QPrinter>
#include<QPrintDialog>

namespace Ui {
class CafeteriaAdmin;
}

class CafeteriaAdmin : public QFrame
{
    Q_OBJECT

public:
    explicit CafeteriaAdmin(QWidget *parent = nullptr);
    ~CafeteriaAdmin();

private slots:
    void on_pushButton_10_released();

    void on_pushButton_11_released();

    void on_Affichage_produit_doubleClicked(const QModelIndex &index);

    void on_pushButton_2_released();

    void on_pushButton_released();

private:
    Ui::CafeteriaAdmin *ui;
};

#endif // CAFETERIAADMIN_H
