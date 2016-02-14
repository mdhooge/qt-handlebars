CONFIG *= c++11

SOURCES += \
  $$PWD/HandlebarsFlex.cpp \
  $$PWD/HandlebarsIStreamManager.cpp \
  $$PWD/HandlebarsNodes.cpp \
  $$PWD/HandlebarsParser.cpp \
  $$PWD/HandlebarsParsingContext.cpp \
  $$PWD/HandlebarsRenderingContext.cpp \

HEADERS += \
  $$PWD/HandlebarsFlex.h \
  $$PWD/HandlebarsHelpers.h \
  $$PWD/HandlebarsIStreamManager.h \
  $$PWD/HandlebarsNodes.h \
  $$PWD/HandlebarsParser.h \
  $$PWD/HandlebarsParsingContext.h \
  $$PWD/HandlebarsRenderingContext.h \

FLEXSOURCE = $$PWD/Handlebars.l
BISONSOURCE = $$PWD/Handlebars.y

include($$PWD/flex.pri)
include($$PWD/bison.pri)
