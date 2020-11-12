include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
        ../Project/IKeypad.h \
        ../Project/ILatch.h \
        ../Project/lockcontroller.h \
        tst_testdivisionbyzero.h

SOURCES += \
        ../Project/lockcontroller.cpp \
        main.cpp


INCLUDEPATH += ../Project