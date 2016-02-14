#include "HandlebarsFlex.h"

#include <algorithm>
#include <cstring>


#include "HandlebarsIStreamManager.h"
#include "HandlebarsParsingContext.h"


namespace Handlebars {

Flex::Flex( IStreamManager & streams, ParsingContext & context ) :
  yyFlexLexer( streams.getCurrentStream() ),
  m_context( context ),
  m_streams( streams ),
  yylloc( streams.getCurrentStreamLocation() )
{
}

void
Flex::updateLoc()
{
  QString text( yytext );
  int newlines( text.count( '\n' ));
  if( newlines > 0 ) {
    yylloc->lines( newlines );
    yylloc->end.column = text.size() - text.lastIndexOf( '\n' );
  }
  else
    *yylloc += yyleng;
}

}// namespace Handlebars
