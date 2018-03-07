#-------------------------------------------------
#
# Project created by QtCreator 2018-03-07T17:10:15
#
#-------------------------------------------------

QT       += core gui network
CONFIG +=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SendFileServer
TEMPLATE = app


SOURCES += main.cpp\
        sendfileserver.cpp

HEADERS  += sendfileserver.h

FORMS    += sendfileserver.ui
