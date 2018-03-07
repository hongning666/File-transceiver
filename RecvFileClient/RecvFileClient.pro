#-------------------------------------------------
#
# Project created by QtCreator 2018-03-07T19:03:58
#
#-------------------------------------------------

QT       += core gui network
CONFIG +=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RecvFileClient
TEMPLATE = app


SOURCES += main.cpp\
        recvfileclient.cpp

HEADERS  += recvfileclient.h

FORMS    += recvfileclient.ui
