
#ifndef __HTMLGENERATOR_H_INCL__
#define __HTMLGENERATOR_H_INCL__

/**
 * TODO: Add class description
 * 
 * @author   adir
 */
class HTMLGenerator : public pugi::xml_tree_walker {
public:
    // Constructor
    HTMLGenerator();

    // Destructor
    virtual ~HTMLGenerator();

    // Copy constructor
    // TODO: Uncomment the copy constructor when you need it.
    //HTMLGenerator(const HTMLGenerator& src);

    // Assignment operator
    // TODO: Uncomment the assignment operator when you need it.
    //HTMLGenerator& operator=(const HTMLGenerator& src);
};

// Constructor implementation
inline HTMLGenerator::HTMLGenerator() {
}

// Destructor implementation
inline HTMLGenerator::~HTMLGenerator() {
}

// TODO: Uncomment the copy constructor when you need it.
//inline HTMLGenerator::HTMLGenerator(const HTMLGenerator& src)
//{
//   // TODO: copy
//}

// TODO: Uncomment the assignment operator when you need it.
//inline HTMLGenerator& HTMLGenerator::operator=(const HTMLGenerator& rhs)
//{
//   if (this == &rhs) {
//      return *this;
//   }
//
//   // TODO: assignment
//
//   return *this;
//}

#endif // __HTMLGENERATOR_H_INCL__
