TEMPLATE = app
CONFIG += c++17
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_LFLAGS += -pthread

SOURCES += \
        main.cpp \
        parse.cpp \
        search_server.cpp

HEADERS += \
    iterator_range.h \
    parse.h \
    search_server.h \
    synchronized.h \
    test_runner.h
