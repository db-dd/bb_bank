#include "create.h"
#include "ui_create.h"
#include <QMessageBox>
#include <time.h>

Create::Create(QWidget *parent,Employee *employee) :
    QDialog(parent),
    ui(new Ui::Create),
    employee(employee)
{
    ui->setupUi(this);

    //设置窗体标题
    this->setWindowTitle(tr("Create"));

    this->setFixedSize(400,400);

    //用户名Label
    userNameLbl = new QLabel(this);   //new一个标签对象
    userNameLbl->move(70,80);         //移动到(70,80)位置(Label左上角坐标，相对于父窗体)
    userNameLbl->setText("姓名:");  //设置标签文本

    //用户名输入框
    userNameLEd = new QLineEdit(this);
    userNameLEd->move(120,80);
    userNameLEd->setPlaceholderText(tr("请输入姓名!"));//占位符

    IDLbl = new QLabel(this);
    IDLbl->move(70,105);
    IDLbl->setText("身份证:");

    IDLEd = new QLineEdit(this);
    IDLEd->move(120,105);
    IDLEd->setPlaceholderText("请输入身份证!");

    //密码Label
    pwdLbl = new QLabel(this);
    pwdLbl->move(70,130);
    pwdLbl->setText("密码:");

    //密码输入框
    pwdLEd = new QLineEdit(this);
    pwdLEd->move(120,130);
    pwdLEd->setPlaceholderText("请输入密码!");
    pwdLEd->setEchoMode(QLineEdit::Password);//输入的密码以圆点显示

    credit = new QRadioButton(this);
    credit->move(80,170);
    credit->setText("credit");
    credit->setChecked(true);

    saving = new QRadioButton(this);
    saving->move(150,170);
    saving->setText("saving");
    saving->setChecked(false);

    phoneLbl = new QLabel(this);
    phoneLbl->move(70,205);
    phoneLbl->setText("联系方式:");

    phoneLEd = new QLineEdit(this);
    phoneLEd->move(120,205);
    phoneLEd->setPlaceholderText("请输入手机号!");

    balanceLbl = new QLabel(this);
    balanceLbl->move(70,230);
    balanceLbl->setText("金额:");

    balanceLEd = new QLineEdit(this);
    balanceLEd->move(120,230);
    balanceLEd->setPlaceholderText("请输入金额!");

    rateLbl = new QLabel(this);
    rateLbl->move(70,255);
    rateLbl->setText("利率:");

    rateLEd = new QLineEdit(this);
    rateLEd->move(120,255);
    rateLEd->setPlaceholderText("请输入利率!");

    queryBtn = new QPushButton(this);
    queryBtn->move(80,280);
    queryBtn->setText("创建");

    exitBtn = new QPushButton(this);
    exitBtn->move(170,280);
    exitBtn->setText("退出");

    connect(queryBtn,&QPushButton::clicked,this,&Create::function);
    connect(exitBtn,&QPushButton::clicked,this,&Create::close);
    connect(credit,&QRadioButton::clicked,this,&Create::on_credit_clicked);
    connect(saving,&QRadioButton::clicked,this,&Create::on_saving_clicked);
}

Create::~Create()
{
    delete ui;
}

void Create::on_credit_clicked(){
    if(credit->isChecked()){
        saving->setChecked(false);
    }else{
        saving->setChecked(true);
    }
}

void Create::on_saving_clicked(){
    if(saving->isChecked()){
        credit->setChecked(false);
    }else{
        credit->setChecked(true);
    }
}

void Create::function(){
    int choice;
    double _balance,_rate;
    string _name,_id,_pass,_message,_phone;
    if(credit->isChecked()) {
        choice = 1;
        _rate = 0;
    }
    else{
        choice = 2;
        _rate = rateLEd->text().toDouble();
    }

    _name = userNameLEd->text().toStdString();
    _id = IDLEd->text().toStdString();
    _pass = pwdLEd->text().toStdString();
    _phone = phoneLEd->text().toStdString();
    _balance = balanceLEd->text().toDouble();

    time_t now = time(nullptr);
    tm *tm_t = localtime(&now);
    Date date(tm_t->tm_year+1900,tm_t->tm_mon+1,tm_t->tm_mday);

    int status = employee->createAccount(date,choice,_name,_id,_pass,_phone,_balance,_rate);

    if(status==1){
        QMessageBox::information(this,tr("警告！"),tr("该id已注册！"));
    }else if(status == 2){
        QMessageBox::information(this,tr("警告！"),tr("非法id！"));
    }else if(status == 3){
        QMessageBox::information(this,tr("警告！"),tr("非法手机号！"));
    }else{
        QMessageBox::information(this,tr("成功！"),tr("创建成功！"));
    }
    this->close();
}
