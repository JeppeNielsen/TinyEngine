//
//  main.cpp
//  TinyEngine
//
//  Created by Jeppe Nielsen on 30/12/2020.
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "cling/Interpreter/Interpreter.h"
#include "cling/Interpreter/Value.h"
#include "cling/Utils/Casting.h"
#include "cling/Interpreter/CIFactory.h"
#include <fstream>

#include <cstdio>
#include <unistd.h>

#include <ctime>
#include <memory>
#include <sstream>

template<typename T>
T* GetFunction(cling::Interpreter& interpreter, const std::string& functionName) {
  void* functionAddr = interpreter.getAddressOfGlobal(functionName);
  T* func = cling::utils::VoidToFunctionPtr<T*>(functionAddr);
  return func;
}

std::string pipe_to_string( const char* command )
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


int main_nono() {
    
    //Look in CIFactory.cpp line 367
    
    //cling::CIFactory::SetClangPath("/Users/jeppe/Downloads/clang+llvm-10.0.0-x86_64-apple-darwin");
    
    std::string sdkPath = pipe_to_string("xcrun --sdk macosx --show-sdk-path") + "/usr/include";
    
    
    std::string clangPath = "/Jeppes/TinyEngine/Tiny/Libs/clang";
    
    std::vector<std::string> arguments;
    
    arguments.push_back("-v");
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

    auto interpreter = new cling::Interpreter((int)argumentsList.size(), &argumentsList[0], "/Users/jeppe/Downloads/cling_2020-11-05_mac1015", {}, true);
    
    {
        std::ifstream in("TestScript.txt");
        
        std::string str;
        std::string all;
        while (std::getline(in, str)) {
            all += str + "\n";
        }
        auto res = interpreter->declare(all);
    }
    
    {
        std::ifstream in("TestScript2.txt");
        
        std::string str;
        std::string all;
        while (std::getline(in, str)) {
            all += str + "\n";
        }
        
        auto res = interpreter->declare(all);
        
    }
    
    {
        
        auto getResult = GetFunction<int()>(*interpreter, "GetResult");
        
        if (getResult) {
            int result = getResult();
        
            std::cout << "result from script : " << result << "\n";
        } else {
            
            std::cout << "Error in scripts \n";
        }
            
    }
    
    {
        
        
        auto getResult = GetFunction<std::vector<std::string>()>(*interpreter, "GetValues");
        
        if (getResult) {
            auto result = getResult();
            
            for(auto& str : result) {
                std::cout << "result from script2 : " << str << "\n";
            }
        
            
        } else {
            
            std::cout << "Error in scripts \n";
        }
            
    }
        
    return 0;
}
