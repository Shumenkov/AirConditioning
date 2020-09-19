QT += quick

CONFIG += c++11


include($$PWD/src/src.pri)

RESOURCES += \
    Images.qrc \
    qml.qrc

INCLUDEPATH += ../AirConditioningNetInteraction/src
LIBS += -L../build-AirConditioningNetInteraction-Desktop_Qt_5_11_0_MinGW_32bit-Debug/debug -lAirConditioningNetInteraction

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target






