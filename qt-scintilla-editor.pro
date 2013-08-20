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
        qscintillaeditor.cpp \
    findreplacedialog.cpp \
    buffer.cpp \
    util.cpp \
    icondb.cpp

HEADERS  += qscintillaeditor.h \
    findreplacedialog.h \
    buffer.h \
    util.h \
    icondb.h

FORMS    += qscintillaeditor.ui \
    findreplacedialog.ui

LIBS += -lScintillaEdit

RESOURCES += \
    qtscitntillaeditor.qrc
