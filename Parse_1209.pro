#-------------------------------------------------
#
# Project created by QtCreator 2021-12-09T21:49:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Parse_1209
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fengxianparse.cpp \
    qaesencryption.cpp \
    xinshengparse.cpp

HEADERS  += mainwindow.h \
    fengxian.h \
    fengxianparse.h \
    xinsheng.h \
    xinshengparse.h \
    qaesencryption.h \
    qianwei.h

FORMS    += mainwindow.ui

CONFIG += C++11

RC_ICONS = 3.ico
