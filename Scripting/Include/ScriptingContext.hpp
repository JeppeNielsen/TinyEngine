//
//  ScriptingContext.hpp
//  TinyScripting
//
//  Created by Jeppe Nielsen on 10/01/2021.
//

#pragma once
#include <string>
#include <vector>

namespace Tiny {
struct ScriptingContext {
    using FileCollection = std::vector<std::string>;
    
    FileCollection hppFiles;
    FileCollection cppFiles;
    
    FileCollection GetIncludePaths() const;
    
};
}
