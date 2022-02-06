#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QKeyEvent>
#include <QMessageBox>
#include <QtCharts>
#include "acceuil.h"
#include "demandestaff.h"
#include "demandeenseignant.h"
#include "enseignant.h"
#include "niveauclasse.h"
#include "cafeteriaadmin.h"
#include "cafeteriaactualadmin.h"
#include "gererabonnement.h"
#include "gestionemprunt.h"
#include "place2.h"
#include "gerer_abonnep.h"
#include "foyerui.h"
#include "etudiantt.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, int type = -1, QString login = nullptr);
    ~MainWindow();

private slots:
    void on_closebutton_released();

    void on_minimizebutton_released();

    void on_page1_released();

    void on_page2_released();

    void on_page3_released();

    void on_page4_released();

    void on_pushButton_2_released();

    void on_page5_released();

    void on_page6_released();

private:
    Ui::MainWindow *ui;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
    void unclickbutton();
    void clickbutton();
    QWidget* chartview();
    QString login;
    int type;
};

#endif // MAINWINDOW_H
