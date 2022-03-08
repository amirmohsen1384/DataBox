QT += core gui widgets
CONFIG += c++17
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x06000
SOURCES += \
    src/infoviewer.cpp \
    src/exceptions.cpp \
    src/infoeditor.cpp \
    src/photoviewer.cpp \
    src/personinfo.cpp \
    src/streamhandler.cpp
HEADERS += \
    include/exceptions.h \
    include/infoeditor.h \
    include/photoviewer.h \
    include/personinfo.h \
    include/infoviewer.h
FORMS += \
    ui/infoeditor.ui \
    ui/infoviewer.ui
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
RESOURCES += \
    ui/icons/resource.qrc
