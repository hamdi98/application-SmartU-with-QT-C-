#include "cafeteriaadmin.h"
#include "ui_cafeteriaadmin.h"

CafeteriaAdmin::CafeteriaAdmin(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CafeteriaAdmin)
{
    ui->setupUi(this);
    Produit p;
    QSqlQueryModel* model=new QSqlQueryModel();
    model=p.afficherBuvette();
    ui->Affichage_produit->setModel(model);
}

CafeteriaAdmin::~CafeteriaAdmin()
{
    delete ui;
}

void CafeteriaAdmin::on_pushButton_10_released()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery q;
    QString id=ui->research_2->text();
    q.prepare("select IDPRODUIT,QTEPRODUIT,DATEPRODUIT,PRIXPRODUIT from PRODUIT where IDPRODUIT like ? ");
    q.addBindValue("%"+id+"%");
    if (q.exec())
    {
        model->setQuery(q);
        ui->Affichage_produit->setModel(model);
    }
}

void CafeteriaAdmin::on_pushButton_11_released()
{
    QSqlQuery qry1;
    Produit p;
    QSqlQueryModel *model=new QSqlQueryModel();
    int currentcol=ui->comboBox_4->currentIndex();

    if (currentcol==0)
    {qry1.prepare("select IDPRODUIT,QTEPRODUIT,DATEPRODUIT,PRIXPRODUIT from PRODUIT ");}

    else if (currentcol==1)
    {qry1.prepare("select IDPRODUIT,QTEPRODUIT,DATEPRODUIT,PRIXPRODUIT from PRODUIT where IDBUVETTE=(?)");
        qry1.addBindValue(23);}

    else if (currentcol==2)
    {qry1.prepare("select IDPRODUIT,QTEPRODUIT,DATEPRODUIT,PRIXPRODUIT from PRODUIT where IDBUVETTE=(?)");
        qry1.addBindValue(24);}

    else if (currentcol==3)
    {qry1.prepare("select IDPRODUIT,QTEPRODUIT,DATEPRODUIT,PRIXPRODUIT from PRODUIT where IDBUVETTE=(?)");
        qry1.addBindValue(25);}

    else if (currentcol==4)
    {qry1.prepare("select IDPRODUIT,QTEPRODUIT,DATEPRODUIT,PRIXPRODUIT from PRODUIT where IDBUVETTE=(?)");
        qry1.addBindValue(26);}

    if (qry1.exec())
    {
        model->setQuery(qry1);
        ui->Affichage_produit->setModel(model);
    }
}

void CafeteriaAdmin::on_Affichage_produit_doubleClicked(const QModelIndex &index)
{
    QSqlQuery q;
    QString selectedIDPRODUIT=ui->Affichage_produit->model()->data(index).toString();
    QSqlQueryModel *model1=new QSqlQueryModel();
    q.prepare("select IDPRODUIT,QTEPRODUIT,DATEPRODUIT,PRIXPRODUIT,IDBUVETTE from PRODUIT where IDPRODUIT=(?) ");
    q.addBindValue(selectedIDPRODUIT);
    q.exec();
    model1->setQuery(q);
    ui->Affichage_produit_2->setModel(model1);
    ui->Affichage_produit_2->show();
}

void CafeteriaAdmin::on_pushButton_2_released()
{
    QSqlQueryModel *model1=new QSqlQueryModel();
    ui->Affichage_produit_2->setModel(model1);
}



void CafeteriaAdmin::on_pushButton_released()
{
    QMessageBox::StandardButton reply;
    reply= QMessageBox::question(this,"Confirmer","Voulez-vous imprimer votre reçu d'achat?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QString strStream;
            QTextStream out(&strStream);

            const int rowCount = ui->Affichage_produit_2->model()->rowCount();
            const int columnCount = ui->Affichage_produit_2->model()->columnCount();

            out << "<html>\n"
             "<head>\n"
             "<meta Content=\"Text/html; charset=Windows-1251\">\n"
             << "</head>\n"
             "<body bgcolor=#ffffff link=#5000A0>\n"
             "<table border=1 cellspacing=0 cellpadding=2>\n";

            // headers
            out << "<thead><tr bgcolor=#f0f0f0>";
            for (int column = 0; column < columnCount; column++)
             if (!ui->Affichage_produit_2->isColumnHidden(column))
              out << QString("<th>%1</th>").arg(ui->Affichage_produit_2->model()->headerData(column, Qt::Horizontal).toString());
            out << "</tr></thead>\n";

            // data table
            for (int row = 0; row < rowCount; row++) {
             out << "<tr>";
             for (int column = 0; column < columnCount; column++) {
              if (!ui->Affichage_produit_2->isColumnHidden(column)) {
               QString data = ui->Affichage_produit_2->model()->data(ui->Affichage_produit_2->model()->index(row, column)).toString().simplified();
               out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
              }
             }
             out << "</tr>\n";
            }
            out << "</table>\n"
             "</body>\n"
             "</html>\n";

            QTextDocument *document = new QTextDocument();
            document->setHtml(strStream);

            QPrinter printer;

            QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
            if (dialog->exec() == QDialog::Accepted) {
             document->print(&printer);
            }

            delete document;
    }
}
