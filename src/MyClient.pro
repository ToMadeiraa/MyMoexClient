QT       += core gui network sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QMAKE_CXXFLAGS += -Wall -Wextra -O0 -g

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += QCUSTOMPLOT_USE_LIBRARY
INCLUDEPATH += C:/Users/User/Documents/PetProjects/MyMoexClient/include
CONFIG(debug, debug|release) {
    # Режим Debug
    win32:QCP_LIB_NAME = qcustomplotd2
    else:QCP_LIB_NAME = qcustomplotd
} else {
    # Режим Release
    win32:QCP_LIB_NAME = qcustomplot2
    else:QCP_LIB_NAME = qcustomplot
}
LIBS += -L"C:/Users/User/Documents/PetProjects/MyMoexClient/include" -l$$QCP_LIB_NAME

SOURCES += \
    AxisTag.cpp \
    GuiElements/mycomboboxbinsize.cpp \
    GuiElements/mycomboboxsecurity.cpp \
    PlotDrawer.cpp \
    SqlSelector.cpp \
    SqlUpdater.cpp \
    Widgets/financialplot.cpp \
    Widgets/volumeplot.cpp \
    leftwidget.cpp \
    main.cpp \
    client.cpp \
    GuiElements/mypushbutton.cpp \
    plotsdrawer.cpp \
    topwidget.cpp

HEADERS += \
    AxisTag.h \
    GuiElements/mycomboboxbinsize.h \
    GuiElements/mycomboboxsecurity.h \
    PlotDrawer.h \
    SqlSelector.h \
    SqlUpdater.h \
    Widgets/financialplot.h \
    Widgets/volumeplot.h \
    client.h \
    leftwidget.h \
    GuiElements/mypushbutton.h \
    plotsdrawer.h \
    topwidget.h

FORMS += \
    Widgets/financialplot.ui \
    Widgets/volumeplot.ui \
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
