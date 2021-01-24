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
    interpreter = new cling::Interpreter((int)argumentsList.size(), &argumentsList[0], clangLocation.c_str(), {}, true);
    
    /*
    std::string sdkPath = pipe_to_string("xcrun --sdk macosx --show-sdk-path") + "/usr/include";
    
    std::vector<std::string> arguments;
    
    arguments.push_back("-I/Jeppes/TinyEngine/Scripting/Source/Scripts");
    arguments.push_back("-I" + sdkPath);
    arguments.push_back("-I/Users/jeppe/Downloads/cling_2020-11-05_mac1015/include");
    
    
    //arguments.push_back("-I" + sdkPath);
    //arguments.push_back("-I/Users/jeppe/Downloads/clang+llvm-10.0.0-x86_64-apple-darwin/lib/clang/10.0.0/include");
    //arguments.push_back("-std=c++11");
    //arguments.push_back("-stdlib=libstdc++");
    //arguments.push_back("-I /Users/jeppe/Downloads/cling_2019-01-01_mac1013/lib/clang/5.0.0/include" );
    //arguments.push_back("-I /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include" );
    //arguments.push_back("-isystem /Users/jeppe/Downloads/clang+llvm-10.0.0-x86_64-apple-darwin/include/c++/v1/");
    //arguments.push_back("-I /Users/jeppe/Downloads/clang+llvm-10.0.0-x86_64-apple-darwin/lib/clang/10.0.0/include");

    
    std::vector<const char*> argumentsList;
    for(auto& s : arguments) {
        argumentsList.push_back(s.c_str());
    }

    interpreter = new cling::Interpreter((int)argumentsList.size(), &argumentsList[0], "/Users/jeppe/Downloads/cling_2020-11-05_mac1015", {}, true);
    */
    
    for(auto& cppFile : context.cppFiles) {
        CompileCppFile(cppFile);
    }
    
    return true;
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

void ScriptingEngine::CompileCppFile(const std::string &cppFile) {
    
    std::ifstream t(cppFile);
    std::stringstream buffer;
    buffer << t.rdbuf();
    
    auto code = buffer.str();
    
    auto& interpreter = GetInterpreter(this->interpreter);
    interpreter.declare(code);
     
    /*
    std::ifstream in(cppFile);
    
    std::string str;
    std::string all;
    while (std::getline(in, str)) {
        all += str + "\n";
    }
    auto& interpreter = GetInterpreter(this->interpreter);
    interpreter.declare(all);
     */
}

std::vector<std::string> ScriptingEngine::CreateDefaultArguments() {
    
    std::vector<std::string> arguments;
    
    std::string sdkPath = pipe_to_string("xcrun --sdk macosx --show-sdk-path") + "/usr/include";
    
    arguments.push_back("-v");
    arguments.push_back("-std=c++14");
    arguments.push_back("-fno-rtti");
    //arguments.push_back("-I"+clangLocation+"/include");
    arguments.push_back("-I" + sdkPath);
    arguments.push_back("-I" + clangLocation + "/include/c++/v1");
    arguments.push_back("-I" + clangLocation + "/lib/clang/" + GetFirstFolder(clangLocation + "/lib/clang") + "/include");
    
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
