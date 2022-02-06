#include "gererabonnement.h"
#include "ui_gererabonnement.h"

GererAbonnement::GererAbonnement(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::GererAbonnement)
{
    ui->setupUi(this);
    refreshtableabonnement();
    notifyIcon = new QSystemTrayIcon(this);
        notifyIcon->setVisible(true);
}

GererAbonnement::~GererAbonnement()
{
    delete ui;
}

void GererAbonnement::on_pb_ajouter_released()
{
    if(ui->lineEdit_CIN->text().size()>0)
    {
        Abonnement *a = new Abonnement();
        a->Setcine(ui->lineEdit_CIN->text());
        a->Setid("1");
        a->Settype(ui->comboBox_Type->currentText());
        a->creer();
        delete a;
        refreshtableabonnement();
        notifyIcon->show();
        notifyIcon->showMessage(tr("info"),tr("vous etes abonne"), QSystemTrayIcon::Information,10000);

    }
    else
    {
        QMessageBox::warning(this,"Erreur","Détails insuffisants",QMessageBox::Ok);
    }
}

void GererAbonnement::on_pushButton_8_released()
{
    if((ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),0).data().toString().size()>0)&&(ui->lineEdit_CIN->text().size()>0))
    {
        Abonnement *a = new Abonnement();
        a->Setcine(ui->lineEdit_CIN->text());
        a->Settype(ui->comboBox_Type->currentText());
        a->Setid(ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),0).data().toString());
        a->modifier();
        delete a;
        refreshtableabonnement();
    }
    else
    {
        QMessageBox::warning(this,"Erreur","Veuillez selectionner un abonnement du tableau à modifier et complétez les détails",QMessageBox::Ok);
    }
}

void GererAbonnement::refreshtableabonnement()
{
    QSqlQuery *q = new QSqlQuery();
    q->prepare("Select * from abonnement");
    q->exec();
    QSqlQueryModel *m = new QSqlQueryModel();
    m->setQuery(*q);
    m->setHeaderData(1, Qt::Horizontal, tr("CIN"));
    m->setHeaderData(2, Qt::Horizontal, tr("Type"));
    ui->tableView_2->setModel(m);
    ui->tableView_2->setColumnHidden(0,true);
    ui->tableView_2->setColumnWidth(1,ui->tableView_2->width()/2);
    ui->tableView_2->setColumnWidth(2,ui->tableView_2->width()/2);
}

void GererAbonnement::on_pushButton_4_released()
{
    refreshtableabonnement();
}

void GererAbonnement::on_pushButton_7_released()
{
    QPrinter printer ;
        printer.setPrinterName("firas");
        QPrintDialog dialog (&printer,this);
        if(QDialog::Accepted==dialog.exec())
        {
            if(QPrinter::Landscape !=printer.orientation())
            {
                printer.setOrientation(QPrinter::Landscape);
            }
            QPoint startPoint =QPoint(1,1);
            QRegion printRegion =QRegion(1,1,printer.paperRect().width(),printer.paperRect().height());
            for (int i = 0 ; i<1 ; ++i)
            {
                ui->tableView_2->render(&printer,startPoint,printRegion,QWidget::DrawChildren);
            }
        }
}

void GererAbonnement::on_pushButton_5_released()
{
    if(ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),0).data().toString().size()>0)
    {
        Abonnement *a = new Abonnement();
        a->Setid(ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),0).data().toString());
        a->supprimer();
        delete a;
        refreshtableabonnement();
    }
    else
    {
        QMessageBox::warning(this,"Erreur","Veuillez selectionner un abonnement du tableau à supprimer",QMessageBox::Ok);
    }
}

void GererAbonnement::on_lineEdit_7_textChanged(const QString &arg1)
{
    if(arg1.size()>0)
    {
        QSqlQuery *q = new QSqlQuery();
        QSqlQueryModel *m = new QSqlQueryModel();
        switch(ui->comboBox_2->currentIndex())
        {
            case 0 :
            {
                q->prepare("SELECT * FROM ABONNEMENT WHERE TYPEABONNE = ?");
            }
            break;
            case 1 :
            {
                q->prepare("SELECT * FROM ABONNEMENT WHERE CINE = ?");
            }
            break;
        }
        q->addBindValue(arg1);
        q->exec();
        m->setQuery(*q);
        m->setHeaderData(1, Qt::Horizontal, tr("CIN"));
        m->setHeaderData(2, Qt::Horizontal, tr("Type"));
        ui->tableView_2->setModel(m);
        ui->tableView_2->setColumnHidden(0,true);
        ui->tableView_2->setColumnWidth(1,ui->tableView_2->width()/2);
        ui->tableView_2->setColumnWidth(2,ui->tableView_2->width()/2);
    }
    else
    {
        refreshtableabonnement();
    }
}

void GererAbonnement::on_tableView_2_clicked(const QModelIndex &index)
{
    ui->lineEdit_CIN->setText(ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),1).data().toString());
    if(ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),2).data().toString()=="Mensuel")
    {
        ui->comboBox_Type->setCurrentIndex(0);
    }
    else
    {
        ui->comboBox_Type->setCurrentIndex(1);
    }
}
