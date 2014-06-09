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
    setupwinnerdialog.cpp \
    registrationwidget.cpp \
    fourmatchescontestwidget.cpp \
    fourmatchescontest.cpp \
    phase.cpp

HEADERS  += mainwindow.h \
    teammodel.h \
    team.h \
    matchmodel.h \
    match.h \
    util.h \
    dialogteam.h \
    setupwinnerdialog.h \
    registrationwidget.h \
    fourmatchescontestwidget.h \
    fourmatchescontest.h \
    phase.h

FORMS    += mainwindow.ui \
    dialogteam.ui \
    setupwinnerdialog.ui \
    registrationwidget.ui \
    fourmatchescontestwidget.ui

RESOURCES += \
    resource.qrc
