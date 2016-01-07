#-------------------------------------------------
#
# Project created by QtCreator 2016-01-10T19:55:27
#
#-------------------------------------------------

QT       += core gui \
          widgets serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SerialDataApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    configdialog.cpp \
    us015model.cpp

HEADERS  += mainwindow.h \
    configdialog.h \
    us015model.h

FORMS    += mainwindow.ui \
    configdialog.ui

RESOURCES += \
    resources.qrc

DISTFILES += \
    images/application-exit.png \
    images/clear.png \
    images/connect.png \
    images/disconnect.png \
    images/settings.png
