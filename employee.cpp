#include "employee.h"
#include <regex>
#include <QString>

const string &Employee::getName() const {
    return name;
}

const string &Employee::getId() const {
    return ID;
}

const string &Employee::getPhoneNumber() const {
    return phoneNumber;
}

const string &Employee::getEmployeeId() const {
    return EmployeeID;
}

const string &Employee::getPassword() const {
    return password;
}

void Employee::setName(const string &name) {
    Employee::name = name;
}

void Employee::setId(const string &id) {
    ID = id;
}

void Employee::setPhoneNumber(const string &phoneNumber) {
    Employee::phoneNumber = phoneNumber;
}

void Employee::setEmployeeId(const string &employeeId) {
    EmployeeID = employeeId;
}

void Employee::setPassword(const string &password) {
    Employee::password = password;
}

bool CheckID(string ID_num)/*身份证校验*/
{
    int weight[]={7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2};
    char validate[]={'1','0','X','9','8','7','6','5','4','3','2'};
    int sum = 0;
    int mode = 0;
    int i = 0;
    int length = ID_num.length();
    if(length == 18)
    {
        for(i=0;i<length-1;i++)
            sum = sum + (ID_num[i] - '0') * weight[i];
        mode = sum % 11;
        if (validate[mode] == ID_num[17])
            return true;
    }
    return false;
}

bool checkPhone(const string &phone)
{
    bool temp = false;
    regex e("^(13[0-9]|14[01456879]|15[0-35-9]|16[2567]|17[0-8]|18[0-9]|19[0-35-9])\\d{8}$");
    if (regex_match(phone,e)){
        temp = true;
    }
    return temp;
}

int Employee::createAccount(Date date,int choice,string _name,string _id,string _pass,string _phone,double _balance,double _rate) {
    if(choice == 1){

        //判断该身份证是否已注册过
        if(getCreditByID(_id) != nullptr) {
            //cout << "account already exists!" << endl;
            return 1;
        }

        if(!CheckID(_id)){
            //cout << "the id is invalid!" <<endl;
            return 2;
        }

        if(!checkPhone(_phone)){
            //cout << "the phone is invalid!" <<endl;
            return 3;
        }
        ofstream outfile;
        outfile.open("F:/qt_workplace/bb_bank/credit.txt", ios::app);
        outfile <<setiosflags(ios::left) << setw(10) << _name << setw(20) << _id << setw(14) << _phone << setw(14) << _pass << setw(10) << _balance
        << date.getYear() << " " << date.getMonth() << " " << date.getDay() << "     " <<date.getYear() << " " << date.getMonth() << " " << date.getDay() << endl;
        outfile.close();
        return 4;
    } else if (choice == 2){

        //判断该身份证是否已被注册过
        if(getSavingByID(_id) != nullptr) {
            return 1;
        }

        if(!CheckID(_id)){
            return 2;
        }

        if(!checkPhone(_phone)){
            return 3;
        }
        double _interest = 0;
        ofstream outfile;
        outfile.open("F:/qt_workplace/bb_bank/saving.txt", ios::app);
        outfile <<setiosflags(ios::left) << setw(10) << _name << setw(20) << _id << setw(14) << _phone << setw(14) << _pass << setw(10) << _balance
                << date.getYear() << " " << date.getMonth() << " " << date.getDay() << "     " <<date.getYear() << " " << date.getMonth() << " " << date.getDay() << "     "
                << setw(6) << _rate << setw(10) << _interest << endl;
        outfile.close();
        return 4;
    }
    return 4;
}

int Employee::closeAccount(int choice,string _name,string _id,string _pass) {
    if(choice == 1){
//        string _name, _id, _pass;
//        cout << "input id and name:" << endl;
//        cin >> _id >> _name;
        //判断账号是否存在
        CreditAccount * creditAccount;
        creditAccount = getCreditByID(_id);
        if(creditAccount == nullptr) {
            //cout << "account already close!" << endl;
            return 1;
        }
//        cout << "input password:" << endl;
//        cin >> _pass;
        if(_pass == creditAccount->getPassword() && _name == creditAccount->getName() && _id == creditAccount->getId()){
            deleteAccount(1, _id);
            return 3;
        } else {
            //cout << "password or name wrong!" << endl;
            return 2;
        }
    }else if(choice == 2){
//        string _name, _id, _pass;
//        cout << "input id and name:" << endl;
//        cin >> _id >> _name;
        //判断账号是否存在
        SavingAccount * savingAccount;
        savingAccount = getSavingByID(_id);
        if(savingAccount == nullptr) {
//            cout << "account already close!" <<endl;
            return 1;
        }
//        cout << "input password:" << endl;
//        cin >> _pass;
        if(_pass == savingAccount->getPassword() && _name == savingAccount->getName() && _id == savingAccount->getId()){
            deleteAccount(2,_id);
            return 3;
        } else {
//            cout << "password or name wrong!" << endl;
            return 2;
        }
    }
    return 3;
}

