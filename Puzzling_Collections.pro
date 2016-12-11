#-------------------------------------------------
#
# Project created by QtCreator 2016-11-14T16:04:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Puzzling_Collections \

TEMPLATE = app


SOURCES += main.cpp \
    puzzle.cpp \
    main_menu.cpp \
    help_screen.cpp \
    browse_screen.cpp \
    difficulty_screen.cpp \
    select_and_play.cpp

HEADERS  += \
    puzzle.h \
    main_menu.h \
    help_screen.h \
    browse_screen.h \
    difficulty_screen.h \
    select_and_play.h

FORMS    +=

CONFIG += console
