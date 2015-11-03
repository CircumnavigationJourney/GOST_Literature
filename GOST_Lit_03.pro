#-------------------------------------------------
#
# Project created by QtCreator 2015-07-21T15:04:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GOST_Lit_03
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    journalarticlewidget.cpp \
    patentwidget.cpp \
    popularmistakesui.cpp \
    biblio.cpp \
    mergelitlists.cpp \
    literature.cpp \
    article.cpp \
    oldVersion/item_class.cpp \
    item.cpp \
    itemscontainer.cpp \
    colorselect.cpp

HEADERS  += mainwindow.h \
    journalarticlewidget.h \
    patentwidget.h \
    popularmistakesui.h \
    biblio.h \
    mergelitlists.h \
    article.h \
    oldVersion/Item_class.h \
    item.h \
    itemscontainer.h \
    colorselect.h

FORMS    += mainwindow.ui \
    journalarticlewidget.ui \
    patentwidget.ui \
    popularmistakesui.ui \
    mergelitlists.ui \
    colorselect.ui

RESOURCES += \
    Icons.qrc

DISTFILES +=