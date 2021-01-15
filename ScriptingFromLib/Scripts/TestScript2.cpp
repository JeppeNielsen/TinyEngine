#include <stdio.h>
#include <vector>
#include <string>

#include "Vector2.hpp"

extern "C" {
    std::vector<std::string> GetValues() {
        std::vector<std::string> values;
        values.push_back("One");
        values.push_back("Two");
        return values;
    }
}
