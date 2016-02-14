#ifndef HANDLEBARS_NODES_H
#define HANDLEBARS_NODES_H

#include <QHash>
#include <QList>
#include <QString>
#include <QStringList>
#include <QVariant>

namespace Handlebars {

class RenderingContext;

class Node;
using NodeList = QList<Node*>; // !! qDeleteAll must be applied when the list goes out of scope
using NodeHash = QHash<QString,Node*>; // !! qDeleteAll must be applied when the hash goes out of scope


/**
 * The Node class is the abstract class used as front end for all real nodes.
 */
class Node
{
public:
  Node() :
    m_escape( false )
    {}
  virtual ~Node() = default;
  virtual QString toString( RenderingContext & c ) const;
  virtual QVariant toQVariant( RenderingContext & ) const = 0;
  void setEscape( bool v = true ) { m_escape = v; }
private:
  bool m_escape;
};

/**
 * The StringNode class holds a plain string (maybe multi-line) to output.
 */
class StringNode : public Node
{
public:
  StringNode( const QString& value ) :
    m_value( value )
    {}
  QString toString( RenderingContext & ) const override { return m_value; }
  QVariant toQVariant( RenderingContext & ) const override { return m_value; }
private:
  QString m_value;
};

/**
 * The IntegerNode class contains a long int value (to be used as param for helper).
 */
class IntegerNode : public Node
{
public:
  IntegerNode( qint64 value ) :
    m_value( value )
    {}
  QString toString( RenderingContext & ) const override { return QString::number( m_value ); }
  QVariant toQVariant( RenderingContext & ) const override { return m_value; }
private:
  qint64 m_value;
};

/**
 * The PropertyNode class holds a reference to a property name to be rendered
 * later, depending on provided context.
 */
class PropertyNode : public Node
{
public:
  PropertyNode( QStringList && value ) :
    m_path( value )
    {}
  QVariant toQVariant( RenderingContext & ) const override;
private:
  QStringList m_path;
};

/**
 * The PartialNode class holds a reference to a partial to be rendered later.
 */
class PartialNode : public Node
{
public:
  PartialNode( const QString& name ) :
    m_name( name )
    {}
  QVariant toQVariant( RenderingContext & ) const override;
private:
  QString m_name;
};

/**
 * The HelperNode class holds a reference to a non-block helper.
 */
class HelperNode : public Node
{
public:
  HelperNode( const QString & name, NodeList && params, NodeHash && options ) :
    m_name( name ),
    m_params( params ),
    m_options( options )
    {}
  ~HelperNode() override;
  QVariant toQVariant( RenderingContext & ) const override;
protected:
  QString m_name;
  NodeList m_params;
  NodeHash m_options;
};

/**
 * The BlockHelperNode class holds a reference to a block helper.
 */
class BlockHelperNode : public Node
{
public:
  BlockHelperNode( const QString & name, NodeList && params, NodeHash && options ) :
    m_name( name ),
    m_params( params ),
    m_options( options )
    {}
  ~BlockHelperNode() override;
  QVariant toQVariant( RenderingContext & ) const override;
  QString name() const { return m_name; }
  void setInnerBlock( NodeList && first ) { m_first = first; }
  void setInnerBlocks( NodeList && first, NodeList && last ) { m_first = first; m_last = last; }
private:
  QString m_name;
  NodeList m_params;
  NodeHash m_options;
  NodeList m_first;
  NodeList m_last;
};

/**
 * The method "executes" all the Node instances to produce a QVariant,
 * depending on the current context.
 */
QVariantList NodeList_to_QVariant( RenderingContext &, const NodeList & );

/**
 * The method "executes" all the Node instances to produce a QVariant,
 * depending on the current context.
 */
QVariantHash NodeHash_to_QVariant( RenderingContext &, const NodeHash & );

}// namespace Handlebars

#endif // HANDLEBARS_NODES_H
