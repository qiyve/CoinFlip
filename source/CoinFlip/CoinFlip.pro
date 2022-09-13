#-------------------------------------------------
#
# Project created by QtCreator 2022-09-09T16:03:40
#
#-------------------------------------------------

QT       += core gui  multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CoinFlip
TEMPLATE = app


SOURCES += main.cpp\
        mainscene.cpp \
    mypushbutton.cpp \
    chooselevelscene.cpp \
    playscene.cpp \
    mycoin.cpp \
    datacoin.cpp

HEADERS  += mainscene.h \
    mypushbutton.h \
    chooselevelscene.h \
    playscene.h \
    mycoin.h \
    datacoin.h

FORMS    += mainscene.ui

RESOURCES += \
    rec.qrc
