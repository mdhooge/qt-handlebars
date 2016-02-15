TEMPLATE = app
QT += testlib
QT -= gui

CONFIG *= c++11

TARGET = ../test

HEADERS += \
  helpers/ExtraHelpers.h \
  test/ConsoleLogger.h \
  test/DemoContext.h \

SOURCES += \
  helpers/ExtraHelpers.cpp \
  test/ConsoleLogger.cpp \
  test/DemoContext.cpp \
  test/Test.cpp \

INCLUDEPATH = \
  handlebars \
  helpers \

LIBS += \
  -l Handlebars -L ../lib \

CONFIG(release, debug|release) {
  MOC_DIR     = ../build/release
  OBJECTS_DIR = ../build/release
  UI_DIR      = ../build/release
}
else {
  MOC_DIR     = ../build/debug
  OBJECTS_DIR = ../build/debug
  UI_DIR      = ../build/debug
}
