#-------------------------------------------------
#
# Project created by QtCreator 2020-11-06T15:42:54
#
#-------------------------------------------------

QT       += core gui widgets xml printsupport concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MaxPatrol_Report
TEMPLATE = app


SOURCES += main.cpp\
        maxpatrol_report.cpp \
    Report_Generation.cpp \
    Fun_Common.cpp


HEADERS  += maxpatrol_report.h \
    Fun_Common.h \
    Report_Generation.h

RESOURCES += \
    resource.qrc
