QT       += core gui network sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QMAKE_CXXFLAGS += -Wall -Wextra -Werror -O3 -g

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    PlotDrawer.cpp \
    SqlSelector.cpp \
    SqlUpdater.cpp \
    main.cpp \
    client.cpp \
    qcustomplot.cpp

HEADERS += \
    PlotDrawer.h \
    SqlSelector.h \
    SqlUpdater.h \
    client.h \
    qcustomplot.h

FORMS += \
    client.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    config.xml
