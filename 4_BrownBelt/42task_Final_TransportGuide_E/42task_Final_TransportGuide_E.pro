TEMPLATE = app
CONFIG += c++17 console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_LFLAGS += -pthread

INCLUDEPATH += "/home/shurik/myCodes/Coursera/includes"
DEPENDPATH += "/home/shurik/myCodes/Coursera/includes"

SOURCES += \
        descriptions.cpp \
        json.cpp \
        main.cpp \
        requests.cpp \
        sphere.cpp \
        transport_catalog.cpp \
        transport_router.cpp \
        utils.cpp

HEADERS += \
	descriptions.h \
	graph.h \
	json.h \
	requests.h \
	router.h \
	sphere.h \
	transport_catalog.h \
	transport_router.h \
	utils.h
