/**
 * $Id: mkctaskbuilder.cpp 699 2014-09-17 15:00:38Z klugeflo $
 * @file mkctaskbuilder.cpp
 * @brief Build tmssim::MKCTask from XML
 * @authors Peter Ittner, Florian Kluge <kluge@informatik.uni-augsburg.de>
 */

#include <xmlio/mkctaskbuilder.h>

#include <string>
#include <sstream>
#include <utils/tlogger.h>
#include <xmlio/xmlutils.h>
#include <xmlio/utilitycalculatorfactory.h>
#include <xmlio/utilityaggregatorfactory.h>
#include <taskmodels/mkctask.h>

using namespace std;

namespace tmssim {

  Task* MKCTaskBuilder::build(xmlDocPtr doc, xmlNodePtr cur) {
    
    tDebug() << "Building a MKCTask";
    
    // Factories for more complex objects
    UtilityCalculatorFactory ucfact;
    UtilityAggregatorFactory uafact;
    
    // Variables need to build the task
    unsigned int id = 0;
    int period = -1;
    int executiontime = -1;
    int criticaltime = -1;
    int priority = 1;
    int m = 0;
    int k = 0;
    //unsigned int spin = 0;
    UtilityCalculator* uc = NULL;
    UtilityAggregator* ua = NULL;

    // Iterate through the document to get the needed data
    cur = cur->xmlChildrenNode;
    // Iterate over all children elements like <id>, <executiontime>, ...
    while (cur != NULL) {
      if (ucfact.accept(doc, cur)) {
	uc = ucfact.getElement(doc, cur);
      } else if (uafact.accept(doc, cur)) {
	ua = uafact.getElement(doc, cur);
      }
      if (XmlUtils::isNodeMatching(cur, "id")) {
	id = XmlUtils::getNodeValue<unsigned int>(cur, doc);
      } else if (XmlUtils::isNodeMatching(cur, "executiontime")) {
	executiontime = XmlUtils::getNodeValue<int>(cur, doc);
      } else if (XmlUtils::isNodeMatching(cur, "criticaltime")) {
	criticaltime = XmlUtils::getNodeValue<int>(cur, doc);
      } else if (XmlUtils::isNodeMatching(cur, "period")) {
	period = XmlUtils::getNodeValue<int>(cur, doc);
      } else if (XmlUtils::isNodeMatching(cur, "priority")) {
	priority = XmlUtils::getNodeValue<int>(cur, doc);
      } else if (XmlUtils::isNodeMatching(cur, "m")) {
	m = XmlUtils::getNodeValue<int>(cur, doc);
      } else if (XmlUtils::isNodeMatching(cur, "k")) {
	k = XmlUtils::getNodeValue<int>(cur, doc);
	//} else if (XmlUtils::isNodeMatching(cur, "spin")) {
	//spin = XmlUtils::getNodeValue<int>(cur, doc);
      } else {
	//tError() << "Unknown Node Tag: " << cur->name;
      }
      // FIXME: uc, ua
      cur = cur->next;
    }

    // Create the entire task from the parsed data

    MKCTask* taskPtr = new MKCTask(id, period, executiontime, criticaltime,
				   uc, ua, priority, m, k);

      /*
  MKCTask::MKCTask(unsigned int _id, int _period, int _et, int _ct,
	    UtilityCalculator* _uc, UtilityAggregator* _ua,
	    unsigned int _prio, unsigned int _m, unsigned int _k)
  */
    return taskPtr;
  }
  
} // NS tmssim
