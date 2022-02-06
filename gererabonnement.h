#ifndef GERERABONNEMENT_H
#define GERERABONNEMENT_H
#include "abonnement.h"
#include <QFrame>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QPrinter>
#include <QPrintDialog>
#include <QSystemTrayIcon>

namespace Ui {
class GererAbonnement;
}

class GererAbonnement : public QFrame
{
    Q_OBJECT

public:
    explicit GererAbonnement(QWidget *parent = nullptr);
    ~GererAbonnement();
    void refreshtableabonnement();

private slots:
    void on_pb_ajouter_released();

    void on_pushButton_8_released();

    void on_pushButton_4_released();

    void on_pushButton_7_released();

    void on_pushButton_5_released();

    void on_lineEdit_7_textChanged(const QString &arg1);

    void on_tableView_2_clicked(const QModelIndex &index);

private:
    Ui::GererAbonnement *ui;
    QSystemTrayIcon  *notifyIcon ;
};

#endif // GERERABONNEMENT_H
