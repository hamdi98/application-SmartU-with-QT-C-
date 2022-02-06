#ifndef ENSEIGNANT_H
#define ENSEIGNANT_H
#include "arduino.h"
#include <QDialog>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSystemTrayIcon>
namespace Ui {
class enseignant;
}

class enseignant : public QDialog
{
    Q_OBJECT

public:
    explicit enseignant(QWidget *parent = nullptr);
    ~enseignant();
    enseignant (int,QString,QString,QString,int);
    QString get_nom(){return nom;}
    QString get_prenom(){return prenom;}
    int get_CIN(){return CIN;}
    QString get_matiere(){return matiere;}
    void Setnom(QString x){nom=x;}
    void Setprenom(QString x){prenom=x;}
    void Setmat(QString x){matiere=x;}
    void Setdate(QString date){daten=date;}
    void Setnat(QString nat){nationalite=nat;}
    void Setmail(QString m){mail=m;}
    void Setmdp(QString m){mdp=m;}
    void Setcin(int cin){CIN=cin;}
    void Setsal(int sal){salaire = sal;}
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer();
    bool modifier();
    int get_salaire();

private slots:


    void on_pb_ajouter_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    bool on_lineEdit_CIN_editingFinished();

    void on_lineEdit_3_textChanged(const QString &arg1);

    void update_label();

    void send();


   void on_tableView_doubleClicked();

   void on_pb_modifier_clicked();

private:
    QString nom,prenom,matiere,daten,nationalite,mail,mdp;
    int CIN,salaire;
    Ui::enseignant *ui;
    Arduino A;
    QSystemTrayIcon *notifyIcon;
    QByteArray data;
};

#endif // ENSEIGNANT_H
