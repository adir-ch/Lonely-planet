#ifndef __LOCATIONS_MAP_H_INCL__
#define __LOCATIONS_MAP_H_INCL__

#include <string> 
#include <vector> 
#include <map>
/**
 * TODO: Add class description
 * 
 * @author   adir
 */
class LocationsMap {
public:

    typedef std::map<std::string, std::vector<std::string> > LocationsMapT; 

    // Constructor
    LocationsMap();

    // Destructor
    virtual ~LocationsMap();

    virtual bool initLocationsMap() = 0; // will init the location map

    std::string sprint() const;

protected:

    void updateLinksMap(std::string location, std::string parentLocation);

    LocationsMapT m_locationsMap;  
};

// Constructor implementation
inline LocationsMap::LocationsMap() {
}

// Destructor implementation
inline LocationsMap::~LocationsMap() {
}

#endif // __LOCATIONS_MAP_H_INCL__
