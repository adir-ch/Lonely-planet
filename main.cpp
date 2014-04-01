/**
 * 	Lonely planet HTML generator
 */

#include <iostream>


#include "xml_locations_map.h"

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

struct DataParser: pugi::xml_tree_walker
{
    virtual bool for_each(pugi::xml_node& node) {
        
        std::string depthSign;
        std::string name, parent, brother; 

        for (int i = 0; i < depth(); i++) {
            depthSign += "...";
        }
        if (node.type() == pugi::node_cdata) {
            //std::cout << std::endl << depthSign << " Data: " << "Data comes here!" <<  std::endl; //node.value() <<  //std::endl << node.first_child().value() << std::endl; 
        } else {
            name = node.name(); 
            parent = node.parent().name(); 
            if (node.previous_sibling()) {
                brother = node.previous_sibling().name(); 
            }

            if (name != parent) {
                if (name != brother) {
                    std::cout << depthSign << "=== " << node.name() << " (parent: " << node.parent().name() << ") ===" << std::endl; 
                }
            }
        } 

        return true;
    }   
};

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

    std::cout << locationsMap.sprint() << std::endl; 
    std::string location = "Africa";
    std::vector<std::string> *related = locationsMap.getLocationRelated(location); 
    if (related != NULL) {
        std::string relatedList; 
        std::vector<std::string>::const_iterator it;
        std::vector<std::string>::const_iterator itend = related->end(); 
        for (it = related->begin(); it != itend; it++) {
            relatedList += *it + " "; 
        }

        std::cout << location << ": " << relatedList << std::endl; 
    }

    /*
    SimpleHtmlGenerator generator(&locationsMap);
    if (generator.loadDestinationDataDB(argv[2]) == false) {
        std::cout << "Unable to load destinations data DB" << std::endl; 
        return -1; 
    }
    */
    //generator.generateHtml("Africa"); 

    return 0;
}
