#include "eclose.h"
#include "ui_eclose.h"
#include <QMessageBox>

Eclose::Eclose(QWidget *parent,Employee *employee) :
    QDialog(parent),
    ui(new Ui::Eclose),
    employee(employee)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("Close"));

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

    closeBtn = new QPushButton(this);
    closeBtn->move(80,200);
    closeBtn->setText("销户");

    exitBtn = new QPushButton(this);
    exitBtn->move(170,200);
    exitBtn->setText("退出");

    credit = new QRadioButton(this);
    credit->move(80,170);
    credit->setText("credit");
    credit->setChecked(true);

    saving = new QRadioButton(this);
    saving->move(150,170);
    saving->setText("saving");
    saving->setChecked(false);


    connect(closeBtn,&QPushButton::clicked,this,&Eclose::function);
    connect(exitBtn,&QPushButton::clicked,this,&Eclose::close);
    connect(credit,&QRadioButton::clicked,this,&Eclose::on_credit_clicked);
    connect(saving,&QRadioButton::clicked,this,&Eclose::on_saving_clicked);

}

Eclose::~Eclose()
{
    delete ui;
}

void Eclose::on_credit_clicked(){
    if(credit->isChecked()){
        saving->setChecked(false);
    }else{
        saving->setChecked(true);
    }
}

void Eclose::on_saving_clicked(){
    if(saving->isChecked()){
        credit->setChecked(false);
    }else{
        credit->setChecked(true);
    }
}

void Eclose::function(){
    int choice;
    string _name,_id,_pass;
    if(credit->isChecked()) {
        choice = 1;
    }
    else{
        choice = 2;
    }

    _name = userNameLEd->text().toStdString();
    _id = IDLEd->text().toStdString();
    _pass = pwdLEd->text().toStdString();

    int status = employee->closeAccount(choice,_name,_id,_pass);

    if(status==1){
        QMessageBox::information(this,tr("警告！"),tr("该账户已被关闭！"));
    }else if(status == 2){
        QMessageBox::information(this,tr("警告！"),tr("密码或姓名错误！"));
    }else{
        QMessageBox::information(this,tr("成功！"),tr("销户成功！"));
    }
    this->close();
}
