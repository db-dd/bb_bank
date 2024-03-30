#include "account.h"
#include <QMessageBox>

const string &Account::getName() const {
    return name;
}

const string &Account::getId() const {
    return ID;
}

const string &Account::getPhoneNumber() const {
    return phoneNumber;
}

const string &Account::getPassword() const {
    return password;
}

double Account::getBalance() const {
    return balance;
}

void Account::setName(const string &name) {
    Account::name = name;
}

void Account::setId(const string &id) {
    ID = id;
}

void Account::setPhoneNumber(const string &phoneNumber) {
    Account::phoneNumber = phoneNumber;
}

void Account::setPassword(const string &password) {
    Account::password = password;
}

void Account::setBalance(double balance) {
    Account::balance = balance;
}

const Date &Account::getLastDeposit() const {
    return lastDeposit;
}

const Date &Account::getLastWithdraw() const {
    return lastWithdraw;
}

Account::Account(const string &name, const string &id, const string &phoneNumber, const string &password,
                 double balance, const Date &lastDeposit, const Date &lastWithdraw) : name(name), ID(id),
                                                                                      phoneNumber(phoneNumber),
                                                                                      password(password),
                                                                                      balance(balance),
                                                                                      lastDeposit(lastDeposit),
                                                                                      lastWithdraw(lastWithdraw) {

}

//查询账号是否存在， 存在则返回对应账号，不存在返回nullptr
Account *Account::getAccount(int choose, const string &n, const string &I, const string &pass) {
    char buf[MAX_LINE];
    ifstream myfile;

    //活期账户
    if(choose == 1){
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
            if (n == _name && I == _id && pass == _password) {
                auto * creditAccount = new CreditAccount(_name, _id, _phoneNumber, _password, _balance, _lastDeposit, _lastWithdraw);
                return creditAccount;
            }
        }
    }
    //储蓄账户
    else if(choose == 2) {
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
            if (n == _name && I == _id && pass == _password) {
                auto * savingAccount = new SavingAccount(_name, _id, _phoneNumber, _password, _balance, _lastDeposit, _lastWithdraw, _rate, _interest);
                return savingAccount;
            }
        }
    }
    else return nullptr;


    return nullptr;
}

void Account::setLastDeposit(const Date &lastDeposit) {
    Account::lastDeposit = lastDeposit;
}

void Account::setLastWithdraw(const Date &lastWithdraw) {
    Account::lastWithdraw = lastWithdraw;
}

void CreditAccount::deposit(Date date, double amount) {
    string money = to_string(amount);
    this->changeValue(1, money, date);
}

void CreditAccount::withdraw(Date date, double amount) {
    string money = to_string(amount);
    this->changeValue(2, money, date);
}

bool CreditAccount::transfer(Date date, double amount,int choice,string id) {
    string money = to_string(amount);
    if(choice == 1){
        CreditAccount * creditAccount = getCreditByiD(id);
        if(creditAccount == nullptr) {
            return false;
        }
        this->changeValue(3, money, date);   //date不会改变
        creditAccount->changeValue(1, money, creditAccount->getLastDeposit());
    } else if(choice ==2 ){
        SavingAccount * savingAccount = getSavingByiD(id);
        if(savingAccount == nullptr) {
            return false;
        }
        this->changeValue(3, money, date);   //date不会改变
        savingAccount->changeValue(1, money, savingAccount->getLastDeposit());
    }
    return true;
}

CreditAccount::CreditAccount(const string &name, const string &id, const string &phoneNumber, const string &password,
                             double balance, const Date &lastDeposit, const Date &lastWithdraw) : Account(name, id,
                                                                                                          phoneNumber,
                                                                                                          password,
                                                                                                          balance,
                                                                                                          lastDeposit,
                                                                                                          lastWithdraw) {}

CreditAccount &CreditAccount::operator=(const CreditAccount &account) {
    this->setName(account.getName());
    this->setId(account.getId());
    this->setPhoneNumber(account.getPhoneNumber());
    this->setPassword(account.getPassword());
    this->setBalance(account.getBalance());
    this->setLastDeposit(account.getLastDeposit());
    this->setLastWithdraw(account.getLastWithdraw());
    return *this;
}


