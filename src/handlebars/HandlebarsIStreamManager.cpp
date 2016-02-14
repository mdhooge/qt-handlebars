#include "HandlebarsIStreamManager.h"

#include <fstream>
#include <sstream>
using namespace std;

#include <QDir>
#include <QFileInfo>


namespace Handlebars {

IStreamManager::IStreamFrame::IStreamFrame() :
  yylloc( new location )
{
}

IStreamManager::IStreamFrame::IStreamFrame( const string& name ) :
  streamName( name ),
  yylloc( new location( & streamName ))
{
}

IStreamManager::IStreamFrame::~IStreamFrame()
{
  if( deleteStreamOnClose )
    delete yyin;
  delete yylloc;
}

IStreamManager::~IStreamManager()
{
  qDeleteAll( m_frameStack );
}

void
IStreamManager::popStream()
{
  if( ! m_frameStack.isEmpty() )
    m_frameStack.removeLast();
}

void
IStreamManager::useStream( istream * stream, bool delOnClose )
{
  auto frame = unique_ptr<IStreamFrame>( new IStreamFrame );
  frame->deleteStreamOnClose = delOnClose;
  frame->yyin = stream;
  pushFrame( frame );
}

void
IStreamManager::useStream( const string& name, istream * stream, bool delOnClose )
{
  auto frame = unique_ptr<IStreamFrame>( new IStreamFrame( name ));
  frame->deleteStreamOnClose = delOnClose;
  frame->yyin = stream;
  pushFrame( frame );
}

bool
IStreamManager::openFile( const char* filepath )
{
  // Use previous frame to define target dir
  QDir targetDir;
  if( isEmpty() )
    targetDir = QDir::current();
  else
    targetDir = QFileInfo( QString::fromStdString( m_frameStack.last()->streamName )).dir();

  // Check for file existence
  QString q_fp( filepath );
  if( targetDir.exists( q_fp )) {

    // Compute relative filepath from current directory
    QString absolute( targetDir.absoluteFilePath( q_fp ) );
    QString relative( QDir::current().relativeFilePath( absolute ));

    auto frame = unique_ptr<IStreamFrame>(
      new IStreamFrame( relative.toStdString() ));
    auto input = unique_ptr<ifstream>(
      new ifstream( absolute.toStdString() ));

    // Only push the frame if the file can be read
    if( * input ) {
      frame->yyin = input.release();
      frame->deleteStreamOnClose = true;
      pushFrame( frame );
      return true;
    }
  }
  return false;
}

void
IStreamManager::useString( const string& content )
{
  auto frame = unique_ptr<IStreamFrame>( new IStreamFrame );
  frame->yyin = new istringstream( content );
  frame->deleteStreamOnClose = true;
  pushFrame( frame );
}

void
IStreamManager::useString( const string& name, const string& content )
{
  auto frame = unique_ptr<IStreamFrame>( new IStreamFrame( name ));
  frame->yyin = new istringstream( content );
  frame->deleteStreamOnClose = true;
  pushFrame( frame );
}

istream *
IStreamManager::getCurrentStream() const
{
  // TODO throw if empty
  return m_frameStack.last()->yyin;
}

location *
IStreamManager::getCurrentStreamLocation() const
{
  // TODO throw if empty
  return m_frameStack.last()->yylloc;
}

}// namespace Handlebars
