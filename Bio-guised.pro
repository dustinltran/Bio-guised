#-------------------------------------------------
#
# Project created by QtCreator 2016-03-17T22:10:28
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bio-guised
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    fingerprintscanpopup.cpp \
    bioguised.cpp \
    biomodel.cpp \

HEADERS  += mainwindow.h \
    fingerprintscanpopup.h \
    bioguised.h \
    biomodel.h \


FORMS    += mainwindow.ui \
    fingerprintscanpopup.ui \
    bioguised.ui

DISTFILES += \
    Registered
