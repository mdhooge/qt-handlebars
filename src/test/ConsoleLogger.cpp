#include "ConsoleLogger.h"

#include <unistd.h>

#include <iostream>
#include <ostream>
using namespace std;

namespace Handlebars {

namespace Color {
  // http://misc.flogisoft.com/bash/tip_colors_and_formatting
  enum Code {
    BOLD           = 1,
    DIM            = 2,
    UNDERLINED     = 4,
    BLINK          = 5,
    REVERSE        = 7,
    HIDDEN         = 8,

    RESET          = 0,
    RST_BOLD       = 21,
    RST_DIM        = 22,
    RST_UNDERLINED = 24,
    RST_BLINK      = 25,
    RST_REVERSE    = 27,
    RST_HIDDEN     = 28,

    FG_DEFAULT     = 39,

    FG_BLACK       = 30,
    FG_RED         = 31,
    FG_GREEN       = 32,
    FG_YELLOW      = 33,
    FG_BLUE        = 34,
    FG_MAGENTA     = 35,
    FG_CYAN        = 36,
    FG_GRAY        = 37,
    FG_DARK_GRAY   = 90,
    FG_LT_RED      = 91,
    FG_LT_GREEN    = 92,
    FG_LT_YELLOW   = 93,
    FG_LT_BLUE     = 94,
    FG_LT_MAGENTA  = 95,
    FG_LT_CYAN     = 96,
    FG_WHITE       = 97,

    BG_DEFAULT     = 49,

    BG_BLACK       = 40,
    BG_RED         = 41,
    BG_GREEN       = 42,
    BG_YELLOW      = 43,
    BG_BLUE        = 44,
    BG_MAGENTA     = 45,
    BG_CYAN        = 46,
    BG_GRAY        = 47,
    BG_DARK_GRAY   = 100,
    BG_LT_RED      = 101,
    BG_LT_GREEN    = 102,
    BG_LT_YELLOW   = 103,
    BG_LT_BLUE     = 104,
    BG_LT_MAGENTA  = 105,
    BG_LT_CYAN     = 106,
    BG_WHITE       = 107,
  };
  std::ostream& operator<<(std::ostream& os, Code code) {
    return os << "\033[" << static_cast<int>(code) << "m";
  }
}

ConsoleLogger::ConsoleLogger()
{
  color = isatty( fileno( stderr ));
}

void
ConsoleLogger::debug( const QString& msg )
{
  if( color )
    cerr << Color::FG_BLUE << msg.toStdString() << Color::RESET << endl;
  else
    cerr << msg.toStdString() << endl;
}

void
ConsoleLogger::info( const QString& msg )
{
  if( color )
    cerr << Color::FG_LT_CYAN << msg.toStdString() << Color::RESET << endl;
  else
    cerr << msg.toStdString() << endl;
}

void
ConsoleLogger::warning( const QString& msg )
{
  if( color )
    cerr << Color::FG_LT_YELLOW << msg.toStdString() << Color::RESET << endl;
  else
    cerr << msg.toStdString() << endl;
}

void
ConsoleLogger::error( const QString& msg )
{
  if( color )
    cerr << Color::FG_LT_RED << Color::BOLD << msg.toStdString() << Color::RESET << endl;
  else
    cerr << msg.toStdString() << endl;
}

}// namespace Handlebars
