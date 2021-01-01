//
//  ScriptingEngine.hpp
//  TinyScripting
//
//  Created by Jeppe Nielsen on 01/01/2021.
//

#pragma once


namespace Tiny {
    class ScriptingEngine {
    public:
        ScriptingEngine();
        ~ScriptingEngine();
        
        
    private:
        void* interpreter;
    };
}


