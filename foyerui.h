#ifndef FOYERUI_H
#define FOYERUI_H

#include"foyer.h"
#include <QWidget>

namespace Ui {
class foyerui;
}

class foyerui : public QWidget
{
    Q_OBJECT

public:
    explicit foyerui(QWidget *parent = nullptr);
    ~foyerui();

private slots:
    void on_ajouter_clicked();

    void on_rechercher_textChanged(const QString &arg1);

    void on_table_doubleClicked(const QModelIndex &index);

    void on_modifier_clicked();

    void on_supprimer1_clicked();

    void on_supprimer1_2_clicked();

    void on_afficher_2_clicked();

    void on_afficher_clicked();

private:
    Ui::foyerui *ui;
    Foyer tmpetudiant ;
};

#endif // FOYERUI_H
