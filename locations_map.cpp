
#include <iostream>
#include <sstream>
#include "locations_map.h"

std::string LocationsMap::sprint() const
{
    if (m_locationsMap.empty()) {
        return "Empty map"; 
    }

    LocationsMapT::const_iterator it; 
    LocationsMapT::const_iterator itend = m_locationsMap.end();
    std::vector<std::string>::const_iterator vit;
    std::vector<std::string>::const_iterator vitend;
    std::ostringstream out;

    out << "Locations map:" << std::endl;
    for (it = m_locationsMap.begin(); it != itend; it++) {
        out << it->first << ": ";
        vitend = it->second.end(); 
        for (vit = it->second.begin(); vit != vitend; vit++) {
            out << *vit + " ";
        }
        out << std::endl;
    }

    return out.str(); 
}

void LocationsMap::updateLinksMap(std::string location, std::string parentLocation)
{
    if (location.empty()) {
        return; 
    }

    //std::cout << "Updating map - name: " << location << ", parent: " << parentLocation << std::endl; 
    std::pair<LocationsMapT::iterator, bool> rc;

    std::vector<std::string> related;
    rc = m_locationsMap.insert(std::make_pair<std::string, std::vector<std::string> >(location, related)); 
    if (rc.second == false) 
        std::cout << location << " - already exist" << std::endl; 

    if (parentLocation.empty() == false) {
        rc.first->second.push_back(parentLocation); 
        m_locationsMap[parentLocation].push_back(location);
    } 
}

