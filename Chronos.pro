QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# remove possible other optimization flags
QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2

# add the desired -O3 if not present
QMAKE_CXXFLAGS_RELEASE *= -O3

RC_ICONS = icon.ico

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    sources/aboutbox.cpp \
    sources/day.cpp \
    sources/main.cpp \
    sources/mainwindow.cpp \
    sources/setdaydialog.cpp \
    sources/tools.cpp \
    sources/week.cpp \
    sources/welcome.cpp

HEADERS += \
    sources/aboutbox.h \
    sources/day.h \
    sources/mainwindow.h \
    sources/setdaydialog.h \
    sources/tools.h \
    sources/week.h \
    sources/welcome.h

FORMS += \
    ui/aboutbox.ui \
    ui/mainwindow.ui \
    ui/setdaydialog.ui \
    ui/welcome.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    pictures.qrc \
    stylesheets.qrc
