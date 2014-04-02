
#ifndef __HTMLGENERATOR_H_INCL__
#define __HTMLGENERATOR_H_INCL__

#include <string>

class LocationsMap; 

/**
 * TODO: Add class description
 * 
 * @author   adir
 */
template <class T> class HTMLGenerator { // HTML Generator interface
public:
    // Constructor
    HTMLGenerator(T iDB, LocationsMap *iLocationMap) :m_db(iDB), m_locationsMap(iLocationMap) {};

    // Destructor
    virtual ~HTMLGenerator() {};

    virtual bool init() = 0; 
    virtual void generateHtml(const std::string& iLocation = "") = 0; 
    
protected: 

    T m_db; 
    LocationsMap *m_locationsMap; 

};

#endif // __HTMLGENERATOR_H_INCL__
