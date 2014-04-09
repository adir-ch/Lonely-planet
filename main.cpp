/**
 * 	Lonely planet HTML generator
 */

#include <iostream>


#include "xml_locations_map.h"
#include "xml_2_html_generator.h"

void xpath_Test() 
{
    pugi::xml_document doc;

    pugi::xml_parse_result result = doc.load_file("taxonomy.xml");
    std::cout << "Destination info load result: " << result.description() << std::endl;
    pugi::xml_node world = doc.child("taxonomies").child("taxonomy").child("node");
  
    std::cout << "Use xpath to print the map under: Gauteng" << std::endl; 
    std::string query = "//node[node_name='Gauteng']";

    pugi::xpath_query location_search(query.c_str());
    if (location_search.evaluate_boolean(world) == true) {
        std::cout << world.select_single_node(query.c_str()).node().name() << std::endl;
    } else {
        std::cout << "Cannot evaluate quarry" << std::endl; 
    }
}

void printDestinationInfo()
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("destinations.xml");
    pugi::xml_node destinations = doc.child("destinations");
    std::cout << "Destination info load result: " << result.description() << std::endl;

    std::string title; 
    for (pugi::xml_node_iterator nodeit = destinations.begin(); nodeit != destinations.end(); nodeit++) {
        title = nodeit->attribute("title-ascii").value();
        if (title == "Africa") {
            std::cout << "Africa - found!, atlas ID: " << nodeit->attribute("atlas_id").value() << std::endl;
        }
    }
}

void locationMap_Test(XMLLocationsMap& locationsMap)
{
    std::cout << "=========== Location Map unit-test ===========" << std::endl; 

    std::cout << locationsMap.sprint() << std::endl; 
    std::string location = "Africa";
    const std::vector<std::string> *related = locationsMap.getLocationRelated(location); 

    if (related != NULL) {
        std::string relatedList; 
        std::vector<std::string>::const_iterator it;
        std::vector<std::string>::const_iterator itend = related->end(); 
        for (it = related->begin(); it != itend; it++) {
            relatedList += *it + " "; 
        }

        std::cout << location << ": " << relatedList << std::endl; 
    }
}

//////////////////////////////////////////////////////// Main

int main(int argc, char *argv[]) 
{  
    std::cout << "Lonely planet HTML generator" << std::endl;

    if (argc < 2) {
        std::cout << "Usage: html-generator <locations map file> <destinations data file>" << std::endl; 
        return -1; 
    }

    //printDestinationInfo(); 

    XMLLocationsMap locationsMap; 
    if (locationsMap.loadXMLLocationsMap(argv[1]) == false) {
        std::cout << "Unable to load locations map data" << std::endl;
        return -1;  
    }

    //locationMap_Test(locationsMap); 
    std::string destinationsXmlFile = argv[2]; 
    XMLFile2HTMLGenerator generator(destinationsXmlFile, &locationsMap); // consider use Factory design pattern here
    if (generator.init() == false) {
        std::cout << "Unable to load destinations data DB" << std::endl; 
        return -1; 
    }

    generator.generateHtml(); 

    //generator.generateHtml(); 

    
    return 0;
}
