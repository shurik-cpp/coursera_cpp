TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    server_stats.cpp \
    stats.cpp \

HEADERS += \
    http_request.h \
    stats.h \
    test_runner.h
