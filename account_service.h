#ifndef ACCOUNT_SERVICE_H
#define ACCOUNT_SERVICE_H

#include <QDialog>
#include <QPushButton>
#include "account.h"

namespace Ui {
class account_service;
}

class account_service : public QDialog
{
    Q_OBJECT

public:
    explicit account_service(QWidget *parent = nullptr,Account *account = nullptr);
    ~account_service();
    void acc_withdraw();
    void acc_transfer();
    void acc_deposit();
    void acc_check();

private:
    Ui::account_service *ui;
    Account *account;
    QPushButton *withdraw;
    QPushButton *transfer;
    QPushButton *deposit;
    QPushButton *check;
};

#endif // ACCOUNT_SERVICE_H
