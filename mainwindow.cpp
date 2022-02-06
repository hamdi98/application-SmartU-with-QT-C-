#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"

MainWindow::MainWindow(QWidget *parent, int type, QString login) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    acceuil* a = new acceuil();
    ui->stackedWidget->insertWidget(0,a);
    a->remplir(login,type);
    ui->page1->setText("Acceuil");
    if(type==1)
    {
        enseignant *e = new enseignant();
        ui->stackedWidget->insertWidget(1,e);
        niveauclasse *n = new niveauclasse();
        ui->stackedWidget->insertWidget(2,n);
        ui->page2->setText("Gérer Enseignant");
        ui->page3->setText("Gérer Classe");
        cafeteriaactualadmin *c = new cafeteriaactualadmin();
        ui->stackedWidget->insertWidget(3,c);
        ui->page4->setText("Gestion Buvette");
        gerer_abonneP *ap = new gerer_abonneP();
        ui->stackedWidget->insertWidget(4,ap);
        ui->page5->setText("Gérer Parking");
        ui->page6->setHidden(true);
    }
    if(type==2)
    {
        demandestaff *d = new demandestaff();
        ui->stackedWidget->insertWidget(1,d);
        ui->page2->setText("Demandes et Materiel");
        ui->stackedWidget->insertWidget(2,chartview());
        ui->page3->setText("Statistiques");
        GererAbonnement *a = new GererAbonnement();
        ui->stackedWidget->insertWidget(3,a);
        ui->page4->setText("Gestion Abonnements de la Librairie");
        GestionEmprunt *g = new GestionEmprunt();
        ui->stackedWidget->insertWidget(4,g);
        ui->page5->setText("Gestion Emprunts de la librairie");
        foyerui *f = new foyerui();
        ui->stackedWidget->insertWidget(5,f);
        ui->page6->setText("Gestion Foyer");

    }
    if(type==3)
    {
        QSqlQuery q;
        q.prepare("SELECT CIN FROM PERSONNE WHERE MAIL=?");
        q.addBindValue(login);
        q.exec();
        q.first();
        demandeenseignant *d = new demandeenseignant(nullptr,q.value(0).toInt());
        ui->stackedWidget->insertWidget(1,d);
        ui->page2->setText("Demandes et Recus");
        ui->page3->setHidden(true);
        ui->page4->setHidden(true);
        ui->page5->setHidden(true);
        ui->page6->setHidden(true);
    }
    if(type==4)
    {
        CafeteriaAdmin *c = new CafeteriaAdmin();
        ui->stackedWidget->insertWidget(1,c);
        ui->page2->setText("Buvette");
        place2 *p = new place2();
        ui->stackedWidget->insertWidget(2,p);
        ui->page3->setText("Places librairie");
        etudiantt *et = new etudiantt();
        ui->stackedWidget->insertWidget(3,et);
        ui->page4->setText("Foyer");
        ui->page5->setHidden(true);
        ui->page6->setHidden(true);
    }
    ui->stackedWidget->setCurrentIndex(0);
    ui->Username->setText(a->getnom());
    clickbutton();
    this->login=login;
    this->type=type;
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_closebutton_released()
{
    close();
}

void MainWindow::on_minimizebutton_released()
{
    setWindowState(Qt::WindowMinimized);
}

void MainWindow::unclickbutton()
{
    int i;
    i=ui->stackedWidget->currentIndex();
    switch (i)
    {
        case 0 :
        {
            ui->page1->setStyleSheet("QPushButton{"
                                     "border: none;"
                                     "outline: none;"
                                     "}"
                                     "QPushButton:foucs{"
                                     "background-color: rgb(240,240,240);"
                                     "}"
                                     "QPushButton:hover{"
                                     "background-color: rgb(240,240,240);"
                                     "}");
        }
            break;
        case 1 :
        {
            ui->page2->setStyleSheet("QPushButton{"
                                     "border: none;"
                                     "outline: none;"
                                     "}"
                                     "QPushButton:foucs{"
                                     "background-color: rgb(240,240,240);"
                                     "}"
                                     "QPushButton:hover{"
                                     "background-color: rgb(240,240,240);"
                                     "}");
        }
            break;
        case 2 :
        {
            ui->page3->setStyleSheet("QPushButton{"
                                     "border: none;"
                                     "outline: none;"
                                     "}"
                                     "QPushButton:foucs{"
                                     "background-color: rgb(240,240,240);"
                                     "}"
                                     "QPushButton:hover{"
                                     "background-color: rgb(240,240,240);"
                                     "}");
        }
            break;
        case 3 :
        {
            ui->page4->setStyleSheet("QPushButton{"
                                     "border: none;"
                                     "outline: none;"
                                     "}"
                                     "QPushButton:foucs{"
                                     "background-color: rgb(240,240,240);"
                                     "}"
                                     "QPushButton:hover{"
                                     "background-color: rgb(240,240,240);"
                                     "}");
        }
            break;
        case 4 :
        {
        ui->page5->setStyleSheet("QPushButton{"
                                 "border: none;"
                                 "outline: none;"
                                 "}"
                                 "QPushButton:foucs{"
                                 "background-color: rgb(240,240,240);"
                                 "}"
                                 "QPushButton:hover{"
                                 "background-color: rgb(240,240,240);"
                                 "}");
        }
            break;
        case 5 :
        {
        ui->page6->setStyleSheet("QPushButton{"
                                 "border: none;"
                                 "outline: none;"
                                 "}"
                                 "QPushButton:foucs{"
                                 "background-color: rgb(240,240,240);"
                                 "}"
                                 "QPushButton:hover{"
                                 "background-color: rgb(240,240,240);"
                                 "}");
        }
            break;
    }
}

