#ifndef WITHDRAW_H
#define WITHDRAW_H

#include <QDialog>
#include "account.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class Withdraw;
}

class Withdraw : public QDialog
{
    Q_OBJECT

public:
    explicit Withdraw(QWidget *parent = nullptr,Account *account=nullptr);
    ~Withdraw();
    void function();

private:
    Ui::Withdraw *ui;
    Account *account;
    QLineEdit *aLEd;
    QPushButton *qp;
    QLabel *albl;
};

#endif // WITHDRAW_H
