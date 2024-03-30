#ifndef THANK_H
#define THANK_H

#include <QDialog>

namespace Ui {
class thank;
}

class thank : public QDialog
{
    Q_OBJECT

public:
    explicit thank(QWidget *parent = nullptr);
    ~thank();

private:
    Ui::thank *ui;
};

#endif // THANK_H