int Employee::queryAccount(int choice,string _name,string _id,string _pass,string& _message) {
    if ( choice == 2 ) {
        //判断账号是否存在
        SavingAccount * savingAccount;
        savingAccount = getSavingByID(_id);
        if(savingAccount == nullptr){
           // cout << "no such account you want!" <<endl;
            return 1;
        }
        if(_pass == savingAccount->getPassword() && _name == savingAccount->getName() && _id == savingAccount->getId()){
            _message = show(2,_id);
        }else {
            //cout << "password or name is wrong!" << endl;
            return 2;
        }
    }else if ( choice == 1 ) {
        //判断账号是否存在
        CreditAccount * creditAccount;
        creditAccount = getCreditByID(_id);
        if(creditAccount == nullptr){
            //cout << "no such account you want!" <<endl;
            return 1;
        }
        if(_pass == creditAccount->getPassword() && _name == creditAccount->getName() && _id == creditAccount->getId()){
            _message = show(1,_id);
        }else {
            //cout << "password or name is wrong!" <<endl;
            return 2;
        }
    }
    return 3;
}

Employee *Employee::getEmployee(const string &id, const string &pass) {
    char buf[MAX_LINE];
    ifstream myfile;
    myfile.open("F:/qt_workplace/bb_bank/employee.txt", ios::in);
    if(!myfile.is_open()){
        cout << "can not read account" << endl;
        return nullptr;
    }
    for(int i = 0; i < 5; i++) myfile >> buf;  //略过第一行
    string _name;  //姓名
    string _id; //身份证
    string _phoneNumber;   //手机号
    string _employeeID;  //职工号
    string _password;  //登录密码
    while(myfile >> buf) {
        _name = buf;
        myfile >> _id;
        myfile >> _phoneNumber;
        myfile >> _employeeID;
        myfile >> _password;
        if (_employeeID == id && pass == _password) {
            auto * employee = new Employee(_name, _id, _phoneNumber, _employeeID, _password);
            return employee;
        }
    }
    return nullptr;
}

Employee::Employee(const string &name, const string &id, const string &phoneNumber, const string &employeeId,
                   const string &password) : name(name), ID(id), phoneNumber(phoneNumber), EmployeeID(employeeId),
                                             password(password) {

}

CreditAccount * getCreditByID(const string &id)  //查询活期账号是否存在
{
    char buf[MAX_LINE];
    ifstream myfile;
    myfile.open("F:/qt_workplace/bb_bank/credit.txt", ios::in);
    if(!myfile.is_open()){
        cout << "can not read account" << endl;
        return nullptr;
    }
    for(int i = 0; i < 7; i++) myfile >> buf;  //略过第一行
    string _name;  //姓名
    string _id; //身份证
    string _phoneNumber;   //手机号
    string _password;  //登录密码
    double _balance;
    int  year, month, day;
    while(myfile >> buf) {
        _name = buf;
        myfile >> _id;
        myfile >> _phoneNumber;
        myfile >> _password;
        myfile >> buf;
        _balance = atof(buf);
        myfile >> year;
        myfile >> month;
        myfile >> day;
        Date _lastDeposit(year, month, day);//上一次存款日期
        myfile >> year;
        myfile >> month;
        myfile >> day;
        Date _lastWithdraw(year, month, day);   //上一次取款日期
        if (id == _id) {
            auto * creditAccount = new CreditAccount(_name, _id, _phoneNumber, _password, _balance, _lastDeposit, _lastWithdraw);
            return creditAccount;
        }
    }
    return nullptr;
}

