

#include "xml_2_html_generator.h"

bool XMLFile2HTMLGenerator::init()
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(m_db);
    std::cout << "Destination info load result: " << result.description() << std::endl;

    if (result.status != status_ok) {
        return false; 
    }

    m_destinationsTree = doc.child("destinations");
    
    if (m_destinationsTree == NULL) {
        std::cout << "Cannot find destination DB" << std::endl;
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
    for (pugi::xml_node_iterator nodeit = destinations.begin(); nodeit != destinations.end(); nodeit++)
        nodeit->traverse(*this);
}

void XMLFile2HTMLGenerator::generateDestinationHTMLPage(iLocation)
{
    std::cout << "Generate HTML pages for: " << iLocation << std::endl; 
    pugi::xml_node destination = m_destinationsTree.child(iLocation); 
    if (destination == NULL) {
        std::cout << "Cannot find destination: " << iLocation; 
        return;
    }
    
    std::cout << std::endl << "=========" << destination << "=========" << std::endl;
    destination.traverse(*this);
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

        if (name != parent) {
            if (name != brother) {
                std::cout << depthSign << "=== " << node.name() << " (parent: " << node.parent().name() << ") ===" << std::endl; 
            }
        }
    } 

    return true;
}

