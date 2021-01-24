//
//  ScriptingEngine.hpp
//  TinyScripting
//
//  Created by Jeppe Nielsen on 01/01/2021.
//

#pragma once
#include <string>
#include "ScriptingContext.hpp"

namespace Tiny {
    class ScriptingEngine {
    public:
        ScriptingEngine(const std::string& clangPath);
        ~ScriptingEngine();
    
        void Clear();
        bool Compile(const ScriptingContext& context);
        
    private:
        template <class T>
        T VoidToFunctionPtr(void *ptr) {
            union { T f; void *v; } tmp;
            tmp.v = ptr;
            return tmp.f;
        }
   
    public:
        template<typename T>
        T* GetFunction(const std::string& functionName) {
            void* functionAddr = GetAddressOfGlobal(functionName);
            T* func = VoidToFunctionPtr<T*>(functionAddr);
            return func;
        }
        
    private:
        void* GetAddressOfGlobal(const std::string& functionName);
        std::vector<std::string> GetArguments(const ScriptingContext& context);
        void CompileCppFile(const std::string& cppFile);
        std::vector<std::string> CreateDefaultArguments();
        std::string pipe_to_string( const char* command );
        std::string GetFirstFolder(const std::string& path);
        
        void* interpreter;
        std::vector<const char*> argumentsList;
        std::string clangLocation;
        std::vector<std::string> defaultArguments;
    };
}


