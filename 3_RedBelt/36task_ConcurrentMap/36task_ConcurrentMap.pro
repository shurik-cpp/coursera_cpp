TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_LFLAGS += -pthread


SOURCES += \
    concurrent_map.cpp

HEADERS += \
    profile.h \
    syncronized.h \
    test_runner.h
