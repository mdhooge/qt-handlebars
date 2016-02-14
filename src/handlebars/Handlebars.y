%require "3.0.2"

%skeleton "lalr1.cc"
// /usr/share/bison/lalr1.cc
%language "C++"
%defines
//%verbose

%code requires {
  #include <QString>
  #include <QStringList>
  #include "HandlebarsNodes.h"
  namespace Handlebars {
    class Flex;
    class ParsingContext;
  }
}

%define api.namespace {Handlebars}
%define parser_class_name {Bison}
%parse-param { Handlebars::ParsingContext & context }
%parse-param { Handlebars::Flex & flex }


%locations
%define filename_type "const std::string"


%define parse.error verbose


%code {
  #include <sstream>
  #include "HandlebarsFlex.h"
  #include "HandlebarsParsingContext.h"

  #undef yylex
  #define yylex flex.lex

  using std::move;
}

%define api.value.type variant
%define api.token.constructor
%define parse.assert

%define api.token.prefix {TOK_}
%token END 0 "end of file"

%token <QString> TEXT
%token           OPEN2 OPEN3 ELSE CLOSE2 CLOSE3
%token <QString> IDENTIFIER HELPER_IDENTIFIER BLOCK_HELPER_IDENTIFIER HASHKEY
%token <QString> STRING

%type  <Node*> handlebars

%type  <Node*> expression
%type  <QStringList> dot_separated_identifiers

%type  <Node*> partial

%type  <Node*> helper inner_helper
%type  <Node*> parameter
%type  <NodeList> parameters_list
%type  <NodeHash> parameters_hash

%type  <Node*> block
%type  <BlockHelperNode*> block_open
%type  <NodeList> block_inner
%type  <QString> block_end

%define parse.trace
 // See 8.4 Tracing Your Parser, p142
 // set_debug_level()
%printer { yyoutput << '"' << $$.toStdString() << '"'; } <QString>;

%%

template:
  %empty
| template handlebars   { context.addNode( $2 ); }
;

handlebars:
  TEXT                  { $$ = new StringNode( $1 ); }
| expression            { $$ = $1; }
| partial               { $$ = $1; }
| helper                { $$ = $1; }
| block                 { $$ = $1; }
| error CLOSE2          { yyerrok; }
| error CLOSE3          { yyerrok; }
;

expression:
  OPEN2 dot_separated_identifiers CLOSE2 { $$ = new PropertyNode( move( $2 )); $$->setEscape(); }
| OPEN3 dot_separated_identifiers CLOSE3 { $$ = new PropertyNode( move( $2 )); }
;

dot_separated_identifiers:
  IDENTIFIER            { $$ += $1; }
| dot_separated_identifiers '.' IDENTIFIER { $$.swap( $1 ); $$ += $3; }
| dot_separated_identifiers '/' IDENTIFIER { $$.swap( $1 ); $$ += $3; }
;

partial:
  OPEN2 '>' IDENTIFIER CLOSE2 { $$ = new PartialNode( $IDENTIFIER ); $$->setEscape(); }
| OPEN3 '>' IDENTIFIER CLOSE3 { $$ = new PartialNode( $IDENTIFIER ); }
;

helper:
  OPEN2 inner_helper CLOSE2 { $$ = $2; $$->setEscape(); }
| OPEN3 inner_helper CLOSE3 { $$ = $2; }
;

inner_helper:
  HELPER_IDENTIFIER parameters_list parameters_hash
                        { $$ = new HelperNode( $1, move( $2 ), move( $3 )); }
;

parameters_list:
  %empty                {}
| parameters_list parameter { $$.swap( $1 ); $$ += $2; }
;

parameters_hash:
  %empty                {}
| parameters_hash HASHKEY parameter {
                          $$.swap( $1 );
                          $$.insert( $2, $3 );
                        }

parameter:
  STRING                { $$ = new StringNode( $1 ); }
| dot_separated_identifiers
                        { // Try to detect integer
                          if( $1.size() == 1 ) {
                            bool ok;
                            qint64 number { $1.at(0).toLongLong( &ok, 0 ) };
                            if( ok ) {
                              $$ = new IntegerNode( number );
                              break;
                            }
                          }
                          $$ = new PropertyNode( move( $1 ));
                        }
| '(' inner_helper ')'  { $$ = $2; }
;

block:
  block_open block_inner block_end
                        {
                          if( $block_open->name() != $block_end ) {
                            std::ostringstream msg;
                            msg << "Block mismatch {{#" << $block_open->name().toStdString() << "}}";
                            error( @block_open, msg.str() );
                            msg.seekp( 0 );
                            msg << "Block mismatch {{/" << $block_end.toStdString() << "}}";
                            error( @block_end, msg.str() );
                            YYABORT;
                          }
                          $1->setInnerBlock( move( $2 ));
                          $$ = $1;
                        }
| block_open block_inner ELSE block_inner block_end
                        {
                          if( $block_open->name() != $block_end ) {
                            std::ostringstream msg;
                            msg << "Block mismatch {{#" << $block_open->name().toStdString() << "}}";
                            error( @block_open, msg.str() );
                            msg.seekp( 0 );
                            msg << "Block mismatch {{else}}";
                            error( @ELSE, msg.str() );
                            msg.seekp( 0 );
                            msg << "Block mismatch {{/" << $block_end.toStdString() << "}}";
                            error( @block_end, msg.str() );
                            YYABORT;
                          }
                          $1->setInnerBlocks( move( $2 ), move( $4 ));
                          $$ = $1;
                        }
;

block_open:
  OPEN2 '#' BLOCK_HELPER_IDENTIFIER parameters_list parameters_hash CLOSE2
                        { $$ = new BlockHelperNode( $BLOCK_HELPER_IDENTIFIER, move( $parameters_list ), move( $parameters_hash )); }
;

block_inner:
  %empty                 {}
| block_inner handlebars { $$.swap( $1 ); $$ += $handlebars; }
;

block_end:
  OPEN2 '/' BLOCK_HELPER_IDENTIFIER CLOSE2
                        { $$.swap( $BLOCK_HELPER_IDENTIFIER ); }
;

%%

void
Handlebars::Bison::error( const location_type& loc, const std::string & msg )
{
  std::ostringstream output;
  output << loc << ':' << msg;
  context.error( QString::fromStdString( output.str() ));
}
