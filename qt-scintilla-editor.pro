#-------------------------------------------------
#
# Project created by QtCreator 2013-07-27T00:49:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt-scintilla-editor
TEMPLATE = app


SOURCES += main.cpp\
        qscintillaeditor.cpp

HEADERS  += qscintillaeditor.h

FORMS    += qscintillaeditor.ui

LIBS += -lScintillaEdit
