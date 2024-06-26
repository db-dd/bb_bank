#include "account_login.h"
#include <QMessageBox>

LoginForm::LoginForm(QDialog *parent) :
    QDialog(parent)
{
    //设置窗体标题
    this->setWindowTitle(tr("登录界面"));

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

    //登录按钮
    loginBtn = new QPushButton(this);
    loginBtn->move(80,200);
    loginBtn->setText("登录");

    //退出按钮
    exitBtn = new QPushButton(this);
    exitBtn->move(170,200);
    exitBtn->setText("退出");

    //单击登录按钮时 执行 LoginForm::login 槽函数(自定义)；单击退出按钮时 执行 LoginForm::close 槽函数(窗体的关闭函数，不用自己写)
    connect(loginBtn,&QPushButton::clicked,this,&LoginForm::login);
    connect(exitBtn,&QPushButton::clicked,this,&LoginForm::close);
    connect(credit,&QRadioButton::clicked,this,&LoginForm::on_credit_clicked);
    connect(saving,&QRadioButton::clicked,this,&LoginForm::on_saving_clicked);

}

void LoginForm::login()
{
    //获得userNameLEd输入框的文本：userNameLEd->text()；
    //trimmed()去掉前后空格
    //tr()函数，防止设置中文时乱码
    if(credit->isChecked() && Account::getAccount(1,userNameLEd->text().toStdString(),IDLEd->text().toStdString(),pwdLEd->text().toStdString()) != nullptr)
    {
        account = Account::getAccount(1,userNameLEd->text().toStdString(),IDLEd->text().toStdString(),pwdLEd->text().toStdString());
        aservice = new account_service(this,account);
        aservice->show();
        this->close();
    }
    else if(saving->isChecked() && Account::getAccount(2,userNameLEd->text().toStdString(),IDLEd->text().toStdString(),pwdLEd->text().toStdString()) != nullptr)
    {
        account = Account::getAccount(2,userNameLEd->text().toStdString(),IDLEd->text().toStdString(),pwdLEd->text().toStdString());
        aservice = new account_service(this,account);
        aservice->show();
        this->close();
    }
    else
    {                              //标题              内容                OK按钮
       QMessageBox::warning(this, tr("警告！"),tr("用户名或密码错误！"),QMessageBox::Yes);

    // 清空输入框内容
       userNameLEd->clear();
       IDLEd->clear();
       pwdLEd->clear();

       //光标定位
       userNameLEd->setFocus();
    }
}

void LoginForm::on_credit_clicked(){
    if(credit->isChecked()){
        saving->setChecked(false);
    }else{
        saving->setChecked(true);
    }
}

void LoginForm::on_saving_clicked(){
    if(saving->isChecked()){
        credit->setChecked(false);
    }else{
        credit->setChecked(true);
    }
}
