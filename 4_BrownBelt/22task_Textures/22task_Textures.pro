TEMPLATE = app
CONFIG += c++20 #console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_LFLAGS += -pthread

INCLUDEPATH += "/home/joe/myCodes/Coursera/includes"
DEPENDPATH += "/home/joe/myCodes/Coursera/includes"

HEADERS += \
        /home/joe/myCodes/Coursera/includes/test_runner.h \
        Common.h \
        Textures.h

SOURCES += \
        Solution.cpp \
        Textures.cpp \
        main.cpp
