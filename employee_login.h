#ifndef EMPLOYEE_LOGIN_H
#define EMPLOYEE_LOGIN_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "employee.h"
#include "employee_service.h"

namespace Ui {
class employee_login;
}

class employee_login : public QDialog
{
    Q_OBJECT

public:
    explicit employee_login(QWidget *parent = nullptr);
    ~employee_login();
    void login();

private:
    Ui::employee_login *ui;
    QLabel *IDLbl;         //"用户名"标签
    QLabel *pwdLbl;              //"密码"标签
    QLineEdit *IDLEd;      //用户名编辑行
    QLineEdit *pwdLEd;           //密码编辑行
    QPushButton *loginBtn;       //登录按钮
    QPushButton *exitBtn;        //退出按钮
    Employee *employee;
    employee_service *eservice;
};

#endif // EMPLOYEE_LOGIN_H
