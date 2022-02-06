#ifndef PLACE2_H
#define PLACE2_H

#include <QDialog>
#include "arduino.h"
namespace Ui {
class place2;
}

class place2 : public QDialog
{
    Q_OBJECT

public:
    explicit place2(QWidget *parent = nullptr);
    ~place2();
    void refresh();

private slots:

    void on_reserverplace_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::place2 *ui;
    QByteArray data;
    Arduino A;
};

#endif // PLACE2_H
