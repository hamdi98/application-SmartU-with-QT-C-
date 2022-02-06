#ifndef DEMANDEENSEIGNANT_H
#define DEMANDEENSEIGNANT_H
#include "demande.h"
#include "recu.h"
#include "materiel.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QMessageBox>
#include <QPrinter>
#include <QFrame>
#include <QTextDocument>
#include <QPrintDialog>
#include "arduino.h"
#include "dos.h"
#include "stdlib.h"
namespace Ui {
class demandeenseignant;
}

class demandeenseignant : public QFrame
{
    Q_OBJECT

public:
    explicit demandeenseignant(QWidget *parent = nullptr, int id = 0);
    ~demandeenseignant();

private slots:
    void on_listView_clicked(const QModelIndex &index);

    void on_pushButton_9_released();

    void on_pushButton_5_released();

    void on_imprimerbutton_released();

    void on_pushButton_10_released();

    void update_label();

    void send();

private:
    Ui::demandeenseignant *ui;
    void refreshtablemat();
    void refreshtabledemande();
    void refreshtablerecus();
    void imprimer();
    int idens;
    Arduino A;
    QByteArray data;
};

#endif // DEMANDEENSEIGNANT_H
