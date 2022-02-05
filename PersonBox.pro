QT += core
QT += gui
QT += multimedia
QT += multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x06000
SOURCES += \
    sources/infoviewer.cpp \
    sources/exceptions.cpp \
    sources/infosheet.cpp \
    sources/infoeditor.cpp \
    sources/messages.cpp \
    sources/photoviewer.cpp \
    sources/main.cpp \
    sources/personinfo.cpp \
    sources/rootwindow.cpp \
    sources/streamhandler.cpp
HEADERS += \
    headers/exceptions.h \
    headers/infoeditor.h \
    headers/messages.h \
    headers/photoviewer.h \
    headers/rootwindow.h \
    headers/personinfo.h \
    headers/infosheet.h \
    headers/infoviewer.h
FORMS += \
    gui/infoeditor.ui \
    gui/rootwindow.ui \
    gui/infosheet.ui \
    gui/infoviewer.ui
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