//choice = 1:存款   2：取款    3：转账
bool CreditAccount::changeValue(int choice, string value, Date date) {
    int userNum = 0;
    ifstream myfile;
    char buf[MAX_LINE];
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
        //存款
        if(choice == 1){
            if (_id != this->getId()) {
                creditAccount[userNum++] = CreditAccount(_name, _id, _phoneNumber, _password, _balance, _lastDeposit, _lastWithdraw);
            } else if( _id == this->getId()){
                double money = stof(value);
                this->setBalance(_balance + money);
                creditAccount[userNum++] = CreditAccount(_name, _id, _phoneNumber, _password, _balance + money, date, _lastWithdraw);
            }
        } //取款
        else if (choice == 2){
            if (_id != this->getId()) {
                creditAccount[userNum++] = CreditAccount(_name, _id, _phoneNumber, _password, _balance, _lastDeposit, _lastWithdraw);
            } else if( _id == this->getId()){
                double money = stof(value);
                if(money > _balance){
                    cout << "balance not enough" << endl;
                    creditAccount[userNum++] = CreditAccount(_name, _id, _phoneNumber, _password, _balance, _lastDeposit, _lastWithdraw);
                }else{
                    this->setBalance(_balance - money);
                    creditAccount[userNum++] = CreditAccount(_name, _id, _phoneNumber, _password, _balance - money, _lastDeposit, date);
                }
            }
        } //转账
        else if (choice == 3){
            if (_id != this->getId()) {
                creditAccount[userNum++] = CreditAccount(_name, _id, _phoneNumber, _password, _balance, _lastDeposit, _lastWithdraw);
            } else if( _id == this->getId()){
                double money = stof(value);
                if(money > _balance){
                    cout << "balance not enough" << endl;
                    creditAccount[userNum++] = CreditAccount(_name, _id, _phoneNumber, _password, _balance, _lastDeposit, _lastWithdraw);
                }else{
                    this->setBalance(_balance - money);
                    creditAccount[userNum++] = CreditAccount(_name, _id, _phoneNumber, _password, _balance - money, _lastDeposit, _lastWithdraw);
                }
            }
        }

    }
    myfile.close();
    ofstream outfile;
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
    return true;
}


void SavingAccount::deposit(Date date, double amount) {
    string money = to_string(amount);
    this->changeValue(1, money, date);
}

void SavingAccount::withdraw(Date date, double amount) {
    string money = to_string(amount);
    this->changeValue(2, money, date);
}

bool SavingAccount::transfer(Date date, double amount,int choice,string id) {
    string money = to_string(amount);
    CreditAccount * creditAccount = getCreditByiD(this->getId());  //只能与对应活期账号互转
    if(creditAccount == nullptr) {
        return false;
    }
    this->changeValue(3, money, date);   //date不会改变
    creditAccount->changeValue(1, money, creditAccount->getLastDeposit());
    return true;
}

double SavingAccount::calculateInterest() {
    return 0;
}

SavingAccount::SavingAccount(const string &name, const string &id, const string &phoneNumber, const string &password,
                             double balance, const Date &lastDeposit, const Date &lastWithdraw, double rate,
                             double interest) : Account(name, id, phoneNumber, password, balance, lastDeposit,
                                                        lastWithdraw), rate(rate), interest(interest) {}

double SavingAccount::getRate() const {
    return rate;
}

double SavingAccount::getInterest() const {
    return interest;
}

void SavingAccount::setRate(double rate) {
    SavingAccount::rate = rate;
}

void SavingAccount::setInterest(double interest) {
    SavingAccount::interest = interest;
}

SavingAccount &SavingAccount::operator=(const SavingAccount &account) {
    this->setName(account.getName());
    this->setId(account.getName());
    this->setPhoneNumber(account.getPhoneNumber());
    this->setPassword(account.getPassword());
    this->setBalance(account.getBalance());
    this->setLastDeposit(account.getLastDeposit());
    this->setLastWithdraw(account.getLastWithdraw());
    this->setRate(account.getRate());
    this->setInterest(account.getInterest());
    return *this;
}