SavingAccount *getSavingByID(const string &id)  //查询储蓄账号是否存在
{
    char buf[MAX_LINE];
    ifstream myfile;
    myfile.open("F:/qt_workplace/bb_bank/saving.txt", ios::in);
    if(!myfile.is_open()){
        cout << "can not read account" << endl;
        return nullptr;
    }
    for(int i = 0; i < 9; i++) myfile >> buf;  //略过第一行
    string _name;  //姓名
    string _id; //身份证
    string _phoneNumber;   //手机号
    string _password;  //登录密码
    double _balance;
    int  year, month, day;
    double _rate, _interest;
    while(myfile >> buf) {
        _name = buf;
        myfile >> _id;
        myfile >> _phoneNumber;
        myfile >> _password;
        myfile >> buf;
        _balance = atof(buf);
        myfile >> year;
        myfile >> month;
        myfile >> day;
        Date _lastDeposit(year, month, day);//上一次存款日期
        myfile >> year;
        myfile >> month;
        myfile >> day;
        Date _lastWithdraw(year, month, day);   //上一次取款日期
        myfile >> _rate; myfile >> _interest;
        if (id == _id) {
            auto * savingAccount = new SavingAccount(_name, _id, _phoneNumber, _password, _balance, _lastDeposit, _lastWithdraw, _rate, _interest);
            return savingAccount;
        }
    }
    return nullptr;
}

bool deleteAccount(int choice, const string &id)  //从文件删除账号
{
    char buf[MAX_LINE];
    int userNum = 0;
    ofstream outfile;
    ifstream myfile;
    if(choice == 2){
        SavingAccount savingAccount[MAX_USER];
        myfile.open("F:/qt_workplace/bb_bank/saving.txt", ios::in);
        if(!myfile.is_open()){
            cout << "can not read account" << endl;
            return false;
        }
        for(int i = 0; i < 9; i++) myfile >> buf;  //略过第一行
        string _name;  //姓名
        string _id; //身份证
        string _phoneNumber;   //手机号
        string _password;  //登录密码
        double _balance;
        int  year, month, day;
        double _rate, _interest;
        while(myfile >> buf) {
            _name = buf;
            myfile >> _id;
            myfile >> _phoneNumber;
            myfile >> _password;
            myfile >> buf;
            _balance = atof(buf);
            myfile >> year;
            myfile >> month;
            myfile >> day;
            Date _lastDeposit(year, month, day);//上一次存款日期
            myfile >> year;
            myfile >> month;
            myfile >> day;
            Date _lastWithdraw(year, month, day);   //上一次取款日期
            myfile >> _rate; myfile >> _interest;
            if (_id != id) {
                savingAccount[userNum++] = SavingAccount(_name, _id, _phoneNumber, _password, _balance, _lastDeposit, _lastWithdraw, _rate, _interest);
            }
        }
        myfile.close();
        outfile.open("F:/qt_workplace/bb_bank/saving.txt", ios::out);
        outfile <<setiosflags(ios::left) << setw(10) << "name" << setw(20) << "ID" << setw(14) << "phone"
        << setw(14) << "password" << setw(10) << "balance" << setw(14) << "lastDeposit" << setw(14) << "lastWithdraw"
        << setw(6) << "rate" << setw(10) << "interest" << endl;
        for(int i = 0; i < userNum; i++){
            outfile <<setiosflags(ios::left) << setw(10) << savingAccount[i].getName() << setw(20) << savingAccount[i].getId() << setw(14)
            << savingAccount[i].getPhoneNumber() << setw(14) << savingAccount[i].getPassword() << setw(10) << savingAccount[i].getBalance()
            << savingAccount[i].getLastDeposit().getYear() << " " << savingAccount[i].getLastDeposit().getMonth() << " "  << savingAccount[i].getLastDeposit().getDay() << "     "
            << savingAccount[i].getLastWithdraw().getYear() << " " << savingAccount[i].getLastWithdraw().getMonth() << " " << savingAccount[i].getLastWithdraw().getDay() << "     "
            << setw(6) << savingAccount[i].getRate() << setw(10) << savingAccount[i].getInterest() << endl;
        }
        outfile.close();
    } else if(choice == 1){
        CreditAccount creditAccount[MAX_USER];
        myfile.open("F:/qt_workplace/bb_bank/credit.txt", ios::in);
        if(!myfile.is_open()){
            cout << "can not read account" << endl;
            return false;
        }
        for(int i = 0; i < 7; i++) myfile >> buf;  //略过第一行
        string _name;  //姓名
        string _id; //身份证
        string _phoneNumber;   //手机号
        string _password;  //登录密码
        double _balance;
        int  year, month, day;
        while(myfile >> buf) {
            _name = buf;
            myfile >> _id;
            myfile >> _phoneNumber;
            myfile >> _password;
            myfile >> buf;
            _balance = atof(buf);
            myfile >> year;
            myfile >> buf;
            month = atoi(buf);
            myfile >> day;
            Date _lastDeposit(year, month, day);//上一次存款日期
            myfile >> year;
            myfile >> buf;
            month = atoi(buf);
            myfile >> day;
            Date _lastWithdraw(year, month, day);   //上一次取款日期
            if (_id != id) {
                creditAccount[userNum++] = CreditAccount(_name, _id, _phoneNumber, _password, _balance, _lastDeposit, _lastWithdraw);
            }
        }
        myfile.close();
        outfile.open("F:/qt_workplace/bb_bank/credit.txt", ios::out);
        outfile <<setiosflags(ios::left) << setw(10) << "name" << setw(20) << "ID" << setw(14) << "phone"
                << setw(14) << "password" << setw(10) << "balance" << setw(14) << "lastDeposit" << setw(14) << "lastWithdraw" << endl;
        for(int i = 0; i < userNum; i++){
            outfile <<setiosflags(ios::left) << setw(10) << creditAccount[i].getName() << setw(20) << creditAccount[i].getId() << setw(14)
                    << creditAccount[i].getPhoneNumber() << setw(14) << creditAccount[i].getPassword() << setw(10) << creditAccount[i].getBalance()
                    << creditAccount[i].getLastDeposit().getYear() << " " << creditAccount[i].getLastDeposit().getMonth() << " " << creditAccount[i].getLastDeposit().getDay() << "     "
                    << creditAccount[i].getLastWithdraw().getYear() << " " << creditAccount[i].getLastWithdraw().getMonth() << " " << creditAccount[i].getLastWithdraw().getDay() << "     "<< endl;
        }
        outfile.close();
    }


    return true;

}

