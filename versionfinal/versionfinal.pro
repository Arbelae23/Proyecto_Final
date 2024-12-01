QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    avescirculares.cpp \
    avessencillas.cpp \
    explosion.cpp \
    level1.cpp \
    level2.cpp \
    main.cpp \
    mainmenu.cpp \
    mainwindow.cpp \
    particle.cpp

HEADERS += \
    avescirculares.h \
    avessencillas.h \
    explosion.h \
    level1.h \
    level2.h \
    mainmenu.h \
    mainwindow.h \
    particle.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
