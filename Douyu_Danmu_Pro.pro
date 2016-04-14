#-------------------------------------------------
#
# Project created by QtCreator 2016-04-12T19:41:37
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Douyu_Danmu_Pro
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    networkaccess.cpp \
    jsonparse.cpp \
    douyutcpsocket.cpp

HEADERS  += mainwindow.h \
    networkaccess.h \
    jsonparse.h \
    danmuconfig.h \
    douyutcpsocket.h

FORMS    += mainwindow.ui
