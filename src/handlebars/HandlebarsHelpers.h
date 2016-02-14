#ifndef HANDLEBARS_HELPERS_H
#define HANDLEBARS_HELPERS_H

#include <functional>

#include <QHash>
#include <QList>
#include <QVariant>


namespace Handlebars {

  using escape_fn = std::function< QString (const QString&) >;


  class RenderingContext;
  class Node;


  using helper_params = QVariantList;
  using helper_options = QVariantHash;


  using helper_fn = std::function<
    QVariant (
      const RenderingContext & context,
      const helper_params & params,
      const helper_options & options
      )>;


  using block_helper_fn = std::function<
    void (
      RenderingContext & context,
      const helper_params & params,
      const helper_options & options,
      const QList<Node*> & first,
      const QList<Node*> & last
      )>;


  using helpers = QHash< QString, helper_fn >;
  using block_helpers = QHash< QString, block_helper_fn >;

}// namespace Handlebars

#endif // HANDLEBARS_HELPERS_H
