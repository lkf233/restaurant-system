QT       += core gui
QT  += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add.cpp \
    administratorhomepage.cpp \
    admitleave.cpp \
    aftercomment.cpp \
    ask_for_leave.cpp \
    button.cpp \
    change_password.cpp \
    check_salary.cpp \
    check_table.cpp \
    checkcomments_.cpp \
    checkleave.cpp \
    checksaleamount.cpp \
    checksaleamount_day.cpp \
    chef.cpp \
    clock_in_out.cpp \
    commentscene.cpp \
    customerlogin.cpp \
    employee.cpp \
    findpassword.cpp \
    gotocomment.cpp \
    login.cpp \
    loginchooseidentity.cpp \
    main.cpp \
    manager.cpp \
    menuscene.cpp \
    modifymenu.cpp \
    operationondishes.cpp \
    paymentscene.cpp \
    query.cpp \
    register.cpp \
    registerchooseidentity.cpp \
    registerstuff.cpp \
    selectway.cpp \
    servant.cpp \
    servant_open.cpp \
    shoppingbutton.cpp \
    shoppingscene.cpp \
    stufflogin.cpp \
    table.cpp \
    viewcomment.cpp \
    widget1.cpp

HEADERS += \
    add.h \
    administratorhomepage.h \
    admitleave.h \
    aftercomment.h \
    ask_for_leave.h \
    button.h \
    change_password.h \
    check_salary.h \
    check_table.h \
    checkcomments_.h \
    checkleave.h \
    checksaleamount.h \
    checksaleamount_day.h \
    chef.h \
    clock_in_out.h \
    commentscene.h \
    customerlogin.h \
    employee.h \
    findpassword.h \
    gotocomment.h \
    login.h \
    loginchooseidentity.h \
    manager.h \
    menuscene.h \
    modifymenu.h \
    operationondishes.h \
    paymentscene.h \
    query.h \
    register.h \
    registerchooseidentity.h \
    registerstuff.h \
    selectway.h \
    servant.h \
    servant_open.h \
    shoppingbutton.h \
    shoppingscene.h \
    stufflogin.h \
    table.h \
    viewcomment.h \
    widget1.h

FORMS += \
    AddDishes.ui \
    Register.ui \
    add.ui \
    administratorhomepage.ui \
    admitleave.ui \
    aftercomment.ui \
    ask_for_leave.ui \
    change_password.ui \
    check_salary.ui \
    check_table.ui \
    checkcomments_.ui \
    checkleave.ui \
    checksaleamount.ui \
    checksaleamount_day.ui \
    clock_in_out.ui \
    commentscene.ui \
    customerlogin.ui \
    findpassword.ui \
    gotocomment.ui \
    login.ui \
    loginchooseidentity.ui \
    menuscene.ui \
    modifymenu.ui \
    operationondishes.ui \
    paymentscene.ui \
    query.ui \
    registerchooseidentity.ui \
    registerstuff.ui \
    selectway.ui \
    servant_open.ui \
    shoppingscene.ui \
    stufflogin.ui \
    viewcomment.ui \
    widget1.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    new.pro.user

RESOURCES += \
    resource.qrc
