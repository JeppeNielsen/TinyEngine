//
//  ScriptingEngine.cpp
//  TinyScripting
//
//  Created by Jeppe Nielsen on 01/01/2021.
//
#include "cling/Interpreter/Interpreter.h"
#include "cling/Interpreter/Value.h"
#include "cling/Utils/Casting.h"
#include "cling/Interpreter/CIFactory.h"
#include <sstream>
#include <fstream>

#include "ScriptingEngine.hpp"

using namespace Tiny;

cling::Interpreter& GetInterpreter(void* interpreter) {
    return *static_cast<cling::Interpreter*>(interpreter);
}

ScriptingEngine::ScriptingEngine(const std::string& clangPath)
: clangLocation(clangPath), interpreter(nullptr) {
    cling::CIFactory::SetClangPath(clangPath);
}

ScriptingEngine::~ScriptingEngine() {
    Clear();
}

void ScriptingEngine::Clear() {
    if (!interpreter) return;
    delete &GetInterpreter(interpreter);
    interpreter = nullptr;
}

bool ScriptingEngine::Compile(const ScriptingContext &context) {
    Clear();
    
    auto arguments = GetArguments(context);
    
    std::vector<const char*> argumentsList;
    for(auto& s : arguments) {
        argumentsList.push_back(s.c_str());
    }
    
    interpreter = new cling::Interpreter((int)argumentsList.size(), &argumentsList[0], "", {}, true);
    
    for(auto& cppFile : context.cppFiles) {
        CompileCppFile(cppFile);
    }
    
    return true;
}

void* ScriptingEngine::GetAddressOfGlobal(const std::string& functionName) {
    return GetInterpreter(interpreter).getAddressOfGlobal(functionName);
}

std::vector<std::string> ScriptingEngine::GetArguments(const ScriptingContext &context) {
    
    std::vector<std::string> arguments;
    
    arguments.push_back("-v");
    
    for(auto includePath : context.GetIncludePaths()) {
        arguments.push_back("-I" + includePath);
    }
    
    return arguments;
}

void ScriptingEngine::CompileCppFile(const std::string &cppFile) {
    /*
    std::ifstream t(cppFile);
    std::stringstream buffer;
    buffer << t.rdbuf();
    
    auto code = buffer.str();
    
    auto& interpreter = GetInterpreter(this->interpreter);
    interpreter.declare(code);
     */
    
    std::ifstream in(cppFile);
    
    std::string str;
    std::string all;
    while (std::getline(in, str)) {
        all += str + "\n";
    }
    auto& interpreter = GetInterpreter(this->interpreter);
    interpreter.declare(all);
}
