QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controllers/calculatorcontroller.cpp \
    Controllers/creditcontroller.cpp \
    Controllers/graphcontroller.cpp \
    Models/calculatormodel.cpp \
    Models/creditmodel.cpp \
    Models/graphmodel.cpp \
    ThirdParty/qcustomplot.cpp \
    Views/Credit/creditview.cpp \
    Views/Graph/graphview.cpp \
    main.cpp \
    Views/CalculatorView/calculatorview.cpp \
    ThirdParty/parser/parser.c \
    ThirdParty/stack/stack.c
    ThirdParty/qcustomplot.cpp

HEADERS += \
    Controllers/calculatorcontroller.h \
    Controllers/creditcontroller.h \
    Controllers/graphcontroller.h \
    Models/calculatormodel.h \
    Models/creditmodel.h \
    Models/graphmodel.h \
    ThirdParty/qcustomplot.h \
    Views/CalculatorView/calculatorview.h \
    ThirdParty/parser/parser.h \
    ThirdParty/stack/stack.h \
    Views/Credit/creditview.h \
    Views/Graph/graphview.h
    ThirdParty/qcustomplot.h

FORMS += \
    Views/CalculatorView/calculatorview.ui \
    Views/Credit/creditview.ui \
    Views/Graph/graphview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
