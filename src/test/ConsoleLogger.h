#ifndef CONSOLE_LOGGER_H
#define CONSOLE_LOGGER_H

#include "HandlebarsLoggerInterface.h"

namespace Handlebars {

/**
 * The ConsoleLogger class provides a Color output to console for the Handlebars Logger.
 */
class ConsoleLogger : public Handlebars::LoggerInterface
{
public:
  ConsoleLogger();

  void debug  ( const QString& ) override;
  void info   ( const QString& ) override;
  void warning( const QString& ) override;
  void error  ( const QString& ) override;

  bool color;
};

}// namespace Handlebars

#endif // CONSOLE_LOGGER_H
