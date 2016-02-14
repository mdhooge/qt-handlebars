#include "ExtraHelpers.h"

#include <QChar>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QObject>
#include <QTextStream>

#include "HandlebarsParser.h"

namespace Handlebars {

const escape_fn
  fn_noEscape,
  fn_htmlEscape { [] (const QString& str ) { return str.toHtmlEscaped(); } };


void registerAllHelpers( Parser & parser ) {
  registerBitwiseHelpers( parser );
  registerBooleanHelpers( parser );
  registerFileHelpers( parser );
  registerIntegerHelpers( parser );
  registerPropertyHelpers( parser );
  registerStringHelpers( parser );
}


// ###
// ### Bit-wise Helpers
// ###

static QVariant
integerTypes_bit( const QString& tmplate, int bits )
{
  if( bits <= 8 )
    return tmplate.arg( "8" );
  if( bits <= 16 )
    return tmplate.arg( "16" );
  if( bits <= 32 )
    return tmplate.arg( "32" );
  return tmplate.arg( "64" );
}

void
registerBitwiseHelpers( Parser & parser )
{

  parser.registerHelper(
    "bit-mask", [] (
      const RenderingContext &,
      const helper_params & params,
      const helper_options & )
    {
      int shift = 64 - params.value( 0 ).toInt();
      uint64_t mask { UINT64_MAX >> shift };
      QString out( "0x" );
      out.append( QString::number( mask, 16 ).toUpper() );
      return out;
    } );

  parser.registerHelper(
    "int_fast", [] (
      const RenderingContext &,
      const helper_params & params,
      const helper_options & )
    {
      if( params.size() != 2 )
        return QVariant(); // RTFM
      int bits = params.at( 1 ).toInt();
      if( params.at( 0 ).toString().toUpper() == "BYTE" )
        bits *= 8;
      return integerTypes_bit( "int_fast%1_t", bits );
    } );

  parser.registerHelper(
    "int_least", [] (
      const RenderingContext &,
      const helper_params & params,
      const helper_options & )
    {
      if( params.size() != 2 )
        return QVariant(); // RTFM
      int bits = params.at( 1 ).toInt();
      if( params.at( 0 ).toString().toUpper() == "BYTE" )
        bits *= 8;
      return integerTypes_bit( "int_least%1_t", bits );
    } );

  parser.registerHelper(
    "uint_fast", [] (
      const RenderingContext &,
      const helper_params & params,
      const helper_options & )
    {
      if( params.size() != 2 )
        return QVariant(); // RTFM
      int bits = params.at( 1 ).toInt();
      if( params.at( 0 ).toString().toUpper() == "BYTE" )
        bits *= 8;
      return integerTypes_bit( "uint_fast%1_t", bits );
    } );

  parser.registerHelper(
    "uint_least", [] (
      const RenderingContext &,
      const helper_params & params,
      const helper_options & )
    {
      if( params.size() != 2 )
        return QVariant(); // RTFM
      int bits = params.at( 1 ).toInt();
      if( params.at( 0 ).toString().toUpper() == "BYTE" )
        bits *= 8;
      return integerTypes_bit( "uint_least%1_t", bits );
    } );

}


// ###
// ### Boolean Helpers
// ###

void
registerBooleanHelpers( Parser & parser )
{

  parser.registerHelper(
    "==", [] ( const RenderingContext &, const helper_params & params, const helper_options & )
    { return params.value( 0 ) == params.value( 1 ); } );

  parser.registerHelper(
    "!=", [] ( const RenderingContext &, const helper_params & params, const helper_options & )
    { return params.value( 0 ) != params.value( 1 ); } );

  parser.registerHelper(
    "<", [] ( const RenderingContext &, const helper_params & params, const helper_options & )
    { return params.value( 0 ) < params.value( 1 ); } );

  parser.registerHelper(
    "<=", [] ( const RenderingContext &, const helper_params & params, const helper_options & )
    { return params.value( 0 ) <= params.value( 1 ); } );

  parser.registerHelper(
    ">", [] ( const RenderingContext &, const helper_params & params, const helper_options & )
    { return params.value( 0 ) > params.value( 1 ); } );

  parser.registerHelper(
    ">=", [] ( const RenderingContext &, const helper_params & params, const helper_options & )
    { return params.value( 0 ) >= params.value( 1 ); } );

  parser.registerHelper(
    "AND", [] (
      const RenderingContext & c,
      const helper_params & params,
      const helper_options & )
    {
      bool r = true;
      for( auto v : params ) {
        r = r && c.propertyAsBool( v );
        if( ! r ) break;
      }
      return r;
    } );

  parser.registerHelper(
    "NOT", [] ( const RenderingContext & c, const helper_params & params, const helper_options & )
    { return ! c.propertyAsBool( params.value( 0 )); } );

  parser.registerHelper(
    "OR", [] (
      const RenderingContext & c,
      const helper_params & params,
      const helper_options & )
    {
      bool r = false;
      for( auto v : params ) {
        r = r || c.propertyAsBool( v );
        if( r ) break;
      }
      return r;
    } );

}


// ###
// ### File Helpers
// ###

/**
 * Concatenate all params to create file path & name
 */
static QString
pathConcatenate( const helper_params & params )
{
  QString filepath;
  for( auto element : params )
    filepath += element.toString();
  return filepath;
}

/**
 * Recursively copy content of a folder to another folder.
 *
 * - source must be an existing folder.
 */
static void
copyRecursively( const QString& source, const QString& target )
{
  QDir sourceDir( source );
  QDir targetDir( target );

  // Create target folder if needed
  if( ! targetDir.exists() )
    targetDir.mkpath( "." );

  // Loop & copy
  auto list = sourceDir.entryInfoList( QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Readable );
  for( int i = 0; i < list.size(); ++i )
  {
    // Create paths
    auto fileInfo = list.at( i );
    QString
      filename( fileInfo.fileName() ),
      sourcePath( sourceDir.filePath( filename )),
      targetPath( targetDir.filePath( filename ));

    // Copy
    if( fileInfo.isDir() )
      copyRecursively( sourcePath, targetPath );
    else
      QFile::copy( sourcePath, targetPath );
  }
}

void
registerFileHelpers( Parser & parser )
{

  parser.registerHelper(
    "cd", [] (
      const RenderingContext &,
      const helper_params & params,
      const helper_options & )
    {
      QDir::setCurrent( pathConcatenate( params ));
      return QVariant();
    } );

  parser.registerHelper(
    "copy_into-current-folder_from", [] (
      const RenderingContext & context,
      const helper_params & params,
      const helper_options & options)
    {
      // Check source
      QString source( pathConcatenate( params ));
      QFileInfo sourceFileInfo( source );
      if( ! sourceFileInfo.exists() ) {
        context.warning(
          QString( "Handlebars.helper.copy: Source \"%1\" doesn't exist." ).arg( source ));
        return QVariant();
      }

      // "contentOnly" option
      bool contentOnly = options.value( "contentOnly" ).toBool();

      // Copy file or folder
      if ( sourceFileInfo.isDir() ) {
        QString targetPath( contentOnly ? "." : sourceFileInfo.fileName() );
        copyRecursively( source, targetPath );
      }
      else
        QFile::copy( source, sourceFileInfo.fileName() );

      return QVariant();
    } );

  parser.registerHelper(
    "mkdir", [] (
      const RenderingContext &,
      const helper_params & params,
      const helper_options & )
    {
      QDir::current().mkpath( pathConcatenate( params ));
      return QVariant();
    } );

  parser.registerHelper(
    "temp_path", [] (
      const RenderingContext &,
      const helper_params &,
      const helper_options & )
    {
      return QVariant( QDir::tempPath() );
    } );

  parser.registerBlockHelper(
    "create_file", [] (
      RenderingContext & context,
      const helper_params & params,
      const helper_options & options,
      const NodeList & truthy,
      const NodeList &
      )
    {
      if( params.size() == 0 )
        return; // RTFM

      // Compute file path & name
      QString filepath( pathConcatenate( params ));

      // If property "output_folder" exists, use it to compute a relative path (for log messages)
      QString relative_filepath( filepath );
      QVariant output_folder( context.getProperty( "output_folder" ));
      if( output_folder.isValid() ) {
        QDir output_dir( output_folder.toString() );
        relative_filepath = output_dir.relativeFilePath(
          QDir::current().absoluteFilePath( filepath ));
      }

      // Open file
      QFile file( filepath );
      if( ! file.open( QIODevice::WriteOnly )) {
        context.warning( QString( "Handlebars.helper.create_file(%1): error #%2" )
          .arg( relative_filepath )
          .arg( file.error() ));
        return;
      }
      context.info( QString( "Handlebars.helper.create_file(%1)" ).arg( relative_filepath ));

      // Create context with file info
      QFileInfo fi( filepath );
      QVariantHash infos;
      infos.insert( "@basename", fi.baseName() );
      infos.insert( "@filename", fi.fileName() );
      infos.insert( "@filepath", fi.filePath() );
      infos.insert( "@filepath_absolute", fi.canonicalFilePath() );
      if( output_folder.isValid() )
        infos.insert( "@filepath_relative", relative_filepath );
      context.pushPropertiesContext( infos );

      // If options were given, add them to the context
      if( ! options.isEmpty() )
        context.pushPropertiesContext( options );

      // Create file value
      QTextStream stream( & file );
      context.render( truthy, & stream );
      file.close();

      // Remove temporary contexts
      if( ! options.isEmpty() )
        context.popPropertiesContext();
      context.popPropertiesContext();
    } );

}


// ###
// ### Integer Helpers
// ###

void
registerIntegerHelpers( Parser & parser )
{

  parser.registerHelper(
    "range", [] (
      const RenderingContext &,
      const helper_params & params,
      const helper_options & ) -> QVariant
    {
      if( params.size() < 2 )
        return QVariant(); // RTFM
      // Retrieve parameters
      int i = params.at( 0 ).toInt();
      int end = params.at( 1 ).toInt();
      int incr = ( params.size() > 2 )
        ? params.at( 2 ).toInt()
        : ( i <= end ) ? 1 : -1;
      // Loop
      QVariantList range;
      for(; (incr>0) ? i<=end : i>=end; i+=incr )
        range.append( i );
      return range;
    } );

}


// ###
// ### Property Helpers
// ###

/**
 * Loops over a <Container<QVariant>>
 *
 * The container is obtained from the "anonymous" QVariant.
 */
template< template<typename> class C >
static QVariant
objectsWithProperty(
  const QVariant& q_input,
  const helper_params & params
  )
{
  C< QVariant > input( q_input.value< C< QVariant > > () );
  C< QVariant > output;

  for( QVariant q_var : input ) {
    QObject* object( q_var.value<QObject*>() );
    if( object != nullptr )
      for( auto propertyName : params )
        if( object->property( propertyName.toByteArray().constData() ).toBool() ) {
          output.append( q_var );
          break;
        }
  }

  return output;
}

/**
 * Loops over a <Container< QString, QVariant >>
 *
 * The container is obtained from the "anonymous" QVariant.
 */
template< template<typename,typename> class C >
static QVariant
objectsWithProperty(
  const QVariant& q_input,
  const helper_params & params
  )
{
  C< QString,QVariant > input( q_input.value< C< QString,QVariant > > () );
  C< QString,QVariant > output;

  for( auto i = input.constBegin(), end = input.constEnd(); i != end; ++i ) {
    QVariant q_var( *i );
    QObject* object( q_var.value<QObject*>() );
    if( object != nullptr )
      for( auto propertyName : params )
        if( object->property( propertyName.toByteArray().constData() ).toBool() ) {
          output.insert( i.key(), i.value() );
          break;
        }
  }

  return output;
}

void
registerPropertyHelpers( Parser & parser )
{

  parser.registerHelper(
    "objects-with-property", [] (
      const RenderingContext &,
      const helper_params & c_params,
      const helper_options & ) -> QVariant
    {
      if( c_params.size() < 2 )
        return QVariant(); // RTFM

      // Find type of container
      auto params = c_params;
      auto container( params.takeFirst() );
      auto type( QMetaType::Type( container.type() ));
      switch( type )
      {
        case QMetaType::QVariantHash:
          return objectsWithProperty <QHash> ( container, params );
          break;
        case QMetaType::QVariantList:
          return objectsWithProperty <QList> ( container, params );
          break;
        case QMetaType::QVariantMap:
          return objectsWithProperty <QMap> ( container, params );
          break;
        default:
          return QVariant();
          break;
      }
    } );

  parser.registerHelper(
    "container-value", [] (
      const RenderingContext &,
      const helper_params & params,
      const helper_options & ) -> QVariant
    {
      if( params.size() < 2 )
        return QVariant(); // RTFM
      auto container = params.at( 0 );
      auto key = params.at( 1 ).toString();
      return RenderingContext::findPropertyInContext( key, container );
    } );

  parser.registerBlockHelper(
    "set_property", [] (
      RenderingContext & context,
      const helper_params & params,
      const helper_options & options,
      const NodeList & truthy,
      const NodeList &
      )
    {
      if( params.size() < 1 ) return; // RTFM

      auto name = params.at( 0 ).toString();

      // Check if property already exists and "only-if" is set to "new"
      if( options.value( "only-if" ).toString() == "new" && context.hasProperty( name ))
        return;

      QVariant value;
      if( params.size() == 2 )
        value = params.at( 1 );

      else {
        // If options were given, add them to the context
        if( ! options.isEmpty() )
          context.pushPropertiesContext( options );

        // Use temporary output to collect inner block
        QString content;
        QTextStream stream( & content, QIODevice::WriteOnly );

        // Create property value
        context.render( truthy, & stream );

        // Remove any options
        if( ! options.isEmpty() )
          context.popPropertiesContext();

        value = content;
      }

      // Insert property into context (SIDE-EFFECT!)
      context.addProperty( name, value );
    } );

}


// ###
// ### String Helpers
// ###

void
registerStringHelpers( Parser & parser )
{

  parser.registerHelper(
    "camelize", [] (
      const RenderingContext &,
      const helper_params & p,
      const helper_options & )
    {
      QString in( p.value( 0 ).toString() );
      QString out;
      out.reserve( in.size() );
      //
      bool upper = true;
      for( QChar c : in ) {
        if( c.isLetterOrNumber() ) {
          out += upper ? c.toUpper() : c;
          upper = false;
        } else
          upper = true;
      }
      //
      if( out.isEmpty() || ! out[0].isLetter() )
        out.prepend( '_' );
      //
      return out;
    } );

  // date [<format> =]
  parser.registerHelper(
    "date", [] (
      const RenderingContext &,
      const helper_params & p,
      const helper_options & )
    {
      auto format = p.value( 0 ).toString();
      if( format.isEmpty() ) format = "yyyy-MM-ddTHH:mmt";
      return QDateTime::currentDateTime().toString( format );
    } );


  parser.registerHelper(
    "hex", [] (
      const RenderingContext &,
      const helper_params & p,
      const helper_options & opt )
    {
      qint64 value = p.value( 0 ).toLongLong();
      int width = opt.value( "width", 0 ).toInt();
      QString fillS = opt.value( "fill" ).toString();
      QChar fill = fillS.size() > 0 ? fillS.at( 0 ) : ' ';
      return QVariant( QString( "%1" ).arg( value, width, 16, fill ));
    } );

  parser.registerHelper(
    "link", [] (
      const RenderingContext &,
      const helper_params & p,
      const helper_options & opt )
    {
      QStringList attrs;
      for( auto i = opt.begin(), end = opt.end(); i != end; ++i )
        attrs.append( QString( "%1=\"%2\"" ).arg( i.key() ).arg( i.value().toString() ));

      return QVariant( QString( "<a %1>%2</a>" )
        .arg( attrs.join( ' ' ))
        .arg( p.value( 0 ).toString() ));
    } );

  parser.registerHelper(
    "print", [] (
      const RenderingContext &,
      const helper_params & p,
      const helper_options & )
    {
      QString out;
      QTextStream stream( & out, QIODevice::WriteOnly );
      for( auto i = p.begin(), end = p.end() ;;)
      {
        stream << i->typeName() << '(' << i->toString() << ')';
        if( ++i == end )
          break;
        stream << ' ';
      }
      return QVariant( out );
    } );

  parser.registerHelper(
    "upper", [] (
      const RenderingContext &,
      const helper_params & p,
      const helper_options & )
    {
      return QVariant( p.value( 0 ).toString().toUpper() );
    } );

}

}// namespace Handlebars
