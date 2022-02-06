#ifndef GERER_ABONNEP_H
#define GERER_ABONNEP_H

#include "abonnep.h"
#include <QWidget>
#include <QSortFilterProxyModel>
#include <QSystemTrayIcon>
#include "arduino.h"
namespace Ui {
class gerer_abonneP;
}

class gerer_abonneP : public QWidget
{
    Q_OBJECT

public:
    explicit gerer_abonneP(QWidget *parent = nullptr);
    ~gerer_abonneP();
    void sendard ();

private slots:
    void on_save_clicked();

    void on_supprimer_clicked();

  //  void on_afficher_clicked();

    void on_lineEdit_textChanged(const QString &arg1);



    void on_modifier_clicked();

    void on_tabP_activated(const QModelIndex &index);



    void on_retourner_clicked();

    void on_ajouterplaceparking_clicked();

    void on_afficherplaceparking_clicked();

    void on_modifierplaceparking_clicked();

    void on_supprimerplaceparking_clicked();

  //  void on_tabplace_activated(const QModelIndex &index);

    void on_GESTIONABONNEPARKING_clicked();

    void on_GESTIONPLACEPARKING_clicked();

    void on_afficher_demande_clicked();

    void on_consulterdemande_clicked();

    void on_demandeabonnement_clicked();

    void on_envoyerdemandeabonnement_clicked();

    void on_supprimer_demande_clicked();

    //void on_TABDE_activated(const QModelIndex &index);

    void update_label();   // slot permettant la mise à jour du label état de la lampe 1,
        // ce slot est lancé à chaque réception d'un message de Arduino


    void on_val_clicked();

private:
    QByteArray data; // variable contenant les données reçues

    Arduino A; // objet temporaire
    Ui::gerer_abonneP *ui;
      QSystemTrayIcon *notify;

};

#endif // GERER_ABONNEP_H
