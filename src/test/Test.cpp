#include <QtTest/QtTest>
#include <QTextStream>

#include "HandlebarsIStreamManager.h"
#include "HandlebarsParser.h"
#include "ExtraHelpers.h"
using namespace Handlebars;

#include "ConsoleLogger.h"
#include "DemoContext.h"


class Test : public QObject
{
  Q_OBJECT
public:
  Test();

private slots:

  void initTestCase();

  void basic_data();
  void basic();

  void escape();

private:
  ConsoleLogger m_logger;
  Parser m_parser;
  QString m_output;
  QTextStream m_stream;
  QVariantHash m_context;

  QString render( const QString& );
};

Test::Test() :
  m_parser( m_logger ),
  m_stream( & m_output, QIODevice::WriteOnly )
{
  m_parser.setOutputStream( & m_stream );
  m_parser.registerDefaultHelpers();
}

void
Test::initTestCase()
{
  initQVariants( m_context );
  initQObjects( m_context );
}

QString
Test::render( const QString& tmplate )
{
  m_output.clear();
  IStreamManager streams;
  streams.useString( tmplate.toStdString() );
  m_parser.parse( streams );
  m_parser.render( m_context );
  return m_output;
}


void
Test::basic_data()
{
  QTest::addColumn<QString>("tmplate");
  QTest::addColumn<QString>("result");

  QTest::newRow("Unicode identifier")
    << "This is {{æâêîœßð}}!"
    << "This is UNICODE!";

  QTest::newRow("Simple identifiers")
    << ".{{foo}}.{{ bar}}.{{foo }}.{{ bar }}.{{   foo   }}."
    << ".FOO.BAR.FOO.BAR.FOO.";

  QTest::newRow("Unknown identifiers")
    << ".{{X}}.{{ Y}}.{{Z }}.{{ T }}.{{X}}{{Y}}."
    << "......";

  QTest::newRow("Dot-separated paths (Hash & Map)")
    << "{{ x0.y1 }}.{{ x0.z2 }}.{{x0.t9.alpha}}"
    << "Y1.Z2.ALPHA";

  QTest::newRow("Dot-separated paths (List)")
    << "{{ vec.0.name }}.{{ vec.1.name }}.{{ vec.2.name }}"
    << "vec1.vec2.vec3";

  QTest::newRow("Dot-separated paths (deprecated syntax)")
    << "{{x0/t9/alpha}}"
    << "ALPHA";

  QTest::newRow("Segment-literal notation")
    << "{{ x0.t9.f.o/o }} != {{x0.t9.[f.o/o]}}"
    << " != FOO-t9";

  QTest::newRow("Complex types")
    << "{{vec}}.{{vec.0}}.{{x0}}.{{x0.t9}}"
    << "...";

  QTest::newRow("Containers length")
    << "{{vec.length}} | {{3MPTY.length}} | {{x0.length}} | {{EmptyH.length}}"
    << "3 | 0 | 4 | 0";

  QTest::newRow("QObject name")
    << "{{R00T.name}} | {{R00T.objectName}} | {{R00T.className}}"
    << "r0ot | r0ot | DemoRoot";

  QTest::newRow("QObject property")
    << "{{ R00T.children.length }} | {{ R00T.children.0.name }} | {{ R00T.children.1.ID}}"
    << "3 | Child #1 | 31173";

  QTest::newRow("QObject parent")
    << "{{ R00T.children.0.parent.className }}"
    << "DemoRoot";
}

void
Test::basic()
{
  QFETCH( QString, tmplate );
  QFETCH( QString, result );

  QString out( render( tmplate ));
  QCOMPARE( out, result );
}

void
Test::escape()
{
  QString tmplate, result;

  m_parser.setEscapeFunction( fn_htmlEscape );

  tmplate = "{{html}}  |  {{{html}}}";
  result  = "&lt;b&gt;BOLD&lt;/b&gt;  |  <b>BOLD</b>";
  QCOMPARE( render( tmplate ), result );

  m_parser.setEscapeFunction( fn_noEscape );

  tmplate = "{{html}}  |  {{{html}}}";
  result  = "<b>BOLD</b>  |  <b>BOLD</b>";
  QCOMPARE( render( tmplate ), result );
}

// TODO helper escape

QTEST_MAIN(Test)
#include "Test.moc"
