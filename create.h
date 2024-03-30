#ifndef CREATE_H
#define CREATE_H

#include <QDialog>
#include "employee.h"
#include <QRadioButton>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class Create;
}

class Create : public QDialog
{
    Q_OBJECT

public:
    explicit Create(QWidget *parent = nullptr,Employee *employee=nullptr);
    ~Create();
    void function();
    void on_credit_clicked();
    void on_saving_clicked();

private:
    Ui::Create *ui;
    Employee *employee;
    QRadioButton *credit;
    QRadioButton *saving;
    QLabel *userNameLbl;
    QLabel *pwdLbl;
    QLabel *IDLbl;
    QLabel *phoneLbl;
    QLabel *balanceLbl;
    QLabel *rateLbl;
    QLineEdit *userNameLEd;
    QLineEdit *pwdLEd;
    QLineEdit *IDLEd;
    QLineEdit *phoneLEd;
    QLineEdit *balanceLEd;
    QLineEdit *rateLEd;
    QPushButton *queryBtn;
    QPushButton *exitBtn;
};

#endif // CREATE_H
