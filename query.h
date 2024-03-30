#ifndef QUERY_H
#define QUERY_H

#include <QDialog>
#include "employee.h"
#include <QRadioButton>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class Query;
}

class Query : public QDialog
{
    Q_OBJECT

public:
    explicit Query(QWidget *parent = nullptr,Employee *emplyee=nullptr);
    ~Query();
    void function();
    void on_credit_clicked();
    void on_saving_clicked();

private:
    Ui::Query *ui;
    Employee *employee;
    QRadioButton *credit;
    QRadioButton *saving;
    QLabel *userNameLbl;
    QLabel *pwdLbl;
    QLabel *IDLbl;
    QLineEdit *userNameLEd;
    QLineEdit *pwdLEd;
    QLineEdit *IDLEd;
    QPushButton *queryBtn;
    QPushButton *exitBtn;

};

#endif // QUERY_H
