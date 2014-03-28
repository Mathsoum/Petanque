#-------------------------------------------------
#
# Project created by QtCreator 2014-03-15T15:40:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = petanque
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    teammodel.cpp \
    team.cpp \
    matchmodel.cpp \
    match.cpp \
    dialogteam.cpp \
    contest.cpp \
    setupwinnerdialog.cpp

HEADERS  += mainwindow.h \
    teammodel.h \
    team.h \
    matchmodel.h \
    match.h \
    util.h \
    dialogteam.h \
    contest.h \
    setupwinnerdialog.h

FORMS    += mainwindow.ui \
    dialogteam.ui \
    setupwinnerdialog.ui
