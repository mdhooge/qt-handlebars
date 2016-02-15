#ifndef DEMOCONTEXT_H
#define DEMOCONTEXT_H

#include <QVariantHash>
#include <QVariantList>
#include <QVariantMap>


void initQVariants( QVariantHash & context );
void initQObjects( QVariantHash & context );

void cleanQObjects( QVariantHash & context );

/**
 * The DemoChild class has an ID property
 */
class DemoChild : public QObject
{
  Q_OBJECT
public:

  DemoChild() {};

  Q_PROPERTY( int ID MEMBER m_id )
  int m_id;

private:
  Q_DISABLE_COPY(DemoChild);
};


/**
 * The DemoRoot class contains DemoChild instances that can be retrieved
 * through the children property.
 */
class DemoRoot : public QObject
{
  Q_OBJECT
public:

  DemoRoot() {};

  Q_PROPERTY( QVariantList children READ getChildren )
  QVariantList getChildren() const;

private:
  Q_DISABLE_COPY(DemoRoot);
};


#endif // DEMOCONTEXT_H
