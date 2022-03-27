TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        bus_manager.cpp \
        main.cpp \
        query.cpp \
        responses.cpp

HEADERS += \
    bus_manager.h \
    query.h \
    responses.h
