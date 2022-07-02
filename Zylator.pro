QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/qt/* \
	src/shared/* \
#   src/programs/*

HEADERS += \
    include/qt/* \
	include/shared/* 
	include/programs/*

# adding programs manually, until fastled compability issues are solved
SOURCES += \
	src/programs/sampleProgram.cpp

INCLUDEPATH += include

OBJECTS_DIR = .qt/build

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
