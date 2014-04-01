
#ifndef __SIMPLEHTMLGENERATOR_H_INCL__
#define __SIMPLEHTMLGENERATOR_H_INCL__

#include <string>
#include <pugixml.hpp>
#include "HTMLGenerator.h"

/**
 * TODO: Add class description
 * 
 * @author   adir
 */
class XMLFile2HTMLGenerator : public HTMLGenerator<std::string>, pugi::xml_tree_walker {
public:
    // Constructor
    XMLFile2HTMLGenerator(T* iDB, LocationsMap *iLocationMap);

    // Destructor
    virtual ~XMLFile2HTMLGenerator();

    bool init(); 
    void generateHtml(const std::string& iLocation = ""); 
    
private: 

    void generateAllDestinationsHTMLPages(); 
    void generateDestinationHTMLPage(iLocation);
    virtual bool for_each(pugi::xml_node& node);

    pugi::xml_node m_destinationsTree;
    std::string m_currentLocation;
};

// Constructor implementation
inline XMLFile2HTMLGenerator::XMLFile2HTMLGenerator(T* iDB, LocationsMap *iLocationMap) : HTMLGenerator(iDB, iLocationMap) {
}

// Destructor implementation
inline XMLFile2HTMLGenerator::~XMLFile2HTMLGenerator() {
}

#endif // __SIMPLEHTMLGENERATOR_H_INCL__
