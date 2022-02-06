#ifndef NIVEAUCLASSE_H
#define NIVEAUCLASSE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDialog>

namespace Ui {
class niveauclasse;
}

class niveauclasse : public QDialog
{
    Q_OBJECT

public:
    explicit niveauclasse(QWidget *parent = nullptr);
    ~niveauclasse();

    niveauclasse(QString,QString,QString,int);
    int get_NbrEtudiant();
    QString get_branche();
    QString get_annee();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier( QString, QString ,QString, int,int );
    bool ajouter();
    QString get_nom ();

private slots:
    void on_AfficherClasse_clicked();

    void on_AjouterClasse_clicked();

    void on_SuppClasse_clicked();

    void on_ModifierClasse_clicked();

    void on_pushButton_4_clicked();




void on_lineEdit_2_textChanged(const QString &arg1);

void on_tableView_2_doubleClicked();

private:
    Ui::niveauclasse *ui;
    QString annee,nom,branche;
    int NbrEtudiant ;

};

#endif // NIVEAUCLASSE_H
