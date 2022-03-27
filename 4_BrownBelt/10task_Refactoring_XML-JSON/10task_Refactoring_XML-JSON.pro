TEMPLATE = app
CONFIG += c++17 #console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_LFLAGS += -pthread

INCLUDEPATH += "/home/joe/myCodes/Coursera/includes"
DEPENDPATH += "/home/joe/myCodes/Coursera/includes"

HEADERS += \
        /home/joe/myCodes/Coursera/includes/test_runner.h \
				/home/joe/myCodes/Coursera/includes/xml.h \
				/home/joe/myCodes/Coursera/includes/json.h

SOURCES += \
        main.cpp \
				/home/joe/myCodes/Coursera/includes/xml.cpp \
				/home/joe/myCodes/Coursera/includes/json.cpp
