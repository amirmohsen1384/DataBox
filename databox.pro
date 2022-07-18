QT += core
QT += gui
QT += widgets

CONFIG += c++2a

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x06000

SOURCES += \
    main.cpp \
    src/dataviewer.cpp \
    src/countrymodel.cpp \
    src/namedphotoviewer.cpp \
    src/datacontainer.cpp \
    src/dataeditor.cpp \
    src/photoviewer.cpp

HEADERS += \
    include/dataviewer.h \
    include/countrymodel.h \
    include/datacontainer.h \
    include/dataeditor.h \
    include/namedphotoviewer.h \
    include/photoviewer.h

FORMS += \
    ui/dataviewer.ui \
    ui/dataeditor.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ui/icons/resource.qrc