void MainWindow::clickbutton()
{
    int i;
    i=ui->stackedWidget->currentIndex();
    switch(i)
    {
        case 0 :
        {
            ui->page1->setStyleSheet("border: none;"
                                     "outline: none;"
                        "background-color: rgb(240,240,240);");
        }
            break;
        case 1 :
        {
            ui->page2->setStyleSheet("border: none;"
                                     "outline: none;"
                        "background-color: rgb(240,240,240);");
        }
            break;
        case 2 :
        {
            ui->page3->setStyleSheet("border: none;"
                                     "outline: none;"
                        "background-color: rgb(240,240,240);");
        }
            break;
        case 3 :
        {
            ui->page4->setStyleSheet("border: none;"
                                     "outline: none;"
                        "background-color: rgb(240,240,240);");
        }
            break;
        case 4 :
        {
            ui->page5->setStyleSheet("border: none;"
                                     "outline: none;"
                        "background-color: rgb(240,240,240);");
        }
            break;
        case 5 :
        {
            ui->page6->setStyleSheet("border: none;"
                                     "outline: none;"
                        "background-color: rgb(240,240,240);");
        }
            break;
    }
}

void MainWindow::on_page1_released()
{
    if(ui->stackedWidget->currentIndex()!=0)
    {
        unclickbutton();
        ui->stackedWidget->setCurrentIndex(0);
        clickbutton();
    }
}

void MainWindow::on_page2_released()
{
    if(ui->stackedWidget->currentIndex()!=1)
    {
        unclickbutton();
        ui->stackedWidget->setCurrentIndex(1);
        clickbutton();
    }
}

void MainWindow::on_page3_released()
{
    if(type==2)
    {
        ui->stackedWidget->removeWidget(ui->stackedWidget->widget(2));
        ui->stackedWidget->insertWidget(2,chartview());
    }
    if(ui->stackedWidget->currentIndex()!=2)
    {
        unclickbutton();
        ui->stackedWidget->setCurrentIndex(2);
        clickbutton();
    }
}

void MainWindow::on_page4_released()
{
    if(ui->stackedWidget->currentIndex()!=3)
    {
        unclickbutton();
        ui->stackedWidget->setCurrentIndex(3);
        clickbutton();
    }
}

QWidget* MainWindow::chartview()
{
    QSqlQuery q,q1;
    int i=0;
    int j=0;
    QString tabmat[50];
    QBarSet *set[50];
    q.prepare("SELECT IDMAT, NOMMAT FROM MATERIEL");
    q.exec();
    q.first();
    do
    {
        q1.prepare("SELECT * FROM RECU WHERE IDMAT= ?");
        q1.addBindValue(q.value(0));
        q1.exec();
        q1.first();
        j=0;
        do
        {
            j+=q1.value(1).toInt();
        }while(q1.next());
        QBarSet *n = new QBarSet(q.value(1).toString());
        set[i] = n;
        *set[i] << j;
        i++;
    }while(q.next());
    QBarSeries* series = new QBarSeries();
    for(j=0;j<=i-1;j++)
    {
        series->append(set[j]);
    }
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Graph");
    chart->setAnimationOptions(QChart::AllAnimations);
    QStringList categories;
    categories << "Utilisation par ressource";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis,series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    QChartView *r = new QChartView(chart);
    r->setRenderHint(QPainter::Antialiasing);
    QPalette pal = qApp->palette();
    pal.setColor(QPalette::Window, QRgb(0xffffff));
    pal.setColor(QPalette::WindowText, QRgb(0x404040));
    qApp->setPalette(pal);
    return r;
}

void MainWindow::on_pushButton_2_released()
{
    this->close();
    Login* x= new Login(nullptr,login);
    x->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    x->show();
}

void MainWindow::on_page5_released()
{
    if(ui->stackedWidget->currentIndex()!=4)
    {
        unclickbutton();
        ui->stackedWidget->setCurrentIndex(4);
        clickbutton();
    }
}

void MainWindow::on_page6_released()
{
    if(ui->stackedWidget->currentIndex()!=5)
    {
        unclickbutton();
        ui->stackedWidget->setCurrentIndex(5);
        clickbutton();
    }
}
