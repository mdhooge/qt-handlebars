#ifndef HANDLEBARS_RENDERING_CONTEXT_H
#define HANDLEBARS_RENDERING_CONTEXT_H

#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QVariant>

#include "HandlebarsHelpers.h"
#include "HandlebarsLoggerInterface.h"
#include "HandlebarsNodes.h"

namespace Handlebars {


using PropertiesContext = QVariant;


class RenderingContext
{
public:

  RenderingContext( escape_fn, const helpers &, const block_helpers &, LoggerInterface & );


  void render( const NodeList &, QTextStream * output );
  void render( const NodeList & );
  void output( const QString& );


  QString escape( const QString& str ) const { return m_escape_fn? m_escape_fn( str ) : str; }


  QVariant callHelper(
    const QString & name,
    const helper_params &,
    const helper_options & ) const;

  void callBlockHelper(
    const QString & name,
    const helper_params &,
    const helper_options &,
    const NodeList &,
    const NodeList & );


  void registerPartial( const QString& name, const NodeList& partial );
  NodeList getPartial( const QString& name ) const { return m_partials[ name ]; }


  void pushPropertiesContext( const PropertiesContext& context ) { m_propertiesStack.append( context ); }
  void popPropertiesContext() { m_propertiesStack.removeLast(); }

  bool hasProperty( const QString& name );
  void addProperty( const QString& name, const QVariant& value );

  QVariant getProperty( const QString& identifier ) const;
  QVariant getProperty( const QStringList& identifiers ) const;

  bool propertyAsBool( const QVariant& ) const;


  void debug  ( const QString& msg ) const { m_logger.debug  ( msg ); }
  void info   ( const QString& msg ) const { m_logger.info   ( msg ); }
  void warning( const QString& msg ) const { m_logger.warning( msg ); }
  void error  ( const QString& msg ) const { m_logger.error  ( msg ); }


private:

  QTextStream * m_output;
  LoggerInterface & m_logger;

  escape_fn m_escape_fn;
  const helpers & m_helpers;
  const block_helpers & m_block_helpers;

  QHash<QString,NodeList> m_partials;

  QVariantList m_propertiesStack;

public:
  static QVariant findPropertyInContext( const QString& identifier, const PropertiesContext & context );

private:
  template< template<typename> class Container>
  static QVariant findPropertyInContext( const QString& identifier, const PropertiesContext & context );

  template< template<typename,typename> class Container>
  static QVariant findPropertyInContext( const QString& identifier, const PropertiesContext & context );

};

}// namespace Handlebars

#endif // HANDLEBARS_RENDERING_CONTEXT_H
