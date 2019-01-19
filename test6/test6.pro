

TEMPLATE = app

QT += core
QT += gui
QT += widgets

DEFINES += CURRENT_DEBUG_PATH=\\\"$$PWD\\\"

QT += sql

SOURCES += $$PWD/main.cpp

win32-msvc*{
    QMAKE_CXXFLAGS += /std:c++latest
}else{
    CONFIG += c++17
    LIBS += -lstdc++fs
}

win32-msvc*{
    CONFIG += suppress_vcproj_warnings
    CONFIG += console
}else{
    QMAKE_CFLAGS += -std=c11
}





