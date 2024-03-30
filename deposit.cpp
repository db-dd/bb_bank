#include "deposit.h"
#include "ui_deposit.h"
#include <time.h>
#include "date.h"
#include <QMessageBox>

Deposit::Deposit(QWidget *parent,Account *account) :
    QDialog(parent),
    ui(new Ui::Deposit),
    account(account)
{
    ui->setupUi(this);
    this->setWindowTitle("Deposit");
    this->setFixedSize(200,100);

    albl = new QLabel(this);
    albl->move(20,25);
    albl->setText("存款金额:");

    aLEd = new QLineEdit(this);
    aLEd->move(70,25);
    aLEd->setPlaceholderText("请输入金额:");

    qp = new QPushButton(this);
    qp->setText("确认");
    qp->move(50,50);

    connect(qp,&QPushButton::clicked,this,&Deposit::function);

}

Deposit::~Deposit()
{
    delete ui;
}
void Deposit::function()
{
    time_t now = time(nullptr);
    tm *tm_t = localtime(&now);
    Date date(tm_t->tm_year+1900,tm_t->tm_mon+1,tm_t->tm_mday);
    double num = aLEd->text().toDouble();
    account->deposit(date,num);
    this->close();
    QMessageBox::information(this,tr("成功！"),tr("存款成功！"));
}
