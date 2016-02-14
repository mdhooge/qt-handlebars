#ifndef HANDLEBARS_ISTREAM_MANAGER_H
#define HANDLEBARS_ISTREAM_MANAGER_H

#include <istream>
#include <memory>
#include <string>

#include <QList>

#include "location.hh"

namespace Handlebars {

/**
 * The IStreamManager class manages the istreams provided to Flex.
 *
 * It also manages the Bison's location classes.
 */
class IStreamManager
{

  class IStreamFrame {
  public:
    IStreamFrame();
    explicit IStreamFrame( const std::string& name );
    ~IStreamFrame();

    // Stream data
    std::string streamName;
    std::istream * yyin;
    bool deleteStreamOnClose = false;

    // Parser location in stream
    location * yylloc;
  };

public:
  ~IStreamManager();

  bool isEmpty() const { return m_frameStack.isEmpty(); }

  void popStream();

  void useStream( std::istream *, bool deleteStreamOnClose );
  void useStream( const std::string& name, std::istream *, bool deleteStreamOnClose );

  bool openFile( const char* filepath );

  void useString( const std::string& content );
  void useString( const std::string& name, const std::string& content );

  std::istream * getCurrentStream() const;
  location * getCurrentStreamLocation() const;

private:
  QList<IStreamFrame*> m_frameStack;

  void pushFrame( std::unique_ptr<IStreamFrame> & f ) { m_frameStack.append( f.get() ); f.release(); }
};

}// namespace Handlebars

#endif // HANDLEBARS_ISTREAM_MANAGER_H
