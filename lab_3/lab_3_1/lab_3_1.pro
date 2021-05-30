TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

QMAKE_POST_LINK += cp -f $$PWD/../test_numbers.txt $$OUT_PWD/../ $$escape_expand(\\n\\t)
QMAKE_POST_LINK += cp -f $$PWD/N410.txt $$OUT_PWD/ $$escape_expand(\\n\\t)
QMAKE_POST_LINK += cp -f $$PWD/N4100.txt $$OUT_PWD/ $$escape_expand(\\n\\t)
QMAKE_POST_LINK += cp -f $$PWD/N4500.txt $$OUT_PWD/ $$escape_expand(\\n\\t)
QMAKE_POST_LINK += cp -f $$PWD/N41000.txt $$OUT_PWD/ $$escape_expand(\\n\\t)



HEADERS +=
