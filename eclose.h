#ifndef ECLOSE_H
#define ECLOSE_H

#include <QDialog>
#include "employee.h"
#include <QRadioButton>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class Eclose;
}

class Eclose : public QDialog
{
    Q_OBJECT

public:
    explicit Eclose(QWidget *parent = nullptr,Employee *employee=nullptr);
    ~Eclose();
    void function();
    void on_credit_clicked();
    void on_saving_clicked();

private:
    Ui::Eclose *ui;
    Employee *employee;
    QRadioButton *credit;
    QRadioButton *saving;
    QLabel *userNameLbl;
    QLabel *pwdLbl;
    QLabel *IDLbl;
    QLineEdit *userNameLEd;
    QLineEdit *pwdLEd;
    QLineEdit *IDLEd;
    QPushButton *closeBtn;
    QPushButton *exitBtn;
};

#endif // ECLOSE_H
