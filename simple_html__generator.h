
#ifndef __SIMPLEHTMLGENERATOR_H_INCL__
#define __SIMPLEHTMLGENERATOR_H_INCL__

#include "HTMLGenerator.h"

/**
 * TODO: Add class description
 * 
 * @author   adir
 */
class SimpleHTMLGenerator : public HTMLGenerator {
public:
    // Constructor
    SimpleHTMLGenerator();

    // Destructor
    virtual ~SimpleHTMLGenerator();

    // Copy constructor
    // TODO: Uncomment the copy constructor when you need it.
    //SimpleHTMLGenerator(const SimpleHTMLGenerator& src);

    // Assignment operator
    // TODO: Uncomment the assignment operator when you need it.
    //SimpleHTMLGenerator& operator=(const SimpleHTMLGenerator& src);
};

// Constructor implementation
inline SimpleHTMLGenerator::SimpleHTMLGenerator() : HTMLGenerator() {
}

// Destructor implementation
inline SimpleHTMLGenerator::~SimpleHTMLGenerator() {
}

// TODO: Uncomment the copy constructor when you need it.
//inline SimpleHTMLGenerator::SimpleHTMLGenerator(const SimpleHTMLGenerator& src)
//{
//   // TODO: copy
//}

// TODO: Uncomment the assignment operator when you need it.
//inline SimpleHTMLGenerator& SimpleHTMLGenerator::operator=(const SimpleHTMLGenerator& rhs)
//{
//   if (this == &rhs) {
//      return *this;
//   }
//
//   // TODO: assignment
//
//   return *this;
//}

#endif // __SIMPLEHTMLGENERATOR_H_INCL__
