QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    account.cpp \
    account_login.cpp \
    account_service.cpp \
    create.cpp \
    date.cpp \
    deposit.cpp \
    eclose.cpp \
    employee.cpp \
    employee_login.cpp \
    employee_service.cpp \
    main.cpp \
    mainwindow.cpp \
    query.cpp \
    thank.cpp \
    transfer.cpp \
    withdraw.cpp

HEADERS += \
    account.h \
    account_login.h \
    account_service.h \
    create.h \
    date.h \
    deposit.h \
    eclose.h \
    employee.h \
    employee_login.h \
    employee_service.h \
    mainwindow.h \
    query.h \
    thank.h \
    transfer.h \
    withdraw.h

FORMS += \
    account_service.ui \
    create.ui \
    deposit.ui \
    eclose.ui \
    employee_login.ui \
    employee_service.ui \
    mainwindow.ui \
    query.ui \
    thank.ui \
    transfer.ui \
    withdraw.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    a.qrc
