#ifndef HANDLEBARS_LOGGER_INTERFACE_H
#define HANDLEBARS_LOGGER_INTERFACE_H

#include <QString>

namespace Handlebars {

/**
 * The LoggerInterface class defines the interface expected by Handlebars to
 * log messages.
 */
class LoggerInterface
{
public:
  virtual ~LoggerInterface() = default;

  virtual void debug  ( const QString& ) = 0;
  virtual void info   ( const QString& ) = 0;
  virtual void warning( const QString& ) = 0;
  virtual void error  ( const QString& ) = 0;

};

}// namespace Handlebars

#endif // HANDLEBARS_LOGGER_INTERFACE_H
