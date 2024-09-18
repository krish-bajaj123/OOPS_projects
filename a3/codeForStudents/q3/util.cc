#include "util.h"
#include <sstream>

bool getString( std::istream & in, std::string & s ) {
    std::string line;
    getline( in, line );
    if ( in.fail() ) return false;
    s = line;
    return true;
} // getString

bool getInteger( std::istream & in, int & i ) {
    std::string s;
    int value;
    getline( in, s );
    if ( in.fail() ) return false;
    if ( std::istringstream iss{s}; !(iss >> value) ) return false;
    i = value;
    return true;
} // getInteger
