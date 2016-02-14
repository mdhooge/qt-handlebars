flex.name = Flex ${QMAKE_FILE_IN}
flex.input = FLEXSOURCE
flex.output = ${QMAKE_FILE_PATH}/${QMAKE_FILE_BASE}.l.cc
flex.commands = flex -o ${QMAKE_FILE_PATH}/${QMAKE_FILE_BASE}.l.cc ${QMAKE_FILE_IN}
flex.CONFIG += target_predeps
flex.variable_out = GENERATED_SOURCES
silent:flex.commands = @echo Lex ${QMAKE_FILE_IN} && $$flex.commands
QMAKE_EXTRA_COMPILERS += flex

OTHER_FILES += \
    $$FLEXSOURCE
