//
//  testScriptingEngine.cpp
//  TinyScripting
//
//  Created by Jeppe Nielsen on 11/01/2021.
//

#include <iostream>
#include "ScriptingEngine.hpp"

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
    
    ScriptingEngine engine("../../../../ClingBuild/build/Output_test/");
    ScriptingContext context;
    
    context.cppFiles.push_back("../../TestCode/Scripts/TestScript.cpp");
    
    while (true) {
        if(!engine.Compile(context)) {
            std::cout <<" compilation failed" << std::endl;
                std::cout << "unable to get result from script\n";
        } else {
    
            auto getFunction = engine.GetFunction<int()>("GetResult");
    
            int value = getFunction();
    
            std::cout << "Value from script : " << value << "\n";
            
        }
    
    }
    
    
    
    
    return 0;
}
