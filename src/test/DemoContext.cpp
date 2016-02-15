#include "DemoContext.h"


void
initQVariants( QVariantHash & context )
{
  context.insert( "F4LSE", false );
  context.insert( "TRU3", true );
  context.insert( "foo", "FOO" );
  context.insert( "bar", "BAR" );
  context.insert( "html", "<b>BOLD</b>" );
  context.insert( "zero", 0 );
  context.insert( "forty-two", 42 );
  context.insert( "æâêîœßð", "UNICODE" );

  QVariantMap sub1;
  QVariantHash subsub2;
  subsub2.insert( "alpha", "ALPHA" );
  subsub2.insert( "bravo", "BRAVO" );
  subsub2.insert( "f.o/o", "FOO-t9" );
  sub1.insert( "y1", "Y1" );
  sub1.insert( "z2", "Z2" );
  sub1.insert( "t9", subsub2 );
  sub1.insert( "foo", "FOO-x0" );
  context.insert( "x0", sub1 );

  QVariantList vec;
  QVariantMap  submap;
  QVariantHash subhash;
  submap[ "name" ] = "vec1"; vec.append( QVariantMap( submap ));
  submap[ "name" ] = "vec2"; vec.append( QVariantMap( submap ));
  subhash[ "name" ] = "vec3"; vec.append( QVariantHash( subhash ));
  context.insert( "vec", vec );

  context.insert( "3MPTY", QVariantList() );
  context.insert( "EmptyH", QVariantHash() );
  context.insert( "EmptyM", QVariantMap() );
}


void
initQObjects( QVariantHash & context )
{
  DemoRoot* root = new DemoRoot();
  root->setObjectName( "r0ot" );

  DemoChild* child;

  child = new DemoChild();
  child->setObjectName( "Child #1" );
  child->m_id = 1337;
  child->setParent( root );

  child = new DemoChild();
  child->setObjectName( "Child #2" );
  child->m_id = 31173;
  child->setParent( root );

  child = new DemoChild();
  child->setObjectName( "Child #3" );
  child->m_id = 12345;
  child->setParent( root );

  context.insert( "R00T", QVariant::fromValue( root ));
}

void
cleanQObjects( QVariantHash & context )
{
  auto obj = context[ "R00T" ];
  DemoRoot* root = qobject_cast<DemoRoot*>( obj.value<QObject*>() );
  delete root;
}


QVariantList
DemoRoot::getChildren() const
{
  auto children( findChildren<DemoChild*>( QString(), Qt::FindDirectChildrenOnly ));
  QVariantList out;
  for( auto i( children.cbegin() ); i != children.cend(); ++i )
    out.append( QVariant::fromValue( *i ));
  return out;
}
