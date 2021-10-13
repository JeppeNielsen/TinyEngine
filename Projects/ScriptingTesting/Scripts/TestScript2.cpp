#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>

#include "Vector2.hpp"

extern "C" {
    std::vector<std::string> GetValues() {

        std::vector<std::string> values;
        values.push_back("One");
        values.push_back("Two");

        Vector2 vec;
        vec += {1,1}; 

        std::stringstream s;
        s<<vec.Length();

        values.push_back(s.str());

        return values;
    }
}
