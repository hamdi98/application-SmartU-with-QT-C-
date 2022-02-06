#ifndef GESTIONEMPRUNT_H
#define GESTIONEMPRUNT_H
#include "emprunt.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QPrinter>
#include <QPrintDialog>
#include <QFrame>

namespace Ui {
class GestionEmprunt;
}

class GestionEmprunt : public QFrame
{
    Q_OBJECT

public:
    explicit GestionEmprunt(QWidget *parent = nullptr);
    ~GestionEmprunt();
    void refreshtableemprunt();

private slots:
    void on_AjouterClasse_released();

    void on_ModifierClasse_released();

    void on_AfficherClasse_released();

    void on_SuppClasse_released();

    void on_tableView_2_clicked(const QModelIndex &index);

    void on_lineEdit_2_textChanged(const QString &arg1);

private:
    Ui::GestionEmprunt *ui;
};

#endif // GESTIONEMPRUNT_H
