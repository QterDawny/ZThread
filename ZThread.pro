#-------------------------------------------------
#
# Project created by QtCreator 2015-04-16T09:44:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ZThread
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        zthreadpool.cpp


HEADERS  += mainwindow.h \
            zthreadpool.h \
            threadbase.h

FORMS    += mainwindow.ui
