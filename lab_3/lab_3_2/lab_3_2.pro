TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        avl.cpp \
        main.cpp \
        splay.cpp

HEADERS += \
  avl.hpp \
  splay.hpp

OTHER_FILES += testKeys.txt

QMAKE_POST_LINK += cp -f $$PWD/testKeys.txt $$OUT_PWD/ $$escape_expand(\\n\\t)
