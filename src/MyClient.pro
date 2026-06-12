QT       += core gui network sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QMAKE_CXXFLAGS += -Wall -Wextra -O0 -g

DEFINES += QCUSTOMPLOT_USE_LIBRARY
INCLUDEPATH += C:/Users/okhot/Documents/PetProjects/MyMoexClient/src/include
CONFIG(debug, debug|release) {
    # Режим Debug
    win32:QCP_LIB_NAME = qcustomplotd2
    else:QCP_LIB_NAME = qcustomplotd
} else {
    # Режим Release
    win32:QCP_LIB_NAME = qcustomplot2
    else:QCP_LIB_NAME = qcustomplot
}
LIBS += -L"C:/Users/okhot/Documents/PetProjects/MyMoexClient/src/include" -l$$QCP_LIB_NAME

SOURCES += \
    GuiElements/mycomboboxbinsize.cpp \
    GuiElements/mycomboboxsecurity.cpp \
    SqlSelector.cpp \
    SqlUpdater.cpp \
    Widgets/additionalplotwidget.cpp \
    Widgets/candleswidget.cpp \
    Widgets/horizontalvolumewidget.cpp \
    Widgets/verticalvolumewidget.cpp \
    Widgets/xaxiswidget.cpp \
    Widgets/yaxis2widget.cpp \
    leftwidget.cpp \
    main.cpp \
    client.cpp \
    GuiElements/mypushbutton.cpp \
    plotsdrawer.cpp \
    topwidget.cpp

HEADERS += \
    GuiElements/mycomboboxbinsize.h \
    GuiElements/mycomboboxsecurity.h \
    SqlSelector.h \
    SqlUpdater.h \
    Widgets/additionalplotwidget.h \
    Widgets/candleswidget.h \
    Widgets/horizontalvolumewidget.h \
    Widgets/verticalvolumewidget.h \
    Widgets/xaxiswidget.h \
    Widgets/yaxis2widget.h \
    client.h \
    leftwidget.h \
    GuiElements/mypushbutton.h \
    plotsdrawer.h \
    topwidget.h


FORMS += \
    client.ui \
    leftwidget.ui \
    plotsdrawer.ui \
    topwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    config.xml
