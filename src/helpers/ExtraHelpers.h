#include "HandlebarsHelpers.h"

namespace Handlebars {

class Parser;

extern const escape_fn
  fn_noEscape,
  fn_htmlEscape;


void registerAllHelpers( Parser & parser );


void registerBitwiseHelpers( Parser & parser );
  // bit-mask <size>
  // [u]int[_fast|_least] ["bit"|"byte"] <value>


void registerBooleanHelpers( Parser & parser );
  // All common tests: == != < <= > >=
  // AND <bool>+
  // NOT <bool>
  // OR  <bool>+


void registerFileHelpers( Parser & parser );
  // cd <filepathname-element>+
  // copy_into-current-folder_from <filepathname-element>+ [contentOnly=0]
  // mkdir <filepathname-element>+
  // temp_path

  // {{# create_file <filepathname-element>+ [HASH] }} ... {{/ create_file }}


void registerIntegerHelpers( Parser & parser );
  // range <first> <last> [<increment> = +1/-1 by default]


void registerPropertyHelpers( Parser & parser );
  // objects-with-property <container> <property-name>+
  // container-value <container> <key>

  // !SIDE EFFECT! The content is provided as <dest-property-name> to following nodes
  //
  // {{# set_property <dest-property-name>         [only-if="new"] [HASH] }} ... {{/ set_property }}
  // {{# set_property <dest-property-name> <value> [only-if="new"] }}Inner Content is *IGNORED*{{/ set_property }}


void registerStringHelpers( Parser & parser );
  // camelize <string>
  // date [<format> = "yyyy-MM-ddTHH:mmt"]
  // hex <num> width=0 fill=' '
  // link "Text" href=url [other attrs]
  // print <qvariant> [other vars]
  // upper "string"


}// namespace Handlebars
