TEMPLATE = app
CONFIG += c++20 #console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_LFLAGS += -pthread

INCLUDEPATH += "/home/joe/myCodes/Coursera/includes"
DEPENDPATH += "/home/joe/myCodes/Coursera/includes"

HEADERS += \
        /home/joe/myCodes/Coursera/includes/test_runner.h \
        booking.h \
        booking_.h \
        new_booking_providers.h \
        new_trip_manager.h \
        old_booking_providers.h \
        old_trip_manager.h

SOURCES += \
        main.cpp
