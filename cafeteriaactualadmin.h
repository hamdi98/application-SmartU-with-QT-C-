#ifndef CAFETERIAACTUALADMIN_H
#define CAFETERIAACTUALADMIN_H

#include <QFrame>
#include "produit.h"
#include "connection.h"
#include <QPixmap>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QDebug>
#include "arduino.h"
#include "ajout_produit.h"

namespace Ui {
class cafeteriaactualadmin;
}

class cafeteriaactualadmin : public QFrame
{
    Q_OBJECT

public:
    explicit cafeteriaactualadmin(QWidget *parent = nullptr);
    ~cafeteriaactualadmin();

private slots:

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_people_5_clicked();

    void on_Affichage_produit_doubleClicked(const QModelIndex &index);
    void update_label();

private:
    Ui::cafeteriaactualadmin *ui;
    QByteArray data;
    Arduino A;
};

#endif // CAFETERIAACTUALADMIN_H
