#include "ajout_produit.h"
#include "ui_ajout_produit.h"

Ajout_Produit::Ajout_Produit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ajout_Produit)
{
    ui->setupUi(this);
}

Ajout_Produit::~Ajout_Produit()
{
    delete ui;
}

void Ajout_Produit::on_pushButton_clicked()
{
    Produit p;

    if (ui->comboBox_idbuvette->currentIndex()==0)
        p.set_IDBuvette(23);
    else if(ui->comboBox_idbuvette->currentIndex()==1)
        p.set_IDBuvette(24);
    else if(ui->comboBox_idbuvette->currentIndex()==2)
        p.set_IDBuvette(25);
    else if(ui->comboBox_idbuvette->currentIndex()==3)
        p.set_IDBuvette(26);

    p.set_IDProduit(ui->idproduit->text());
    p.set_qteProduit(ui->quantity->text().toInt());
    p.set_PrixProduit(ui->price->text());
    p.set_DateProduit(ui->date->text());
    p.ajouterProduit();
    close();
}
