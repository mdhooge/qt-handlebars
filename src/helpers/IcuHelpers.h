#include "HandlebarsHelpers.h"

namespace Handlebars {

class Parser;

/**
 * Registers ICU helpers.
 *
 * \see http://unicode.org/reports/tr44/#General_Category_Values
 */
void registerIcuHelpers( Parser & parser );
  // icu_transform <Compound_ID> <string>
  // camelize <string>

  // {{# icu_transform_b <Compound_ID> }}TEXT{{/ icu_transform_b }}

}// namespace Handlebars
