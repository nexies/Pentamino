TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt
QT += gui widgets

SOURCES += \
#        figures.cpp \
        gridview.cpp \
        main.cpp \
        mainwindow.cpp \
        second_try.cpp

HEADERS += \
#    figures.h \
    gridview.h \
    mainwindow.h \
    second_try.h

FORMS += \
    mainwindow.ui
