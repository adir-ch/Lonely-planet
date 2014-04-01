
#ifndef __HTMLGENERATOR_H_INCL__
#define __HTMLGENERATOR_H_INCL__

class LocationsMap; 

/**
 * TODO: Add class description
 * 
 * @author   adir
 */
template <class T> class HTMLGenerator { // HTML Generator interface
public:
    // Constructor
    HTMLGenerator(T* iDB, LocationsMap *iLocationMap);

    // Destructor
    virtual ~HTMLGenerator();

    bool init() = 0; 
    void generateHtml(const std::string& iLocation = "") = 0; 
    
protected: 

    T* m_db; 
    LocationsMap *m_locationsMap; 

};

// Constructor implementation
inline HTMLGenerator::HTMLGenerator(T* iDB, LocationsMap *iLocationMap) {
    m_db = iDB;
    m_locationsMap = iLocationMap; 
}

// Destructor implementation
inline HTMLGenerator::~HTMLGenerator() {
}


#endif // __HTMLGENERATOR_H_INCL__
