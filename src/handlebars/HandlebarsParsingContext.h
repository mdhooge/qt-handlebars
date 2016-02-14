#ifndef HANDLEBARS_PARSING_CONTEXT_H
#define HANDLEBARS_PARSING_CONTEXT_H

#include <QList>

#include "HandlebarsHelpers.h"
#include "HandlebarsLoggerInterface.h"

namespace Handlebars {


class Node;


using parsing_error_fn = std::function< void ( const QString& ) >;


class ParsingContext
{
public:

  ParsingContext(
    QList<Node*> & nodes,
    helpers & helpers,
    block_helpers & block_helpers,
    LoggerInterface& logger
    );

  bool hasHelper( const QString & name ) const { return m_helpers.contains( name ); }
  bool hasBlockHelper( const QString & name ) const { return m_block_helpers.contains( name ); }

  void addNode( Node * node ) { m_nodes.append( node ); }

  void debug  ( const QString& msg ) const { m_logger.debug  ( msg ); }
  void info   ( const QString& msg ) const { m_logger.info   ( msg ); }
  void warning( const QString& msg ) const { m_logger.warning( msg ); }
  void error  ( const QString& msg ) const { m_logger.error  ( msg ); }

private:

  QList<Node*> & m_nodes;
  const helpers & m_helpers;
  const block_helpers & m_block_helpers;
  LoggerInterface & m_logger;
};

}// namespace Handlebars

#endif // HANDLEBARS_PARSING_CONTEXT_H
