#ifndef __TEXTPROCESS_H__
#define __TEXTPROCESS_H__
#include <iostream>
#include <string>

// Abstract base class that provides the necessary interface for concrete decorators and concrete
// subclasses being decorated.
class TextProcessor {
  public:
    // Passes the input source down to the concrete subclass being decorated that reads input.
    virtual void setSource(std::istream *in) = 0;
    // Retrieves the next non-empty word from the pipeline; std::ios::failure is raised when EOF is detected.
    virtual std::string getWord() = 0;
    virtual ~TextProcessor();
};

#endif
