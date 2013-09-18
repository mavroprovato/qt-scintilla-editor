#-------------------------------------------------
#
# Project created by QtCreator 2013-07-27T00:49:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt-scintilla-editor
TEMPLATE = app

INCLUDEPATH += include

SOURCES += src/main.cpp\
        src/qscintillaeditor.cpp \
    src/findreplacedialog.cpp \
    src/buffer.cpp \
    src/util.cpp \
    src/icondb.cpp \
    src/aboutdialog.cpp

HEADERS  += include/qscintillaeditor.h \
    include/findreplacedialog.h \
    include/buffer.h \
    include/util.h \
    include/icondb.h \
    include/aboutdialog.h \
    include/version.h

FORMS    += forms/qscintillaeditor.ui \
    forms/findreplacedialog.ui \
    forms/aboutdialog.ui

LIBS += -lScintillaEdit

RESOURCES += \
    resources/qtscitntillaeditor.qrc
