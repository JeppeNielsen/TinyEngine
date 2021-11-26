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
#include <dirent.h>

#include "ScriptingEngine.hpp"
#include "ScriptingErrorCatcher.hpp"

using namespace Tiny;

cling::Interpreter& GetInterpreter(void* interpreter) {
    return *static_cast<cling::Interpreter*>(interpreter);
}

ScriptingEngine::ScriptingEngine(const std::string& clangPath)
: clangLocation(clangPath), interpreter(nullptr) {
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
    
    argumentsList.clear();
    for(auto& s : arguments) {
        argumentsList.push_back(s.c_str());
    }
    
    std::stringstream interpreterErrorsBuffer;
    {
        //ScriptingErrorCatcher errorCatcher(interpreterErrorsBuffer);
        interpreter = new cling::Interpreter((int)argumentsList.size(), &argumentsList[0], clangLocation.c_str(), {}, false);
    }
    
    std::stringstream compilationErrorsBuffer;
    bool anyCompilationErrors = false;
    {
        //ScriptingErrorCatcher errorCatcher(compilationErrorsBuffer);
        for(auto& cppFile : context.cppFiles) {
            if (!CompileCppFile(cppFile)) {
                anyCompilationErrors = true;
                break;
            }
        }
    }
    compilationErrors = anyCompilationErrors ? compilationErrorsBuffer.str() : "";
    
    return !anyCompilationErrors;
}

std::string& ScriptingEngine::GetCompilationErrors() {
    return compilationErrors;
}

void* ScriptingEngine::GetAddressOfGlobal(const std::string& functionName) {
    return GetInterpreter(interpreter).getAddressOfGlobal(functionName);
}

std::vector<std::string> ScriptingEngine::GetArguments(const ScriptingContext &context) {
    
    if (defaultArguments.empty()) {
        defaultArguments = CreateDefaultArguments();
    }
    
    std::vector<std::string> arguments = defaultArguments;
    
    for(auto includePath : context.GetIncludePaths()) {
        arguments.push_back("-I" + includePath);
    }
    
    return arguments;
}

bool ScriptingEngine::CompileCppFile(const std::string &cppFile) {
    
    std::ifstream t(cppFile);
    std::stringstream buffer;
    buffer << t.rdbuf();
    
    auto code = buffer.str();
    
    auto& interpreter = GetInterpreter(this->interpreter);
    auto result = interpreter.declare(code);

    return result == cling::Interpreter::kSuccess;
}

std::vector<std::string> ScriptingEngine::CreateDefaultArguments() {
    
    std::vector<std::string> arguments;
    
    //std::string sdkPath = pipe_to_string("xcrun --sdk macosx --show-sdk-path") + "/usr/include";
    
    arguments.push_back("-v");
    arguments.push_back("-std=c++14");
    arguments.push_back("-fno-rtti");
    arguments.push_back("-Wno-nullability-completeness");
    //arguments.push_back("-I" + clangLocation + "/include/c++/v1");
    //arguments.push_back("-I" + clangLocation + "/lib/clang/" + GetFirstFolder(clangLocation + "/lib/clang") + "/include");
    //arguments.push_back("-I" + sdkPath);
    
    return arguments;
}
 
std::string ScriptingEngine::pipe_to_string( const char* command )
{
    FILE* file = popen( command, "r" ) ;

    if( file )
    {
        std::stringstream stm;

        constexpr std::size_t MAX_LINE_SZ = 1024 ;
        char line[MAX_LINE_SZ] ;

        while( fgets( line, MAX_LINE_SZ, file ) ) stm << line;

        pclose(file) ;
        std::string str = stm.str() ;
        str = str.substr(0,str.length() - 1);
        return str;
    }

    return "" ;
}

std::string ScriptingEngine::GetFirstFolder(const std::string &path) {
    
    std::string foundPath = "";
    
    DIR *dir = opendir(path.c_str());

    struct dirent *entry = readdir(dir);

    while (entry != NULL)
    {
        if (entry->d_type == DT_DIR) {
            foundPath = std::string(entry->d_name);
            
            if (foundPath != "." && foundPath!="..") {
                break;
            }
        }
        entry = readdir(dir);
    }

    closedir(dir);
    
    return foundPath;
}
