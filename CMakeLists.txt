cmake_minimum_required(VERSION 3.9)

project(qt-scintilla-editor LANGUAGES CXX)

set(SCINTILLA_CODE ../scintilla-code)

include_directories(
        ${SCINTILLA_CODE}/include
        ${SCINTILLA_CODE}/qt/ScintillaEditBase
        ${SCINTILLA_CODE}/qt/ScintillaEdit
        include
)

link_directories(${SCINTILLA_CODE}/bin)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS forms)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(
        qt-scintilla-editor
        src/aboutdialog.cpp
        src/qscintillaeditor.cpp
        src/buffer.cpp
        src/colorscheme.cpp
        src/configuration.cpp
        src/encoding.cpp
        src/encodingdialog.cpp
        src/findreplacedialog.cpp
        src/icondb.cpp
        src/language.cpp
        src/languagedialog.cpp
        src/main.cpp
        src/qscintillaeditor.cpp
        src/styleinfo.cpp
        src/util.cpp
        include/aboutdialog.h
        include/buffer.h
        include/colorscheme.h
        include/configuration.h
        include/encoding.h
        include/encodingdialog.h
        include/findreplacedialog.h
        include/icondb.h
        include/language.h
        include/languagedialog.h
        include/qscintillaeditor.h
        include/styleinfo.h
        include/util.h
        include/version.h
        forms/aboutdialog.ui
        forms/encodingdialog.ui
        forms/findreplacedialog.ui
        forms/languagedialog.ui
        forms/qscintillaeditor.ui
        resources/qtscitntillaeditor.qrc
)

target_link_libraries(qt-scintilla-editor PRIVATE Qt5::Widgets ScintillaEdit)
