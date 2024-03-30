#include "employee_service.h"
#include "ui_employee_service.h"
#include <QMessageBox>

employee_service::employee_service(QWidget *parent,Employee *employee) :
    QDialog(parent),
    ui(new Ui::employee_service),
    employee(employee)
{
    ui->setupUi(this);
    string str = employee->getName();
    this->setWindowTitle(QString::fromStdString(str));

    this->setFixedSize(600,400);

    QPixmap pixmap = QPixmap(":/new/prefix1/back.jpg");
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(pixmap));
    this->setPalette(palette);

    Create = new QPushButton(this);
    Create->move(200,100);
    Create->setText("Create");
    Create->setFixedSize(200,30);

    Close = new QPushButton(this);
    Close->move(200,140);
    Close->setText("Close");
    Close->setFixedSize(200,30);

    Query = new QPushButton(this);
    Query->move(200,180);
    Query->setText("Query");
    Query->setFixedSize(200,30);

    connect(Create,&QPushButton::clicked,this,&employee_service::e_create);
    connect(Close,&QPushButton::clicked,this,&employee_service::e_close);
    connect(Query,&QPushButton::clicked,this,&employee_service::e_query);
}

employee_service::~employee_service()
{
    delete ui;
}

void employee_service::e_create()
{
    create = new class Create(this,employee);
    create->show();
}
void employee_service::e_close()
{
    eclose = new class Eclose(this,employee);
    eclose->show();
}
void employee_service::e_query()
{
    query = new class Query(this,employee);
    query->show();
}
