#ifndef HANDLEBARS_FLEX_H
#define HANDLEBARS_FLEX_H

#include "Handlebars.y.hh"

#if ! defined(yyFlexLexerOnce)
// /usr/include/FlexLexer.h
#include <FlexLexer.h>
#endif

namespace Handlebars {


class IStreamManager;
class ParsingContext;


class Flex : public yyFlexLexer
{
public:

  Flex( IStreamManager &, ParsingContext & );

  Bison::symbol_type lex(); // Defined in Handlebars.l.cc

private:
  bool m_initialization = true;

  ParsingContext & m_context;

  IStreamManager & m_streams;
  QByteArray m_input;
  int m_input_position;

  Bison::location_type * yylloc;
  void updateLocSingleLine() { *yylloc += yyleng; }
  void updateLoc();
};

}// namespace Handlebars

#endif // HANDLEBARS_FLEX_H
