TEMPLATE = app
QT += core
CONFIG *= c++11

TARGET = ../demo

HEADERS += \
  helpers/ExtraHelpers.h \
  helpers/IcuHelpers.h \
  test/ConsoleLogger.h \
  test/DemoContext.h \

SOURCES += \
  helpers/ExtraHelpers.cpp \
  helpers/IcuHelpers.cpp \
  test/ConsoleLogger.cpp \
  test/DemoContext.cpp \
  test/Demo.cpp \

INCLUDEPATH = \
  handlebars \
  helpers \

LIBS += \
  -l Handlebars -L ../lib \
  -licuuc \
  -licui18n \


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
