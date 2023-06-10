#-------------------------------------------------
#
# Project created by QtCreator 2023-05-27T22:23:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Game
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        character.cpp \
        barrier.cpp

HEADERS  += mainwindow.h \
        header.h \
        character.h \
        barrier.h \
        barrier.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
