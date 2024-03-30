#ifndef TRANSFER_H
#define TRANSFER_H

#include <QDialog>
#include "account.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>

namespace Ui {
class Transfer;
}

class Transfer : public QDialog
{
    Q_OBJECT

public:
    explicit Transfer(QWidget *parent = nullptr,Account *account = nullptr);
    ~Transfer();
    void function();
    void on_credit_clicked();
    void on_saving_clicked();

private:
    Ui::Transfer *ui;
    Account *account;
    QLineEdit *aLEd,*idld;
    QLabel *albl,*idlb;
    QPushButton *qp;
    QRadioButton *credit,*saving;
};

#endif // TRANSFER_H
