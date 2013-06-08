#-------------------------------------------------
#
# Project created by QtCreator 2013-05-23T00:31:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = alphacool_demo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++0x
LIBS           += -L../app -lalphacool
INCLUDEPATH    += ../app/core/include
INCLUDEPATH    += ../app/extra/include