string show(int choice, const string &id) {
    ifstream ifile ;
    char buf[MAX_LINE];
    string temp;
    if(choice == 1){//credit
        CreditAccount creditAccount;
        ifile.open("F:/qt_workplace/bb_bank/credit.txt",ios::in);
        for(int i = 0; i < 7; i++) ifile >> buf; //略过第一行
        string _name;  //姓名
        string _id; //身份证
        string _phoneNumber;   //手机号
        string _password;  //登录密码
        double _balance;
        int  year, month, day;
        while(ifile >> buf) {
            _name = buf;
            ifile >> _id;
            ifile >> _phoneNumber;
            ifile >> _password;
            ifile >> buf;
            _balance = atof(buf);
            ifile >> year;
            ifile >> buf;
            month = atoi(buf);
            ifile >> day;
            Date _lastDeposit(year, month, day);//上一次存款日期
            ifile >> year;
            ifile >> buf;
            month = atoi(buf);
            ifile >> day;
            Date _lastWithdraw(year, month, day);   //上一次取款日期
            if (_id == id) {
                creditAccount = CreditAccount(_name, _id, _phoneNumber, _password, _balance, _lastDeposit, _lastWithdraw);
                break;
            }
        }
        //cout << "name      ID                  phone         password      balance   lastDeposit    lastWithdraw" << endl;
        //cout <<setiosflags(ios::left) << setw(10) << creditAccount.getName() << setw(20) << _id << setw(14)
         //       << creditAccount.getPhoneNumber() << setw(14) << creditAccount.getPassword() << setw(10) << creditAccount.getBalance()
         //       << creditAccount.getLastDeposit().getYear() << " " << creditAccount.getLastDeposit().getMonth() << " " << creditAccount.getLastDeposit().getDay() << "      "
         //       << creditAccount.getLastWithdraw().getYear() << " " << creditAccount.getLastWithdraw().getMonth() << " " << creditAccount.getLastWithdraw().getDay() << "     "<< endl;
        temp = "name: ";
        temp+=creditAccount.getName();temp+=",ID: ";temp+=_id;temp+=",phone: ";temp+=creditAccount.getPhoneNumber();
        temp+=",password: ";temp+=creditAccount.getPassword();temp+=",balance: ";temp+=QString::number(creditAccount.getBalance(),10,2).toStdString();
        temp+=",lastDeposit: ";temp+=QString("%1").arg(creditAccount.getLastDeposit().getYear()).toStdString();temp+=" ";
                               temp+=QString("%1").arg(creditAccount.getLastDeposit().getMonth()).toStdString();temp+=" ";
                               temp+=QString("%1").arg(creditAccount.getLastDeposit().getDay()).toStdString();
        temp+=",lastWithdraw: ";temp+=QString("%1").arg(creditAccount.getLastWithdraw().getYear()).toStdString();temp+=" ";
                                temp+=QString("%1").arg(creditAccount.getLastWithdraw().getMonth()).toStdString();temp+=" ";
                                temp+=QString("%1").arg(creditAccount.getLastWithdraw().getDay()).toStdString();
        ifile.close();
    }else if (choice == 2){//saving
        SavingAccount savingAccount;
        ifile.open("F:/qt_workplace/bb_bank/saving.txt", ios::in);
        for(int i = 0; i < 9; i++) ifile >> buf;  //略过第一行
        string _name;  //姓名
        string _id; //身份证
        string _phoneNumber;   //手机号
        string _password;  //登录密码
        double _balance;
        int  year, month, day;
        double _rate, _interest;
        while(ifile >> buf) {
            _name = buf;
            ifile >> _id;
            ifile >> _phoneNumber;
            ifile >> _password;
            ifile >> buf;
            _balance = atof(buf);
            ifile >> year;
            ifile >> month;
            ifile >> day;
            Date _lastDeposit(year, month, day);//上一次存款日期
            ifile >> year;
            ifile >> month;
            ifile >> day;
            Date _lastWithdraw(year, month, day);   //上一次取款日期
            ifile >> _rate; ifile >> _interest;
            if (_id == id) {
                savingAccount = SavingAccount(_name, _id, _phoneNumber, _password, _balance, _lastDeposit, _lastWithdraw, _rate, _interest);
                break;
            }
        }/*
        cout <<"name      ID                  phone         password      balance   lastDepost    lastWithdraw    rate  interest" << endl;
        cout <<setiosflags(ios::left) << setw(10) << savingAccount.getName() << setw(20) << savingAccount.getId() << setw(14)
               << savingAccount.getPhoneNumber() << setw(14) << savingAccount.getPassword() << setw(10) << savingAccount.getBalance()
               << savingAccount.getLastDeposit().getYear() << " " << savingAccount.getLastDeposit().getMonth() << " "  << savingAccount.getLastDeposit().getDay() << "      "
               << savingAccount.getLastWithdraw().getYear() << " " << savingAccount.getLastWithdraw().getMonth() << " " << savingAccount.getLastWithdraw().getDay() << "      "
               << setw(6) << savingAccount.getRate() << setw(10) << savingAccount.getInterest() << endl;*/
        temp = "name: ";
        temp+=savingAccount.getName();temp+=",ID: ";temp+=_id;temp+=",phone: ";temp+=savingAccount.getPhoneNumber();
        temp+=",password: ";temp+=savingAccount.getPassword();temp+=",balance: ";temp+=QString::number(savingAccount.getBalance(),10,2).toStdString();
        temp+=",lastDeposit: ";temp+=QString("%1").arg(savingAccount.getLastDeposit().getYear()).toStdString();temp+=" ";
                               temp+=QString("%1").arg(savingAccount.getLastDeposit().getMonth()).toStdString();temp+=" ";
                               temp+=QString("%1").arg(savingAccount.getLastDeposit().getDay()).toStdString();
        temp+=",lastWithdraw: ";temp+=QString("%1").arg(savingAccount.getLastWithdraw().getYear()).toStdString();temp+=" ";
                                temp+=QString("%1").arg(savingAccount.getLastWithdraw().getMonth()).toStdString();temp+=" ";
                                temp+=QString("%1").arg(savingAccount.getLastWithdraw().getDay()).toStdString();
        temp+=",rate: ";temp+=QString::number(savingAccount.getRate(),10,2).toStdString();
        temp+=",insterest: ";temp+=QString::number(savingAccount.getInterest(),10,2).toStdString();
        ifile.close();
    }
    return temp;
}
