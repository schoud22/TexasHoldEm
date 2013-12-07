#-------------------------------------------------
#
# Project created by QtCreator 2013-11-04T17:23:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CS340Project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    card.cpp \
    carddeck.cpp \
    game.cpp \
    player.cpp \
    mainmenu.cpp \
    informationdialogue.cpp

HEADERS  += mainwindow.h \
    card.h \
    carddeck.h \
    game.h \
    player.h \
    mainmenu.h \
    informationdialogue.h

FORMS    += mainwindow.ui \
    mainmenu.ui \
    informationdialogue.ui

RESOURCES += \
    images.qrc
