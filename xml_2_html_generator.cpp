
#include <iostream>
#include "xml_2_html_generator.h"
#include "locations_map.h"

bool XMLFile2HTMLGenerator::init()
{
    std::cout << "Initializing destinations tree with: " << m_db << std::endl;
    pugi::xml_parse_result result = m_destinationsTree.load_file(m_db.c_str());
    std::cout << "Destination info load result: " << result.description() << std::endl;

    if (result.status != pugi::status_ok) {
        return false; 
    }

    return true; 
}

void XMLFile2HTMLGenerator::generateHtml(const std::string& iLocation)
{
    if (iLocation.empty()) {
        generateAllDestinationsHTMLPages();
    } else {
        generateDestinationHTMLPage(iLocation);
    }
}

void XMLFile2HTMLGenerator::generateAllDestinationsHTMLPages()
{
    std::cout << "No destination name given - will generate HTML pages for all destinations" << std::endl; 
    for (pugi::xml_node_iterator nodeit = m_destinationsTree.begin(); nodeit != m_destinationsTree.end(); nodeit++)
        nodeit->traverse(*this);
}

void XMLFile2HTMLGenerator::generateDestinationHTMLPage(const std::string& iLocation)
{
    if (m_destinationsTree == NULL) {
        std::cout << "Destination tree is not initialized yet" << std::endl;
        return;
    }

    pugi::xml_node destinations = m_destinationsTree.child("destinations");

    if (destinations == NULL) {
        std::cout << "cannot locate detinations tree" << std::endl; 
        return;
    }

    std::cout << "Generate HTML pages for: " << iLocation << std::endl; 
    std::string title; 

    for (pugi::xml_node_iterator nodeit = destinations.begin(); nodeit != destinations.end(); nodeit++) {
        title = nodeit->attribute("title").value();
        std::cout << "title = " << title << std::endl;
        if (title == iLocation) {
            std::cout << std::endl << "=========" << iLocation << "=========" << std::endl;
            nodeit->traverse(*this);
            return;
        }
    }
    
    std::cout << "Could not find: " << iLocation << std::endl;
}

bool XMLFile2HTMLGenerator::for_each(pugi::xml_node& node)
{
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

        if (name == "destination") {
            std::cout << depthSign << "=== " << node.attribute("title").value() << " ===" << std::endl;

            const std::vector<std::string> *related = m_locationsMap->getLocationRelated(std::string(node.attribute("title").value()));
            std::string relatedList; 
            LocationsMap::RelatedListT::const_iterator it;
            LocationsMap::RelatedListT::const_iterator itend = related->end(); 
            for (it = related->begin(); it != itend; it++) {
                relatedList += *it + " "; 
            }
            std::cout << "   Related: " << "---> " << relatedList << std::endl; 
        } else{
            if (name != parent) {
                if (name != brother) {
                    std::cout << depthSign << "=== " << node.name() << " (parent: " << node.parent().name() << ") ===" << std::endl; 
                }
            }
        }
    } 

    return true;
}

