#ifndef DEMANDESTAFF_H
#define DEMANDESTAFF_H
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QFrame>
#include <QMessageBox>
#include "materiel.h"
#include "demande.h"
#include "recu.h"
#include "staff.h"
#include "arduino.h"

namespace Ui {
class demandestaff;
}

class demandestaff : public QFrame
{
    Q_OBJECT

public:
    explicit demandestaff(QWidget *parent = nullptr);
    ~demandestaff();

private slots:
    void on_pushButton_8_released();

    void on_pushButton_15_released();

    void on_pushButton_14_released();

    void on_pushButton_7_released();

    void on_pushButton_6_released();

    void on_tableView_8_clicked(const QModelIndex &index);

    void on_pushButton_16_released();

    void update_label();

    void send();

private:
    Ui::demandestaff *ui;
    void refreshtabledemande();
    void refreshtablestock();
    void refreshtablemat();
    void searchdemande(QString id);
    Arduino A;
    QByteArray data;
};

#endif // DEMANDESTAFF_H
