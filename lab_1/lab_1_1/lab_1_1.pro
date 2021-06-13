TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

DISTFILES += README.md \
             base.bin

QMAKE_POST_LINK += cp -f $$PWD/base.bin $$OUT_PWD/ $$escape_expand(\\n\\t)
