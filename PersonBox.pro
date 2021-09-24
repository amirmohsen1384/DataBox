QT += core
QT += gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x06000
SOURCES += \
    sources/main.cpp \
    sources/personinfo.cpp \
    sources/rootwindow.cpp
HEADERS += \
    headers/rootwindow.h \
    headers/personinfo.h
FORMS += \
    gui/rootwindow.ui
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
