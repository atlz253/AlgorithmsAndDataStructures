TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

DISTFILES += \
  base.bin

QMAKE_POST_LINK += cp -f ../../../lab_1/lab_1_1/base.bin $$OUT_PWD/ $$escape_expand(\\n\\t)
