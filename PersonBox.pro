QT += core
QT += gui
QT += multimedia
QT += multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x06000
SOURCES += \
    src/infoviewer.cpp \
    src/exceptions.cpp \
    src/infosheet.cpp \
    src/infoeditor.cpp \
    src/messages.cpp \
    src/photoviewer.cpp \
    src/main.cpp \
    src/personinfo.cpp \
    src/rootwindow.cpp \
    src/streamhandler.cpp
HEADERS += \
    include/exceptions.h \
    include/infoeditor.h \
    include/messages.h \
    include/photoviewer.h \
    include/rootwindow.h \
    include/personinfo.h \
    include/infosheet.h \
    include/infoviewer.h
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
