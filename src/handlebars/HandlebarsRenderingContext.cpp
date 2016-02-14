#include "HandlebarsRenderingContext.h"

namespace Handlebars {

RenderingContext::RenderingContext(
  escape_fn escape,
  const helpers & helpers,
  const block_helpers & block_helpers,
  LoggerInterface & logger
  ) :
  m_logger( logger ),
  m_escape_fn( escape ),
  m_helpers( helpers ),
  m_block_helpers( block_helpers )
{
}

void
RenderingContext::render( const NodeList & nodes, QTextStream * output )
{
  QTextStream* previous = m_output;
  m_output = output;

  render( nodes );

  m_output = previous;
}

void
RenderingContext::render( const NodeList & nodes )
{
  if( m_output == nullptr )
    m_logger.error( "Handlebars: RenderingContext: No output defined." );

  else
    foreach( Node * node, nodes )
      * m_output << node->toString( *this ) << flush;
}

void
RenderingContext::output( const QString& text )
{
  if( m_output == nullptr )
    m_logger.error( "Handlebars: RenderingContext: No output defined." );

  else
      * m_output << text << flush;
}


// ###
// ### Helpers
// ###

QVariant
RenderingContext::callHelper(
  const QString & name,
  const helper_params & params,
  const helper_options & opt
  ) const
{
  auto helper = m_helpers.value( name );
  return helper( *this, params, opt );
}

void
RenderingContext::callBlockHelper(
  const QString & name,
  const helper_params & params,
  const helper_options & opt,
  const NodeList & first,
  const NodeList & last
  )
{
  auto block_helper = m_block_helpers.value( name );
  block_helper( *this, params, opt, first, last );
}


void
RenderingContext::registerPartial( const QString& name, const NodeList& partial )
{
  m_partials.insert( name, partial );
}

// ###
// ### Properties Management
// ###

/**
 * Returns true if getProperty() returns a valid QVariant
 */
bool
RenderingContext::hasProperty( const QString& name )
{
  return getProperty( name ).isValid();
}

/**
 * Add the (name,value) pair to current context (if possible given current context type).
 *
 * \note This method is *not* recommended to add a property because plain
 *       QVariant cannot be directly changed and a work-around is used.
 *       If you have a *write* access to current outer context, use it instead!
 *
 * \note The properties stack *MUST* not be empty (this should always be the case).
 */
void
RenderingContext::addProperty(
  const QString& name,
  const QVariant& value)
{
  Q_ASSERT_X( ! m_propertiesStack.isEmpty(), "RenderingContext::addProperty", "Expecting a context" );

  // Cannot change "in place", so we pop here and push back at the end
  auto context = m_propertiesStack.takeLast();

  auto type = QMetaType::Type( context.type() );
  switch( type )
  {
    case QMetaType::QVariantHash:
      {
        QVariantHash hash( context.toHash() );
        hash.insert( name, value );
        m_propertiesStack.append( hash );
      } break;

    case QMetaType::QVariantMap:
      {
        QVariantMap map( context.toMap() );
        map.insert( name, value );
        m_propertiesStack.append( map );
      } break;

    case QMetaType::QObjectStar:
    case QMetaType::User:
      {
        QObject* object( context.value<QObject*>() );
        if( object != nullptr ) {
          object->setProperty( qPrintable( name ), value );
          m_propertiesStack.append( QVariant::fromValue( object ));
        }
        else
          m_propertiesStack.append( context );
      } break;

    default:
      m_propertiesStack.append( context ); // Push back the context -- no luck
      warning( QString( "Property '%1' cannot be added to current context" ).arg( name ));
      break;
  }
}

QVariant
RenderingContext::getProperty( const QString& identifier ) const
{
  QVariant current;
  int stack_level = m_propertiesStack.size();
  while( ! current.isValid() && --stack_level >= 0 )
    current = findPropertyInContext( identifier, m_propertiesStack.at( stack_level ) );
  return current;
}

QVariant
RenderingContext::getProperty( const QStringList& identifiers ) const
{
  const int identifiers_size = identifiers.size();

  QVariant current;

  for( int stack_level = m_propertiesStack.size(); --stack_level >= 0; )
  {
    current = m_propertiesStack.at( stack_level );

    for( int identifier_pos = 0; identifier_pos < identifiers_size; ++identifier_pos )
    {
      current = findPropertyInContext( identifiers.at( identifier_pos ), current );
      if( ! current.isValid() )
        break;
    }

    if( current.isValid() )
      break;
  }

  return current;
}

bool
RenderingContext::propertyAsBool( const QVariant& value ) const
{
  bool result;
  auto type( QMetaType::Type( value.type() ));
  switch( type )
  {
    case QMetaType::QVariantHash: {
      QVariantHash container( value.value< QVariantHash > () );
      result = ! container.isEmpty();
      } break;
    case QMetaType::QVariantList: {
      QVariantList container( value.value< QVariantList > () );
      result = ! container.isEmpty();
      } break;
    case QMetaType::QVariantMap: {
      QVariantMap container( value.value< QVariantMap > () );
      result = ! container.isEmpty();
      } break;
    case QMetaType::QObjectStar:
    case QMetaType::User: {
      QObject* object( value.value<QObject*>() );
      result = object != nullptr;
      } break;

    default:
      result = value.toBool();
      break;
  }
  return result;
}

QVariant
RenderingContext::findPropertyInContext( const QString& identifier, const QVariant& context )
{
  QVariant value;
  auto type = QMetaType::Type(context.type());

  switch( type )
  {
    case QMetaType::QVariantHash:
      value = findPropertyInContext<QHash>( identifier, context );
      break;

    case QMetaType::QVariantList:
      value = findPropertyInContext<QList>( identifier, context );
      break;

    case QMetaType::QVariantMap:
      value = findPropertyInContext<QMap>( identifier, context );
      break;

    case QMetaType::QObjectStar:
    case QMetaType::User:
      {
        QObject* object( context.value<QObject*>() );
        if( object != nullptr )
        {
          value = object->property( qPrintable( identifier ));
          // Add some magic around QObject methods
          if( ! value.isValid() )
          {
            if( identifier == "name" || identifier == "objectName" )
              value = object->objectName();
            else if( identifier == "parent" )
              value.setValue( object->parent() );
            else if( identifier == "className" )
              value.setValue( QString( object->metaObject()->className() ));
          }
        }
      } break;

    default:
      break;
  }

  return value;
}

/**
 * Search a property in a Container of type C< QVariant >
 *
 * \note The "inner,hidden type" of the given QVariant context parameter must
 *       match the template "explicit" type of this method. Otherwise the
 *       conversion will likely result in an empty container.
 *
 *       Fortunately, this method cannot be automatically chosen by the
 *       compiler. So if you call it, you likely know what you're doing!
 */
template< template<typename> class C>
QVariant
RenderingContext::findPropertyInContext( const QString& identifier, const QVariant& context )
{
  // Convert the "anonymous/global" QVariant context given as parameter into
  // a container of the corresponding template type.  The fact that the
  // conversion will succeed has been taken into account by the caller
  // (normally it is the "not-templatized" findPropertyInContext method).
  C< QVariant > container( context.value< C< QVariant > > () );

  if( identifier == "length" || identifier == "size" )
    return container.size();

  bool ok;
  int index( identifier.toInt( &ok ) );
  if( ok && index < container.size() )
    return container.at( index );

  return QVariant();
}

/**
 * Search a property in a Container of type C< QString, QVariant >
 *
 * \note The "inner,hidden type" of the given QVariant context parameter must
 *       match the template "explicit" type of this method. Otherwise the
 *       conversion will likely result in an empty container.
 *
 *       Fortunately, this method cannot be automatically chosen by the
 *       compiler. So if you call it, you likely know what you're doing!
 */
template< template<typename,typename> class C>
QVariant
RenderingContext::findPropertyInContext( const QString& identifier, const QVariant& context )
{
  // Convert the "anonymous/global" QVariant context given as parameter into
  // a container of the corresponding template type.  The fact that the
  // conversion will succeed has been taken into account by the caller
  // (normally it is the "not-templatized" findPropertyInContext method).
  C< QString,QVariant > container( context.value< C< QString,QVariant > > () );

  // Retrieve value from identifier
  QVariant value( container.value( identifier ));

  // Handle special cases
  if( ! value.isValid() )
  {
    if( identifier == "length" )
      value = container.size();
  }

  return value;
}

}// namespace Handlebars
