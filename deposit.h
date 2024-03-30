#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QDialog>
#include "account.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class Deposit;
}

class Deposit : public QDialog
{
    Q_OBJECT

public:
    explicit Deposit(QWidget *parent = nullptr,Account *account=nullptr);
    ~Deposit();
    void function();

private:
    Ui::Deposit *ui;
    Account *account;
    QLineEdit *aLEd;
    QPushButton *qp;
    QLabel *albl;
};

#endif // DEPOSIT_H
