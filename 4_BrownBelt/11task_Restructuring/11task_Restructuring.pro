TEMPLATE = app
CONFIG += c++17 #console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_LFLAGS += -pthread

INCLUDEPATH += "/home/joe/myCodes/Coursera/includes"
DEPENDPATH += "/home/joe/myCodes/Coursera/includes"

HEADERS += \
        /home/joe/myCodes/Coursera/includes/test_runner.h \
        stats_aggregator.h

SOURCES += \
        main.cpp \
        stats_aggregator.cpp \
        stats_aggregator_test.cpp
