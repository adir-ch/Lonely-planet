#ifndef __XML_LOCATIONS_MAP_H_INCL__
#define __XML_LOCATIONS_MAP_H_INCL__

#include <pugixml.hpp>
#include "locations_map.h"

/**
 * TODO: Add class description
 * 
 * @author   adir
 */
class XMLLocationsMap : public LocationsMap, pugi::xml_tree_walker {
public:
    // Constructor
    XMLLocationsMap();

    // Destructor
    virtual ~XMLLocationsMap();
    virtual bool initLocationsMap(); // will init the location map

    bool loadXMLLocationsMap(const std::string& XMLFileName);
    virtual bool for_each(pugi::xml_node& node); // xml tree traversal 

private: 

    pugi::xml_document m_locationsMapXml;
};

// Constructor implementation
inline XMLLocationsMap::XMLLocationsMap() : LocationsMap() {
}

// Destructor implementation
inline XMLLocationsMap::~XMLLocationsMap() {
}



#endif // __XML_LOCATIONS_MAP_H_INCL__
