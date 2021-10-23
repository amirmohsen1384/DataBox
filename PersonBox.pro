QT += core
QT += gui
QT += multimedia
QT += multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x06000
SOURCES += \
    sources/filehandling.cpp \
    sources/infosheet.cpp \
    sources/infoeditor.cpp \
    sources/infomonitor.cpp \
    sources/messages.cpp \
    sources/personinfowidget.cpp \
    sources/photoviewer.cpp \
    sources/infoitem.cpp \
    sources/main.cpp \
    sources/personinfo.cpp \
    sources/rootwindow.cpp
HEADERS += \
    headers/infoeditor.h \
    headers/infoitem.h \
    headers/infomonitor.h \
    headers/messages.h \
    headers/personinfowidget.h \
    headers/photoviewer.h \
    headers/rootwindow.h \
    headers/personinfo.h \
    headers/infosheet.h
FORMS += \
    gui/infoeditor.ui \
    gui/rootwindow.ui \
    gui/infosheet.ui
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
