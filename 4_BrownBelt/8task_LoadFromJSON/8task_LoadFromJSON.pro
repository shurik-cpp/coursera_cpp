TEMPLATE = app
CONFIG += c++17 #console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_LFLAGS += -pthread

INCLUDEPATH += "/home/joe/myCodes/Coursera/includes"

SOURCES += \
        json.cpp \
        spendings_json.cpp

HEADERS += \
  json.h
