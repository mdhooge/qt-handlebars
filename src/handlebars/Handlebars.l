%option 8bit batch nounput noyywrap
%option nodefault warn
%option c++ yyclass="Handlebars::Flex"
%option debug

%{
#include "Handlebars.y.hh"
#include "HandlebarsFlex.h"
#include "HandlebarsIStreamManager.h"
#include "HandlebarsParsingContext.h"

#undef  YY_DECL
#define YY_DECL Handlebars::Bison::symbol_type Handlebars::Flex::lex()
 // Can no longer use yylex() as method name because it clashes with parent signature

using token = Handlebars::Bison;
%}

 // TEXT_STATE condition is used when harvesting text outside of brackets
%x  TEXT_STATE

 // SPACE_STATE condition drops the next space chars
%x  SPACE_STATE

 // INCLUDE_STATE condition is used to include another file in-place
%x  INCLUDE_STATE

%x  COMMENT1_STATE
%x  COMMENT2_STATE

 // http://handlebarsjs.com/expressions.html
 // Identifiers may be any unicode character except for the following:
ID_char [^[:space:]!"#%&'()*+,./;<=>[\\\]^`{|}~]
ID      {ID_char}+

%%
%{
                        // Initialization on first call (or yyin reset)
                        if( m_initialization ) {
                          m_initialization = false;
                          BEGIN( TEXT_STATE );
                        }

                        // Location: Bison Manual, 10.1.3, p159
                        yylloc->step();
%}

<TEXT_STATE>[^{]+     |
<TEXT_STATE>"{"[^{]*  {
                        updateLoc();
                        return token::make_TEXT( yytext, *yylloc );
                      }

<TEXT_STATE>"{{"~?    {
                        BEGIN( INITIAL );
                        updateLocSingleLine();
                        return token::make_OPEN2( *yylloc );
                      }

<TEXT_STATE>"{{{"~?   {
                        BEGIN( INITIAL );
                        updateLocSingleLine();
                        return token::make_OPEN3( *yylloc );
                      }

<TEXT_STATE>[^{]*"{{~" |
<TEXT_STATE>[^{]*"{{{~" |
<TEXT_STATE>"{"[^{]*"{{~" |
<TEXT_STATE>"{"[^{]*"{{{~" {
                        // Put back the opening token
                        yyless( (*( yytext + yyleng - 4 ) == '{' )? yyleng - 4 : yyleng - 3 );
                        updateLoc();

                        // Remove all spaces from the end
                        yy_size_t len = yyleng;
                        decltype(yytext) last = yytext + yyleng;
                        while( len > 0 && isspace( *(--last) ))
                          --len;
                        if( len != 0 ) ++last;
                        *last = 0;

                        return token::make_TEXT( yytext, *yylloc );
                      }

<TEXT_STATE>"{{"~?[[:space:]]*else[[:space:]]*~?"}}" {
                        if( *( yytext + yyleng - 3 ) == '~' )
                          BEGIN( SPACE_STATE );
                        updateLoc();
                        return token::make_ELSE( *yylloc );
                      }

<TEXT_STATE>"{{"~?"+" {
                        BEGIN( INCLUDE_STATE );
                        updateLocSingleLine();
                      }

<INCLUDE_STATE>\"[^"\n]*\" |
<INCLUDE_STATE>'[^'\n]*' {
                        updateLocSingleLine();
                        *( yytext + yyleng - 1 ) = 0;
                        ++yytext;
                        //
                        if( m_streams.openFile( yytext )) {
                          m_context.debug( QString( "Handlebars: {{+ \"%1\" }}" ).arg( yytext ));
                          yypush_buffer_state( yy_create_buffer( m_streams.getCurrentStream(), YY_BUF_SIZE ));
                          yylloc = m_streams.getCurrentStreamLocation();
                          BEGIN( TEXT_STATE );
                        }
                        else
                          m_context.warning( QString( "Handlebars: {{+ \"%1\" }}: File not found." ).arg( yytext ));
                      }

<INCLUDE_STATE>[[:space:]]* {
                        updateLoc();
                        yylloc->step();
                      }

<INCLUDE_STATE>.      {
                        *yylloc += 1;
                        // ERROR
                      }

<COMMENT1_STATE,INCLUDE_STATE>"}}" {
                        BEGIN( TEXT_STATE );
                        updateLocSingleLine();
                      }

<COMMENT1_STATE,INCLUDE_STATE>"~}}" {
                        BEGIN( SPACE_STATE );
                        updateLocSingleLine();
                      }

<TEXT_STATE>"{{"~?!   {
                        BEGIN( COMMENT1_STATE );
                        updateLocSingleLine();
                      }


<TEXT_STATE>"{{!--"   {
                        BEGIN( COMMENT2_STATE );
                        updateLocSingleLine();
                      }


<COMMENT2_STATE>"--}}" {
                        BEGIN( TEXT_STATE );
                        updateLocSingleLine();
                      }

<COMMENT1_STATE,COMMENT2_STATE>[^-~}]*  { updateLoc(); }
<COMMENT1_STATE,COMMENT2_STATE>.        { *yylloc += 1; }

<SPACE_STATE>[[:space:]]* {
                        BEGIN( TEXT_STATE );
                        updateLoc();
                        yylloc->step();
                      }

<SPACE_STATE>.        {
                        BEGIN( TEXT_STATE );
                        yyless( 0 );
                      }

"}}"                  {
                        BEGIN( TEXT_STATE );
                        updateLocSingleLine();
                        return token::make_CLOSE2( *yylloc );
                      }

"~}}"                 {
                        BEGIN( SPACE_STATE );
                        updateLocSingleLine();
                        return token::make_CLOSE2( *yylloc );
                      }

"}}}"                 {
                        BEGIN( TEXT_STATE );
                        updateLocSingleLine();
                        return token::make_CLOSE3( *yylloc );
                      }

"~}}}"                 {
                        BEGIN( SPACE_STATE );
                        updateLocSingleLine();
                        return token::make_CLOSE3( *yylloc );
                      }

{ID}                  |
"["[^]\n]+"]"         {
                        updateLocSingleLine();
                        // Remove the square brackets
                        if( *yytext == '[' ) {
                          *( yytext + yyleng - 1 ) = 0; // ']'
                          ++yytext; // '['
                        }
                        // Decide what kind of identifier we have
                        QString id( yytext );
                        if( m_context.hasBlockHelper( id ))
                          return token::make_BLOCK_HELPER_IDENTIFIER( yytext, *yylloc );
                        if( m_context.hasHelper( id ))
                          return token::make_HELPER_IDENTIFIER( yytext, *yylloc );
                        return token::make_IDENTIFIER( yytext, *yylloc );
                      }

{ID}=                 {
                        updateLocSingleLine();
                        *( yytext + yyleng - 1 ) = 0; // Clear the "="
                        return token::make_HASHKEY( yytext, *yylloc );
                      }

\"[^"\n]*\"           |
'[^'\n]*'             {
                        updateLocSingleLine();
                        *( yytext + yyleng - 1 ) = 0;
                        return token::make_STRING( yytext + 1, *yylloc );
                      }

[[:space:]]+          {
                        updateLoc();
                        yylloc->step();
                      }

.                     {
                        *yylloc += 1;
                        return Bison::symbol_type( (Bison::token::yytokentype)(*yytext), *yylloc );
                      }

<<EOF>>               {
                        yypop_buffer_state();
                        if( YY_CURRENT_BUFFER ) {
                          m_streams.popStream();
                          // The Flex buffer remembered the previous istream
                          yylloc = m_streams.getCurrentStreamLocation();
                          BEGIN( INCLUDE_STATE );
                        } else {
                          return token::make_END( *yylloc );
                        }
                      }

%%

// vim:foldmethod=manual
