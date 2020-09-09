QT += quick

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        src/imitatorsettings.cpp \
        src/mainwindow.cpp \
        src/mainwindowcontroller.cpp \
        src/tcpserver.cpp

TRANSLATIONS += \
    AirConditioningImitator_ru_RU.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/imitatorsettings.h \
    src/mainwindow.h \
    src/mainwindowcontroller.h \
    src/tcpserver.h

DISTFILES += \
    MainWindow.qml \
    MainWindowForm.ui.qml

RESOURCES += \
    Images.qrc \
    qml.qrc
