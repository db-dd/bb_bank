#include "thank.h"
#include "ui_thank.h"

thank::thank(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::thank)
{
    ui->setupUi(this);
    this->setWindowTitle("Thanks");
}

thank::~thank()
{
    delete ui;
}
