#-------------------------------------------------
#
# Project created by QtCreator 2017-06-14T22:53:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gwentSim
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gwentGame.cpp \
    gwentMechanics.cpp

HEADERS  += mainwindow.h \
    gwentGame.h \
    gwentMechanics.h

FORMS    += mainwindow.ui
