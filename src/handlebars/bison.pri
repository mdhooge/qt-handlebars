bison.name = Bison ${QMAKE_FILE_IN}
bison.input = BISONSOURCE
bison.output = ${QMAKE_FILE_PATH}/${QMAKE_FILE_BASE}.y.cc
bison.commands = bison -o ${QMAKE_FILE_PATH}/${QMAKE_FILE_BASE}.y.cc ${QMAKE_FILE_IN}
bison.CONFIG += target_predeps
bison.variable_out = GENERATED_SOURCES
silent:bison.commands = @echo Bison ${QMAKE_FILE_IN} && $$bison.commands
QMAKE_EXTRA_COMPILERS += bison

bison_h.name = Bison Header ${QMAKE_FILE_IN}
bison_h.input = BISONSOURCE
bison_h.output = ${QMAKE_FILE_PATH}/${QMAKE_FILE_BASE}.y.hh
bison_h.commands = bison -o ${QMAKE_FILE_PATH}/${QMAKE_FILE_BASE}.y.cc ${QMAKE_FILE_IN}
bison_h.CONFIG += target_predeps no_link
silent:bison_h.commands = @echo Bison Header ${QMAKE_FILE_IN} && $$bison.commands
QMAKE_EXTRA_COMPILERS += bison_h

OTHER_FILES += \
    $$BISONSOURCE
