#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <iostream>
#include <cstring>
#include "date.h"
#include "account.h"
#include <iomanip>

using namespace std;

class Employee {
public:
    Employee(const string &name, const string &id, const string &phoneNumber, const string &employeeId,
             const string &password);

public:
    void setName(const string &name);

    void setId(const string &id);

    void setPhoneNumber(const string &phoneNumber);

    void setEmployeeId(const string &employeeId);

    void setPassword(const string &password);

private:
    string name;//姓名
    string ID; //身份证
    string phoneNumber;   //手机号
    string EmployeeID;   //职工号
    string password;  //登录密码
public:
    int createAccount(Date date,int choice,string _name,string _id,string _pass,string _phone,double _balance,double _rate);  //开户
    int closeAccount(int choice,string _name,string _id,string _pass);  //销户
    int queryAccount(int choice,string _name,string _id,string _pass,string& _message);  //查询账户

    const string &getName() const;

    const string &getId() const;

    const string &getPhoneNumber() const;

    const string &getEmployeeId() const;

    const string &getPassword() const;

    static Employee * getEmployee(const string &id, const string &pass);
};
CreditAccount * getCreditByID(const string &id);  //查询活期账号是否存在
SavingAccount *getSavingByID(const string &id);  //查询储蓄账号是否存在
bool deleteAccount(int choice, const string &id);  //从文件删除账号
string show(int choice, const string &id); //展示账号信息
#endif // EMPLOYEE_H
