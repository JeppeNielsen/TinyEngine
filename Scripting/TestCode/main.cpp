//
//  testScriptingEngine.cpp
//  TinyScripting
//
//  Created by Jeppe Nielsen on 11/01/2021.
//

#include <iostream>
#include "ScriptingEngine.hpp"
#include "ScriptingParser.hpp"

using namespace Tiny;


template<class T>
struct Collection {
    T inner;
};

struct Position {
    int x;
    int y;
};
 

int main() {
    
    ScriptingParser parser("../../../../ClingBuild/build_old/Output_test/lib/clang/9.0.1/include");
    
    
    ScriptingEngine engine("../../../../ClingBuild/build_old/Output_test/");
    ScriptingContext context;
    
    context.cppFiles.push_back("../../TestCode/Scripts/TestScript.cpp");
    
    ScriptingParserResult result;
    
    parser.Parse(context, [](const std::string& s) {
        std::cout << s << std::endl;
        return true;
    }, result);
    
    result.ToStream(std::cout);
   
    while (true) {
        if(!engine.Compile(context)) {
            std::cout <<" compilation failed" << std::endl;
                std::cout << "unable to get result from script\n";
        } else {
    
            auto getFunction = engine.GetFunction<int(int)>("GetResult");
    
            int value = getFunction(1000);
    
            std::cout << "Value from script : " << value << "\n";
            
        }
    
    }
    
    
    
    
    return 0;
}
