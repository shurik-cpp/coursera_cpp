TEMPLATE = app
CONFIG += c++17 console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_LFLAGS += -pthread

INCLUDEPATH += "/home/shurik/myCodes/Coursera/includes"
DEPENDPATH += "/home/shurik/myCodes/Coursera/includes"

HEADERS += \
        /home/shurik/myCodes/Coursera/includes/test_runner.h

SOURCES += \
        main.cpp
