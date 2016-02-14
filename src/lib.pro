TEMPLATE = lib
CONFIG += staticlib
VERSION = 1.0.0

CONFIG *= c++11

CONFIG += release
DESTDIR = ../lib


include(handlebars/Handlebars.pri)


CONFIG(release, debug|release) {
  TARGET      = Handlebars
  MOC_DIR     = ../build/release
  OBJECTS_DIR = ../build/release
  UI_DIR      = ../build/release
}
else {
  TARGET      = Handlebarsd
  MOC_DIR     = ../build/debug
  OBJECTS_DIR = ../build/debug
  UI_DIR      = ../build/debug
}
