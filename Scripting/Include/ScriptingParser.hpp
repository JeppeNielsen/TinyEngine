//
//  ScriptingParser.hpp
//  ScriptingEngine
//
//  Created by Jeppe Nielsen on 19/10/2021.
//

#pragma once

#include <vector>
#include <string>
#include <functional>
#include "ScriptingContext.hpp"
#include "ScriptingParserResult.hpp"

namespace Tiny {
    class ScriptingParser {
    public:
        
        ScriptingParser(const std::string& clangLocation);
        
        bool Parse(const ScriptingContext&, const std::function<bool(const std::string&)>& predicate, ScriptingParserResult& result);
        
    private:
        
        std::vector<std::string> CreateDefaultArguments();
        std::vector<std::string> GetArguments(const ScriptingContext &context);
        std::vector<std::string> defaultArguments;
        std::string GetFirstFolder(const std::string& path);
        std::string pipe_to_string( const char* command );
        
        std::string clangLocation;
    };
}

