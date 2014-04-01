/**
 * 	Lonely planet HTML generator
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <pugixml.hpp>

std::map<std::string, std::vector<std::string> > links; 

void updateLinksMap(std::string location, std::string parentLocation)
{
    if (location.empty()) {
        return; 
    }

    //std::cout << "Updating map - name: " << location << ", parent: " << parentLocation << std::endl; 
    std::pair<std::map<std::string, std::vector<std::string> >::iterator, bool> rc;

    std::vector<std::string> v;
    rc = links.insert(std::make_pair<std::string, std::vector<std::string> >(location, v)); 
    if (rc.second == false) 
        std::cout << location << " - already exist" << std::endl; 

    if (parentLocation.empty() == false) {
        rc.first->second.push_back(parentLocation); 
        links[parentLocation].push_back(location);
    }  
}

struct LinksBuilder: pugi::xml_tree_walker
{
    virtual bool for_each(pugi::xml_node& node) {
        //for (int i = 0; i < depth(); ++i) std::cout << "  "; // indentation
        if (std::string(node.name()) == "node_name") {
            //std::cout << "*** name='" << node.name() << "', value='" << node.first_child().value() << std::endl; 
            //std::cout << "*** name: " << node.first_child().value() << ", parent: " << node.parent().parent().child("node_name").first_child().value() << std::endl; 
            updateLinksMap(node.first_child().value(), node.parent().parent().child("node_name").first_child().value());
        } 
        return true; // continue traversal
    }
};


void buildLinksMap() 
{
    pugi::xml_document doc;

    pugi::xml_parse_result result = doc.load_file("taxonomy.xml");
    //pugi::xml_node world = doc.child("taxonomies").child("taxonomy").child("node");
    std::cout << "Destination map load result: " << result.description() << std::endl;

    LinksBuilder builder;
    doc.traverse(builder);

    return; 

    /*
    std::cout << "Links map:" << std::endl;
    std::map<std::string, std::vector<std::string> >::const_iterator it;
    for (it = links.begin(); it != links.end(); it++) {
        std::string related;
        std::vector<std::string>::const_iterator vit; 
        for (vit = it->second.begin(); vit != it->second.end(); vit++) {
            related += *vit + " ";
        }
        std::cout << it->first << " related: " << related << std::endl;
    } 
    */ 
}

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

void generateHtmlPage(std::string name)
{

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

//////////////////////////////////////////////////////// Main

int main(int argc, char *argv[]) {

    
    std::cout << "Lonely planet HTML generator" << std::endl;

    //printDestinationLocations();
    buildLinksMap(); 
    printDestinationInfo();
    return 0;
}
