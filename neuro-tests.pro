TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lgtest -lpthread

INCLUDEPATH += "../../"

SOURCES += \
        main.cpp \
    ../../narray.cpp

HEADERS += \
    ../../narray.h
