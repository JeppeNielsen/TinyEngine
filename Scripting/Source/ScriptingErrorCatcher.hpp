//
//  ScriptingErrorCatcher.hpp
//  ScriptingEngine
//
//  Created by Jeppe Nielsen on 14/10/2021.
//

#pragma once

#include <iostream>
#include <sstream>

namespace Tiny {
    class ScriptingErrorCatcher {
    public:
        
        ScriptingErrorCatcher(std::stringstream& outputStream);
        ~ScriptingErrorCatcher();
        
    private:
        std::streambuf* oldBuffer;
    };
}

