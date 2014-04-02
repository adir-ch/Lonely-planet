/**
 * 	Lonely planet HTML generator
 */

#include <iostream>


#include "xml_locations_map.h"
#include "xml_2_html_generator.h"

/*
void printLocationData(const pugi::xml_node& iNode, int nest = 0)
{
    if (iNode.empty()) {
        return; 
    }

    nest += 5;
    std::string nesting; 
    int dots = nest;
    while (dots > 0) {
        nesting += ".";
        dots--; 
    }
    // print the name
    if (iNode.child("node_name") != NULL) {
        std::cout << nesting << iNode.child("node_name").child_value() << std::endl; 
    }

    // print all other childred names
    for (pugi::xml_node_iterator nodeit = iNode.begin(); nodeit != iNode.end(); nodeit++) {
        if ((std::string)nodeit->name() != "node_name") 
            printLocationData(*nodeit, nest); 
    }
}

void printDestinationLocations() 
{
    pugi::xml_document doc;

    pugi::xml_parse_result result = doc.load_file("taxonomy.xml");
    pugi::xml_node world = doc.child("taxonomies").child("taxonomy").child("node");
    std::cout << "Destination map load result: " << result.description() << std::endl;

    std::cout << "Print the map" << std::endl;
    printLocationData(world);

    std::cout << "Use xpath to print the map under: Gauteng" << std::endl; 

    std::string query = "//node[node_name='Gauteng']";

    pugi::xpath_query location_search(query.c_str());
    if (location_search.evaluate_boolean(world) == true) {
        printLocationData(world.select_single_node(query.c_str()).node());
    } else {
        std::cout << "Cannot evaluate quarry" << std::endl; 
    }
}


void extractDestinationInfo(pugi::xml_node& iNode)
{
    std::string destination = iNode.attribute("title").value();
    std::cout << "=========" << destination << "=========" << std::endl;

    // related destinations 
    std::string related;
    std::vector<std::string>::const_iterator vit = links[destination].begin();
    std::vector<std::string>::const_iterator vitend = links[destination].end();
    for (; vit != vitend; vit++) {
        related += *vit + " ";
    }

    std::cout << "Related destinations: " << related << std::endl;

    std::cout << "The web page: " << std::endl; 

    DataParser parser;
    iNode.traverse(parser);
}


void printDestinationInfo()
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("destinations.xml");
    pugi::xml_node destinations = doc.child("destinations");
    std::cout << "Destination info load result: " << result.description() << std::endl;

    int count = 0; 
    for (pugi::xml_node_iterator nodeit = destinations.begin(); nodeit != destinations.end(); nodeit++) {

        extractDestinationInfo(*nodeit);
        if (count < 2) { // only 2 pages for now !!!!!!!!!!!!!! ADIR !!!!!!!!!!!!!!!!!!!!
            count++;
        } else {
            break; 
        }
    }
}
*/
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

    XMLLocationsMap locationsMap; 
    if (locationsMap.loadXMLLocationsMap(argv[1]) == false) {
        std::cout << "Unable to load locations map data" << std::endl;
        return -1;  
    }

    //locationMap_Test(locationsMap); 
    std::string destinationsXmlFile = argv[2]; 
    XMLFile2HTMLGenerator generator(destinationsXmlFile, &locationsMap);
    if (generator.init() == false) {
        std::cout << "Unable to load destinations data DB" << std::endl; 
        return -1; 
    }

    //generator.generateHtml("Africa"); 

    return 0;
}
