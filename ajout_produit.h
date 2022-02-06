#ifndef AJOUT_PRODUIT_H
#define AJOUT_PRODUIT_H
#include "produit.h"
#include <QDialog>
#include <QString>
#include <QComboBox>
#include<QDebug>
namespace Ui {
class Ajout_Produit;
}

class Ajout_Produit : public QDialog
{
    Q_OBJECT

public:
    explicit Ajout_Produit(QWidget *parent = nullptr);
    ~Ajout_Produit();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Ajout_Produit *ui;
};

#endif // AJOUT_PRODUIT_H
