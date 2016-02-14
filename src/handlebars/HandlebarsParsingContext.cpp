#include "HandlebarsParsingContext.h"

#include <fstream>
using namespace std;

namespace Handlebars {

ParsingContext::ParsingContext(
  QList<Node*> & nodes,
  helpers & helpers,
  block_helpers & block_helpers,
  LoggerInterface& logger
) :
  m_nodes( nodes ),
  m_helpers( helpers ),
  m_block_helpers( block_helpers ),
  m_logger( logger )
{
}

}// namespace Handlebars
