TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

DISTFILES += \
  graph \
  graph.graphml \
  graph2 \
  graph2.graphml \
  graph3 \
  graph3.graphml \
  graph4 \
  graph4.graphml

QMAKE_POST_LINK += cp -f $$PWD/graph $$OUT_PWD/ $$escape_expand(\\n\\t)
QMAKE_POST_LINK += cp -f $$PWD/graph2 $$OUT_PWD/ $$escape_expand(\\n\\t)
QMAKE_POST_LINK += cp -f $$PWD/graph3 $$OUT_PWD/ $$escape_expand(\\n\\t)
QMAKE_POST_LINK += cp -f $$PWD/graph4 $$OUT_PWD/ $$escape_expand(\\n\\t)
