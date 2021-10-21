//
//  ScriptingCreator.hpp
//  ScriptingTesting
//
//  Created by Jeppe Nielsen on 20/10/2021.
//

#pragma once
#include <ostream>
#include "ScriptingParserResult.hpp"

namespace Tiny {
    class ScriptingCreator {
    
    public:
        ScriptingCreator();
        
        void WriteMainCppFile(std::ostream& stream, ScriptingParserResult& result);
        
    private:
        void WriteIncludes(std::ostream& stream, ScriptingParserResult& result);
        void WriteECSDefinitions(std::ostream& stream, ScriptingParserResult& result);
        void WriteComponents(std::ostream &stream, ScriptingParserResult &result);
        void WriteSystems(std::ostream &stream, ScriptingParserResult &result);

        void WriteRegistryFunctions(std::ostream& stream, ScriptingParserResult& result);
        void WriteSceneFunctions(std::ostream& stream, ScriptingParserResult& result);
        void WriteTypeInfoFactory(std::ostream& stream, ScriptingParserResult& result);
    };

}
