TEMPLATE = app
CONFIG += c++17
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_LFLAGS += -pthread

SOURCES += \
    priority_collection_2.cpp

HEADERS += \
    test_runner.h

