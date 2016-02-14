#include "HandlebarsNodes.h"

#include "HandlebarsRenderingContext.h"

namespace Handlebars {

QString
Node::toString( RenderingContext & c ) const
{
  QString text( toQVariant(c).toString() );
  if( m_escape )
    text = c.escape( text );
  return text;
}

QVariant
PropertyNode::toQVariant( RenderingContext & c ) const
{
  return c.getProperty( m_path );
}

QVariant
PartialNode::toQVariant( RenderingContext & c ) const
{
  // Use temporary string to collect partial output
  QString output;
  QTextStream stream( & output, QIODevice::WriteOnly );

  // Retrieve partial nodes
  NodeList partial( c.getPartial( m_name ));
  if( partial.isEmpty() )
    c.warning( QString( "Handlebars: Partial \"%1\" not found." ).arg( m_name ));
  else
    c.render( partial );

  return output;
}

HelperNode::~HelperNode()
{
  qDeleteAll( m_params );
  qDeleteAll( m_options );
}

QVariant
HelperNode::toQVariant( RenderingContext & c ) const
{
  return c.callHelper(
    m_name,
    NodeList_to_QVariant( c, m_params ),
    NodeHash_to_QVariant( c, m_options )
    );
}

BlockHelperNode::~BlockHelperNode()
{
  qDeleteAll( m_params );
  qDeleteAll( m_options );
  qDeleteAll( m_first );
  qDeleteAll( m_last );
}

QVariant
BlockHelperNode::toQVariant( RenderingContext & c ) const
{
  c.callBlockHelper(
    m_name,
    NodeList_to_QVariant( c, m_params ),
    NodeHash_to_QVariant( c, m_options ),
    m_first,
    m_last
    );
  return QVariant();
}



QVariantList
NodeList_to_QVariant( RenderingContext & c, const NodeList & in )
{
  QVariantList out;
  foreach( Node* node, in )
    out.append( node->toQVariant( c ));
  return out;
}

QVariantHash
NodeHash_to_QVariant( RenderingContext & c, const NodeHash & in )
{
  QVariantHash out;
  for( auto i = in.constBegin(), end = in.constEnd(); i != end; ++i )
    out.insert( i.key(), i.value()->toQVariant( c ));
  return out;
}

}// namespace Handlebars
