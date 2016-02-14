#ifndef HANDLEBARS_PARSER_H
#define HANDLEBARS_PARSER_H

#include <QString>
#include <QTextStream>

#include "HandlebarsHelpers.h"
#include "HandlebarsRenderingContext.h"

namespace Handlebars {

class IStreamManager;
class LoggerInterface;

class Parser
{
public:

  Parser( LoggerInterface& );
  ~Parser();

/// \name Parser & Renderer
/// \{
public:
  bool parse( IStreamManager& );
  void render( PropertiesContext );

private:
  NodeList m_nodes;
/// \}

/// \name Output Streams
/// The default output streams is stdout.
/// \{
public:
  void setOutputStream( QTextStream * out );

  void setEscapeFunction( escape_fn f ) { m_escape_fn = f; }

private:
  QTextStream m_default_stdout;
  QTextStream * m_output;

  escape_fn m_escape_fn;

  LoggerInterface& m_logger;
/// \}


/// \name Context
/// The context to use when rendering the template
/// \{
public:
  void registerHelper( const QString & name, helper_fn f ) { m_helpers.insert( name, f ); }
  void registerBlockHelper( const QString & name, block_helper_fn f ) { m_block_helpers.insert( name, f ); }

  void registerDefaultHelpers();
  // {{# each <container> }} ... {{ else }} empty - or not a container {{/ each }}
  // {{# if <truthy> }} TRUE {{ else }} FALSE {{/ if }}
  // {{# registerPartial <partial-name> }} ... {{/ registerPartial }}
  // {{# unless <false> }} FALSE {{else}} TRUE {{/ unless }}
  // {{# with <property> }} ... {{/ with }}

private:
  helpers m_helpers;
  block_helpers m_block_helpers;
/// \} Context


/// \name Debug
/// \{
public:
  void setBisonDebugLevel( int l ) { m_bisonDebugLevel = l; }
  void setFlexDebugFlag( int f ) { m_flexDebugFlag = f; }

private:
  int m_bisonDebugLevel = 0;
  int m_flexDebugFlag = 0;
/// \}


};

}// namespace Handlebars

#endif // HANDLEBARS_PARSER_H
