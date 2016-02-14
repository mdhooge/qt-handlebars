#include "HandlebarsParser.h"

#include "HandlebarsIStreamManager.h"
#include "HandlebarsLoggerInterface.h"
#include "HandlebarsNodes.h"
#include "HandlebarsParsingContext.h"

#include "HandlebarsFlex.h"
#include "Handlebars.y.hh"


namespace Handlebars {

Parser::Parser( LoggerInterface& logger ) :
  m_default_stdout( stdout ),
  m_output( & m_default_stdout ),
  m_logger( logger )
{
}

Parser::~Parser()
{
  qDeleteAll( m_nodes );
}


// ###
// ### Handlebars Parser & Renderer
// ###

bool
Parser::parse( IStreamManager& streams )
{
  // Purge old nodes
  qDeleteAll( m_nodes );
  m_nodes.clear();

  // Parsing environment
  ParsingContext parsingContext(
    m_nodes,
    m_helpers,
    m_block_helpers,
    m_logger
    );

  // Lexical scanner
  Flex flex( streams, parsingContext );
  flex.set_debug( m_flexDebugFlag );

  // Handlebars Parser
  Bison bison( parsingContext, flex );
#if YYDEBUG
  bison.set_debug_level( m_bisonDebugLevel );
#endif

  // Parse template into Node tree
  m_logger.debug( "Handlebars: Parsing Input..." );
  int result = bison.parse();
  m_logger.debug( "Handlebars: Parsing done." );

  return ( result == 0 );
}

void
Parser::render( PropertiesContext properties )
{
  RenderingContext context(
    m_escape_fn,
    m_helpers,
    m_block_helpers,
    m_logger
    );
  context.pushPropertiesContext( properties );

  m_logger.debug( "Handlebars: Rendering..." );
  context.render( m_nodes, m_output );
  m_logger.debug( "Handlebars: Rendering done." );
}


// ###
// ### Output Streams
// ###

void
Parser::setOutputStream( QTextStream * out )
{
  m_output = ( out != nullptr )? out : & m_default_stdout;
}


// ###
// ### Default Block Helpers
// ###

/**
 * Loops over a Container
 *
 * The Container can be any class providing methods: isEmpty(), size() and at().
 * The class typename returned by at() must offer a conversion to QVariant (for
 * example, QObject*).
 */
template< typename C >
static
void eachLoopHelper(
  RenderingContext & context,
  const C & container,
  const NodeList & truthy,
  const NodeList & falsy
  )
{
  if( container.isEmpty() )
    context.render( falsy );

  else {
    // A temporary, intermediate context with data about current loop step
    QVariantHash step;

    for( int i = 0, last = container.size() - 1; i <= last; ++i )
    {
      QVariant value( QVariant::fromValue( container.at( i ) ));

      step.clear();
      step.insert( "@index0", i );
      step.insert( "@index", i+1 );
      step.insert( "this", value );
      step.insert( "@first", i == 0 );
      step.insert( "@last",  i == last );

      context.pushPropertiesContext( step );
      context.pushPropertiesContext( value );
      context.render( truthy );
      context.popPropertiesContext();
      context.popPropertiesContext();
    }
  }
}

/**
 * Loops over a Container of type C< QVariant >
 *
 * \note The "inner,hidden type" of the given QVariant property parameter must
 *       match the template "explicit" type of this method. Otherwise the
 *       conversion will likely result in an empty container.
 *
 *       Fortunately, this method cannot be automatically chosen by the
 *       compiler. So if you call it, you likely know what you're doing!
 */
template< template<typename> class C >
static
void eachLoopHelper(
  RenderingContext & context,
  const QVariant& property,
  const NodeList & truthy,
  const NodeList & falsy
  )
{
  // Convert the "anonymous/global" QVariant property given as parameter into
  // a container of the corresponding template type.  The fact that the
  // conversion will succeed has been taken into account by the caller
  // (normally it is the "each" helper function).
  C< QVariant > container( property.value< C< QVariant > > () );
  // Then fall-back to the more generic templated method
  eachLoopHelper( context, container, truthy, falsy );
}

/**
 * Loops over a Container of type C< QString, QVariant >
 *
 * \note The "inner,hidden type" of the given QVariant property parameter must
 *       match the template "explicit" type of this method. Otherwise the
 *       conversion will likely result in an empty container.
 *
 *       Fortunately, this method cannot be automatically chosen by the
 *       compiler. So if you call it, you likely know what you're doing!
 */
template< template<typename,typename> class C >
static
void eachLoopHelper(
  RenderingContext & context,
  const QVariant& property,
  const NodeList & truthy,
  const NodeList & falsy
  )
{
  // Convert the "anonymous/global" QVariant property given as parameter into
  // a container of the corresponding template type.  The fact that the
  // conversion will succeed has been taken into account by the caller
  // (normally it is the "each" helper function).
  C< QString,QVariant > container( property.value< C< QString,QVariant > > () );

  if( container.isEmpty() )
    context.render( falsy );

  else {
    // A temporary, intermediate context with data about current loop step
    QVariantHash step;
    int n = 0, last = container.size() - 1;

    for(
      auto i = container.constBegin(), end = container.constEnd();
      i != end;
      ++i, ++n )
    {
      step.clear();
      step.insert( "@index0", n );
      step.insert( "@index", n+1 );
      step.insert( "@key", i.key() );
      step.insert( "this", i.value() );
      step.insert( "@first", n == 0 );
      step.insert( "@last",  n == last );

      context.pushPropertiesContext( step );
      context.pushPropertiesContext( i.value() );
      context.render( truthy );
      context.popPropertiesContext();
      context.popPropertiesContext();
    }
  }
}

/**
 * Register the helpers expected by any Handlebars user
 */
void
Parser::registerDefaultHelpers()
{

  registerBlockHelper(
    "each", [] (
      RenderingContext & context,
      const helper_params & params,
      const helper_options &,
      const NodeList & truthy,
      const NodeList & falsy
      )
    {
      if( params.size() != 1 ) return; // RTFM!
      QVariant value( params.at( 0 ));
      //
      auto type( QMetaType::Type( value.type() ));
      switch( type )
      {
        case QMetaType::QVariantHash:
          eachLoopHelper <QHash> ( context, value, truthy, falsy );
          break;
        case QMetaType::QVariantList:
          eachLoopHelper <QList> ( context, value, truthy, falsy );
          break;
        case QMetaType::QVariantMap:
          eachLoopHelper <QMap> ( context, value, truthy, falsy );
          break;
        case QMetaType::QObjectStar:
        case QMetaType::User:
          {
            QObject* object( value.value<QObject*>() );
            if( object != nullptr )
            {
              auto children( object->findChildren<QObject*>( QString(), Qt::FindDirectChildrenOnly ));
              eachLoopHelper( context, children, truthy, falsy );
            }
          } break;
        default:
          context.render( falsy );
          break;
      }
    } );

  registerBlockHelper(
    "if", [] (
      RenderingContext & context,
      const helper_params & params,
      const helper_options &,
      const NodeList & truthy,
      const NodeList & falsy
      )
    {
      QVariant value( params.value( 0 ));
      context.render( context.propertyAsBool( value ) ? truthy : falsy );
    } );

  registerBlockHelper(
    "registerPartial", [] (
      RenderingContext & context,
      const helper_params & params,
      const helper_options &,
      const NodeList & partial,
      const NodeList &
      )
    {
      if( params.size() == 1 ) {
        context.registerPartial( params.at( 0 ).toString(), partial );
      }
    } );

  registerBlockHelper(
    "unless", [] (
      RenderingContext & context,
      const helper_params & params,
      const helper_options &,
      const NodeList & truthy,
      const NodeList & falsy
      )
    {
      QVariant value( params.value( 0 ));
      context.render( context.propertyAsBool( value ) ? falsy : truthy );
    } );

  registerBlockHelper(
    "with", [] (
      RenderingContext & context,
      const helper_params & params,
      const helper_options &,
      const NodeList & inner,
      const NodeList &
      )
    {
      if( params.size() == 1 ) {
        context.pushPropertiesContext( params.at( 0 ));
        context.render( inner );
        context.popPropertiesContext();
      }
    } );

}

}// namespace Handlebars
