QT += core gui widgets
CONFIG += c++17
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x06000
SOURCES += \
    src/infocontainer.cpp \
    src/infoeditor.cpp \
    src/photoview.cpp
HEADERS += \
    include/infocontainer.h \
    include/infoeditor.h \
    include/photoview.h
FORMS += \
    ui/infoeditor.ui \

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
RESOURCES += \
    ui/icons/resource.qrc
