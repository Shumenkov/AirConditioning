QT += quick

CONFIG += c++11


include($$PWD/src/src.pri)

RESOURCES += \
    Images.qrc \
    qml.qrc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target






