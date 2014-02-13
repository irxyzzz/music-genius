# -------------------------------------------------
# Project created by QtCreator 2011-02-28T15:16:48
# -------------------------------------------------
TARGET = vpiano
TEMPLATE = app
QT += core \
      gui
DEFINES += __WINDOWS_MM__
CONFIG -= debug
CONFIG -= debug_and_release
CONFIG += release
CONFIG += qtestlib
CONFIG -= console
QMAKE_CXXFLAGS += -Wall \

SOURCES += main.cpp \
    mainwindow.cpp \
    controller.cpp \
    RtMidi.cpp \
    octavekeybd.cpp \
    staff/partitura.cpp \
    staff/nota.cpp \
    staff/compas.cpp \
    renderpartitura.cpp \
    partituracommands.cpp \
    staff/currentstatus.cpp \
    staff/chordanalyst.cpp \
    staff/staff.cpp \
    staff/staffdao.cpp \
    staff/MidiMaker.cpp \
    staff/minHeap.cpp
HEADERS += mainwindow.h \
    midiref.h \
    controller.h \
    RtMidi.h \
    RtError.h \
    octavekeybd.h \
    staff/partitura.h \
    staff/nota.h \
    staff/compas.h \
    renderpartitura.h \
    partituracommands.h \
    staff/currentstatus.h \
    staff/chordanalyst.h \
    staff/staff.h \
    staff/music_element.h \
    staff/staffdao.h \
    staff/MidiMaker.h \
    staff/minHeap.h
FORMS += mainwindow.ui \
         controller.ui
INCLUDEPATH += d:/qt/2010.05/qt/include/vpiano
LIBS += -L"d:/qt/2010.05/qt/lib" \
        -lvpianokeybd \
        -lwinmm
RESOURCES += katmus.qrc
