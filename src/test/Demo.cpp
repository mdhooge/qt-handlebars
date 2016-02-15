#include <QCoreApplication>
#include <QFile>
#include <QTextStream>

#include "HandlebarsParser.h"
#include "ExtraHelpers.h"
#include "IcuHelpers.h"
using namespace Handlebars;

#include "ConsoleLogger.h"
#include "DemoContext.h"
#include "HandlebarsIStreamManager.h"


int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  // Check command line arguments
  auto args = QCoreApplication::arguments();

  if( args.size() < 2 )
  {
    qDebug( "Usage: %s [-b] [-f] [--html] <template>", qPrintable( args.at( 0 )));
    return -1;
  }

  else
  {
    ConsoleLogger logger;
    Handlebars::Parser parser( logger );
    parser.registerDefaultHelpers();
    registerAllHelpers( parser );
    registerIcuHelpers( parser );

    // Loop on arguments to handle options
    while( args.size() > 1 ) {
      auto arg ( args.at( 0 ));

      if( arg == "-b" )
        parser.setBisonDebugLevel( 1 );

      else if( arg == "-f" )
        parser.setFlexDebugFlag( 1 );

      else if( arg == "--html" )
        parser.setEscapeFunction( fn_htmlEscape );

      args.removeFirst();
    }

    // Open file
    IStreamManager streams;
    if( ! streams.openFile( qPrintable( args.at( 0 ))))
      return 1;

    // Create context
    QVariantHash context;
    initQVariants( context );
    initQObjects( context );

    // Parse file
    parser.parse( streams );
    parser.render( context );

    // Housecleaning
    cleanQObjects( context );
  }

  return 0;
}
