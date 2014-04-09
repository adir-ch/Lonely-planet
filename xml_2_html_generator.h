
#ifndef __SIMPLEHTMLGENERATOR_H_INCL__
#define __SIMPLEHTMLGENERATOR_H_INCL__

#include <string>
#include <pugixml.hpp>
#include "html_generator.h"

/**
 * TODO: Add class description
 * 
 * @author   adir
 */
class XMLFile2HTMLGenerator : public HTMLGenerator<std::string>, pugi::xml_tree_walker {
public:
    // Constructor
    XMLFile2HTMLGenerator(std::string iDB, LocationsMap *iLocationMap);

    // Destructor
    virtual ~XMLFile2HTMLGenerator();

    bool init(); 
    void generateHtml(const std::string& iLocation = ""); 
    
private: 

    void generateAllDestinationsHTMLPages(); 
    void generateDestinationHTMLPage(const std::string& iLocation);
    virtual bool for_each(pugi::xml_node& node);

    pugi::xml_document m_destinationsTree;
    std::string m_currentLocation;
};

// Constructor implementation
inline XMLFile2HTMLGenerator::XMLFile2HTMLGenerator(std::string iDB, LocationsMap *iLocationMap) : HTMLGenerator<std::string>(iDB, iLocationMap) {
}

// Destructor implementation
inline XMLFile2HTMLGenerator::~XMLFile2HTMLGenerator() {
}

#endif // __SIMPLEHTMLGENERATOR_H_INCL__
