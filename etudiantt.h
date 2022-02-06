#ifndef ETUDIANTT_H
#define ETUDIANTT_H

#include <QWidget>
#include "arduino.h"

namespace Ui {
class etudiantt;
}

class etudiantt : public QWidget
{
    Q_OBJECT

public:
    explicit etudiantt(QWidget *parent = nullptr);
    ~etudiantt();


private slots:
    void on_demande_clicked();

    void on_pushButton_2_clicked();

    void on_annulerdemande_clicked();
    void arduino_verif() ;
    void envoie() ;
private:
    Ui::etudiantt *ui;
    Arduino A;

    QByteArray data;
};

#endif // ETUDIANTT_H
