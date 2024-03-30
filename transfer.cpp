#include "transfer.h"
#include "ui_transfer.h"
#include <QMessageBox>

Transfer::Transfer(QWidget *parent,Account *account) :
    QDialog(parent),
    ui(new Ui::Transfer),
    account(account)
{
    ui->setupUi(this);
    this->setWindowTitle("Transfer");
    this->setFixedSize(200,200);

    albl = new QLabel(this);
    albl->move(20,25);
    albl->setText("转账金额:");

    aLEd = new QLineEdit(this);
    aLEd->move(70,25);
    aLEd->setPlaceholderText("请输入金额:");

    credit = new QRadioButton(this);
    credit->move(20,80);
    credit->setText("credit");
    credit->setChecked(true);

    saving = new QRadioButton(this);
    saving->move(70,80);
    saving->setText("saving");
    saving->setChecked(false);

    idlb = new QLabel(this);
    idlb->move(20,125);
    idlb->setText("转账人id:");

    idld = new QLineEdit(this);
    idld->move(70,125);
    idld->setPlaceholderText("请输入id:");

    qp = new QPushButton(this);
    qp->setText("确认");
    qp->move(50,175);

    connect(qp,&QPushButton::clicked,this,&Transfer::function);
    connect(credit,&QRadioButton::clicked,this,&Transfer::on_credit_clicked);
    connect(saving,&QRadioButton::clicked,this,&Transfer::on_saving_clicked);
}

Transfer::~Transfer()
{
    delete ui;
}
void Transfer::on_credit_clicked(){
    if(credit->isChecked()){
        saving->setChecked(false);
    }else{
        saving->setChecked(true);
    }
}

void Transfer::on_saving_clicked(){
    if(saving->isChecked()){
        credit->setChecked(false);
    }else{
        credit->setChecked(true);
    }
}

void Transfer::function()
{
    int choice;
    if(credit->isChecked()) choice=1;
    else choice =2;

    string id = idld->text().toStdString();

    time_t now = time(nullptr);
    tm *tm_t = localtime(&now);
    Date date(tm_t->tm_year+1900,tm_t->tm_mon+1,tm_t->tm_mday);
    double num = aLEd->text().toDouble();

    bool temp = account->transfer(date,num,choice,id);
    this->close();
    if(!temp){
        QMessageBox::information(this,tr("警告！"),tr("用户不存在！"));
    }else{
        QMessageBox::information(this,tr("成功！"),tr("转账成功！"));
    }
}
