# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

QT	+= core gui multimedia

TEMPLATE = app
TARGET = Sub-Merge

SOURCES += \
	main.cpp \
	SM_MainWindow.cpp 

HEADERS += \
	SM_MainWindow.h 

DESTDIR = ../x64/Debug

CONFIG += debug

LIBS += -L"."

DEPENDPATH += .

MOC_DIR += .

OBJECTS_DIR += debug

UI_DIR += .

RCC_DIR += .

include(Sub-Merge.pri)