//choice = 1:存款   2：取款    3：转账
bool SavingAccount::changeValue(int choice, string value, Date date) {
    int userNum = 0;
    char buf[MAX_LINE];
    SavingAccount savingAccount[MAX_USER];
    ifstream myfile;
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
        //存款
        if(choice == 1){
            if (_id != this->getId()) {
                savingAccount[userNum++] = SavingAccount(_name, _id, _phoneNumber, _password, _balance, _lastDeposit, _lastWithdraw, _rate, _interest);
            } else if( _id == this->getId()){
                double money = stof(value);
                int days1 = date - _lastDeposit, days2 = date - _lastWithdraw;
                if(days1  <= days2){
                    for(int i = 0; i < days1; i++){
                        _interest = (_balance + _interest) * _rate - _balance;  //计算从上次存款开始的利息
                    }

                    savingAccount[userNum++] = SavingAccount(_name, _id, _phoneNumber, _password, _balance + money, date, _lastWithdraw, _rate, _interest);
                }
                else   {
                    for(int i = 0; i < days2; i++){
                        _interest = (_balance + _interest) * _rate - _balance;  //计算从上次取款开始的利息
                    }
                    savingAccount[userNum++] = SavingAccount(_name, _id, _phoneNumber, _password, _balance + money, date, _lastWithdraw, _rate, _interest);
                }
                this->setBalance(_balance + money);
            }
        } //取款
        else if (choice == 2){
            if (_id != this->getId()) {
                savingAccount[userNum++] = SavingAccount(_name, _id, _phoneNumber, _password, _balance, _lastDeposit, _lastWithdraw, _rate, _interest);
            } else if( _id == this->getId()){
                double money = stof(value);
                if(money > _balance){
                    cout << "balance not enough" << endl;
                    savingAccount[userNum++] = SavingAccount(_name, _id, _phoneNumber, _password, _balance, _lastDeposit, _lastWithdraw, _rate, _interest);
                }else{
                    int days1 = date - _lastDeposit, days2 = date - _lastWithdraw;
                    if(days1  <= days2){
                        for(int i = 0; i < days1; i++){
                            _interest = (_balance + _interest) * _rate - _balance;  //计算从上次存款开始的利息
                        }
                        savingAccount[userNum++] = SavingAccount(_name, _id, _phoneNumber, _password, _balance - money, _lastDeposit,date, _rate, _interest);
                    }
                    else   {
                        for(int i = 0; i < days2; i++){
                            _interest = (_balance + _interest) * _rate - _balance;  //计算从上次取款开始的利息
                        }
                        savingAccount[userNum++] = SavingAccount(_name, _id, _phoneNumber, _password, _balance - money, _lastDeposit,date, _rate, _interest);
                    }
                    this->setBalance(_balance - money);

                }
            }
        } //转账
        else if (choice == 3){
            if (_id != this->getId()) {
                savingAccount[userNum++] = SavingAccount(_name, _id, _phoneNumber, _password, _balance, _lastDeposit, _lastWithdraw, _rate, _interest);
            } else if( _id == this->getId()){
                double money = stof(value);
                if(money > _balance){
                    cout << "balance not enough" << endl;
                    savingAccount[userNum++] = SavingAccount(_name, _id, _phoneNumber, _password, _balance, _lastDeposit, _lastWithdraw, _rate, _interest);
                }else{
                    savingAccount[userNum++] = SavingAccount(_name, _id, _phoneNumber, _password, _balance - money, _lastDeposit, _lastWithdraw, _rate, _interest);
                    this->setBalance(_balance - money);
                }
            }
        }
    }
    myfile.close();
    ofstream outfile;
    outfile.open("F:/qt_workplace/bb_bank/saving.txt", ios::out);
    outfile <<setiosflags(ios::left) << setw(10) << "name" << setw(20) << "ID" << setw(14) << "phone"
            << setw(14) << "password" << setw(10) << "balance" << setw(14) << "lastDeposit" << setw(14) << "lastWithdraw"
            << setw(6) << "rate" << setw(10) << "interest" << endl;
    for(int i = 0; i < userNum; i++){
        outfile <<setiosflags(ios::left) << setw(10) << savingAccount[i].getName() << setw(20) << savingAccount[i].getId() << setw(14)
                << savingAccount[i].getPhoneNumber() << setw(14) << savingAccount[i].getPassword() << setw(10) << savingAccount[i].getBalance()
                << savingAccount[i].getLastDeposit().getYear() << " " << savingAccount[i].getLastDeposit().getMonth() << " " << savingAccount[i].getLastDeposit().getDay() << "     "
                << savingAccount[i].getLastWithdraw().getYear() << " " << savingAccount[i].getLastWithdraw().getMonth() << " " << savingAccount[i].getLastWithdraw().getDay() << "     "
                << setw(6) << savingAccount[i].getRate() << setw(10) << savingAccount[i].getInterest() << endl;
    }
    outfile.close();
    return true;
}




CreditAccount * getCreditByiD(const string &id)  //查询活期账号是否存在
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

SavingAccount *getSavingByiD(const string &id)  //查询储蓄账号是否存在
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
