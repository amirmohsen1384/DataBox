QT += core
QT += gui
QT += widgets

CONFIG += c++2a

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x06000

SOURCES += \
    src/abstracteditor.cpp \
    src/dataviewer.cpp \
    src/countrymodel.cpp \
    src/namedphotoviewer.cpp \
    src/datacontainer.cpp \
    src/photoviewer.cpp

HEADERS += \
    include/abstracteditor.h \
    include/dataviewer.h \
    include/countrymodel.h \
    include/datacontainer.h \
    include/namedphotoviewer.h \
    include/photoviewer.h

FORMS += \
    ui/abstracteditor.ui \
    ui/dataviewer.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ui/icons/resource.qrc
