//
//  ScriptingContext.cpp
//  TinyScripting
//
//  Created by Jeppe Nielsen on 10/01/2021.
//

#include "ScriptingContext.hpp"
#include <set>

using namespace Tiny;

std::string GetPathFromIncludeFile(const std::string& includeFile)
{
     size_t pos = includeFile.find_last_of("\\/");
     return (std::string::npos == pos)
         ? ""
         : includeFile.substr(0, pos);
}

ScriptingContext::FileCollection ScriptingContext::GetIncludePaths() const {
    std::set<std::string> unique;
    for(auto& includePath : hppFiles) {
        unique.insert(GetPathFromIncludeFile(includePath));
    }
    
    FileCollection includePaths;
    includePaths.assign(unique.begin(), unique.end());
    return includePaths;
}
