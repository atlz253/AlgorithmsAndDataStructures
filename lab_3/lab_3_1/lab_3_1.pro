TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

QMAKE_POST_LINK += cp -f ../../../lab_3/test_numbers.txt $$OUT_PWD/../ $$escape_expand(\\n\\t)
