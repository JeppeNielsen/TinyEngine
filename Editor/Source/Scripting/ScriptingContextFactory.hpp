//
//  ScriptingContextFactory.hpp
//  ScriptingTesting
//
//  Created by Jeppe Nielsen on 20/10/2021.
//

#pragma once
#include "ScriptingContext.hpp"

namespace Tiny{
    class ScriptingContextFactory {
    public:
        ScriptingContextFactory(const std::string& tinyPath);
        
        ScriptingContext CreateContext();
    private:
        std::string tinyPath;
    };
}
