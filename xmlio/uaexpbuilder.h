/**
 * $Id: uaexpbuilder.h 501 2014-05-07 14:16:17Z klugeflo $
 * @file uaexpbuilder.h
 * @brief Build exponential utility aggregator from XML
 * @authors Peter Ittner, Florian Kluge <kluge@informatik.uni-augsburg.de>
 */

#ifndef XMLIO_UAEXPBUILDER_H
#define XMLIO_UAEXPBUILDER_H 1

#include <core/scobjects.h>
#include <xmlio/ielementbuilder.h>

namespace tmssim {

  /**
   * Builds a UAExp object from the given XML-document.
   */
  class UAExpBuilder: public IElementBuilder<UtilityAggregator> {
    
  public:
    /**
     * Builds a UtilityAggregator
     * @param doc The XML-document
     * @param cur The current position within the document
     * @return A pointer to the created UtilityAggregator
     */
    UtilityAggregator* build(xmlDocPtr doc, xmlNodePtr cur);
  };
  
} // NS tmssim

#endif /* !XMLIO_UAEXPBUILDER_H */
