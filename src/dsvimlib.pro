#-------------------------------------------------
#
# Project created by QtCreator 2017-12-27T13:20:57
#
#-------------------------------------------------

QT       -= core gui

TARGET = dsvimlib
TEMPLATE = lib

DEFINES += DSVIMLIB_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    imageA2b.cpp \
    imageTalk.cpp \
    IniFile.cpp \
    launch_timer.cpp \
    msg_util.cpp \
    time_util.cpp \
    nio_thread.cpp \
    mkdir_p.cpp

HEADERS += \
    convert.h \
    global.h \
    imageA2b.h \
    imageTalk.h \
    IniFile.h \
    launch_timer.h \
    macros.h \
    msg_util.h \
    time_util.h \
    ../include/convert.h \
    ../include/global.h \
    ../include/imageA2b.h \
    ../include/imageTalk.h \
    ../include/IniFile.h \
    ../include/launch_timer.h \
    ../include/macros.h \
    ../include/msg_util.h \
    ../include/time_util.h \
    ../include/nio_thread.h \
    ../include/mkdir_p.h \
    ../include/umcparameters.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
