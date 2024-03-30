#include "withdraw.h"
#include "ui_withdraw.h"
#include <time.h>
#include "date.h"
#include <QMessageBox>

Withdraw::Withdraw(QWidget *parent,Account *account) :
    QDialog(parent),
    ui(new Ui::Withdraw),
    account(account)
{
    ui->setupUi(this);
    this->setWindowTitle("Withdraw");
    this->setFixedSize(200,100);

    albl = new QLabel(this);
    albl->move(20,25);
    albl->setText("取款金额:");

    aLEd = new QLineEdit(this);
    aLEd->move(70,25);
    aLEd->setPlaceholderText("请输入金额:");

    qp = new QPushButton(this);
    qp->setText("确认");
    qp->move(50,50);

    connect(qp,&QPushButton::clicked,this,&Withdraw::function);

}

Withdraw::~Withdraw()
{
    delete ui;
}
void Withdraw::function()
{
    time_t now = time(nullptr);
    tm *tm_t = localtime(&now);
    Date date(tm_t->tm_year+1900,tm_t->tm_mon+1,tm_t->tm_mday);
    double num = aLEd->text().toDouble();
    account->withdraw(date,num);
    this->close();
    QMessageBox::information(this,tr("成功！"),tr("取款成功！"));
}
