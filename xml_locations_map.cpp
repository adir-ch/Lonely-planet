#include <iostream>
#include "xml_locations_map.h"

// TODO: your implementation here

bool XMLLocationsMap::for_each(pugi::xml_node &node) {

    if (std::string(node.name()) == "node_name") {
        //std::cout << "*** name='" << node.name() << "', value='" << node.first_child().value() << std::endl;
        //std::cout << "*** name: " << node.first_child().value() << ", parent: " << node.parent().parent().child("node_name").first_child().value() << std::endl;
        updateLinksMap(node.first_child().value(), node.parent().parent().child("node_name").first_child().value());
    }
    return true; // continue traversal
}

bool XMLLocationsMap::initLocationsMap() {
    m_locationsMapXml.traverse(*this);
    return true; // TODO - check return
}

bool XMLLocationsMap::loadXMLLocationsMap(const std::string &XMLFileName) {
    

    pugi::xml_parse_result result = m_locationsMapXml.load_file(XMLFileName.c_str());
    std::cout << "Destination map load result: " << result.description() << std::endl;

    if (result.status != pugi::status_ok) {
        return false; 
    }

    // check for loading rc and return false is not loaded
    initLocationsMap();
    return true;
}
