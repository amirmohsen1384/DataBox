QT += core
QT += gui
QT += widgets

CONFIG += c++2a

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x06000

SOURCES += \
    src/datacontainer.cpp \
    src/dataeditor.cpp \
    src/photoviewer.cpp

HEADERS += \
    include/datacontainer.h \
    include/dataeditor.h \
    include/photoviewer.h

FORMS += \
    ui/dataeditor.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ui/icons/resource.qrc
