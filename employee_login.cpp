#include "employee_login.h"
#include "ui_employee_login.h"
#include <QMessageBox>

employee_login::employee_login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::employee_login)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("登录界面"));

    //IDLabel
    IDLbl = new QLabel(this);   //new一个标签对象
    IDLbl->move(70,80);         //移动到(70,80)位置(Label左上角坐标，相对于父窗体)
    IDLbl->setText("employeeID:");  //设置标签文本

    //ID输入框
    IDLEd = new QLineEdit(this);
    IDLEd->move(120,80);
    IDLEd->setPlaceholderText(tr("请输入ID!"));//占位符

    //密码Label
    pwdLbl = new QLabel(this);
    pwdLbl->move(70,130);
    pwdLbl->setText("密码:");

    //密码输入框
    pwdLEd = new QLineEdit(this);
    pwdLEd->move(120,130);
    pwdLEd->setPlaceholderText("请输入密码!");
    pwdLEd->setEchoMode(QLineEdit::Password);//输入的密码以圆点显示

    //登录按钮
    loginBtn = new QPushButton(this);
    loginBtn->move(80,200);
    loginBtn->setText("登录");

    //退出按钮
    exitBtn = new QPushButton(this);
    exitBtn->move(170,200);
    exitBtn->setText("退出");

    //单击登录按钮时 执行 LoginForm::login 槽函数(自定义)；单击退出按钮时 执行 LoginForm::close 槽函数(窗体的关闭函数，不用自己写)
    connect(loginBtn,&QPushButton::clicked,this,&employee_login::login);
    connect(exitBtn,&QPushButton::clicked,this,&employee_login::close);
}

employee_login::~employee_login()
{
    delete ui;
}

void employee_login::login()
{
    string employeeID = IDLEd->text().toStdString();
    string password = pwdLEd->text().toStdString();
    //获得userNameLEd输入框的文本：userNameLEd->text()；
    //trimmed()去掉前后空格
    //tr()函数，防止设置中文时乱码
    if(Employee::getEmployee(employeeID,password)!=nullptr)
    {
        eservice = new employee_service(this,Employee::getEmployee(employeeID,password));
        eservice->show();
        this->close();
    }
    else
    {                              //标题              内容                OK按钮
       QMessageBox::warning(this, tr("警告！"),tr("ID或密码错误！"),QMessageBox::Yes);

    // 清空输入框内容
       IDLEd->clear();
       pwdLEd->clear();

       //光标定位
       IDLEd->setFocus();
    }
}
