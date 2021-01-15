//
//  testScriptingEngine.cpp
//  TinyScripting
//
//  Created by Jeppe Nielsen on 11/01/2021.
//

#include <iostream>
#include "ScriptingEngine.hpp"

using namespace Tiny;

int main() {
    
    ScriptingEngine engine("/Users/jeppe/Downloads/clang+llvm-10.0.0-x86_64-apple-darwin");
    ScriptingContext context;
    
    context.hppFiles.push_back("/Jeppes/TinyEngine/Scripting/Scripts/Vector2.hpp");
    context.cppFiles.push_back("/Jeppes/TinyEngine/Scripting/Scripts/TestScript.txt");
    context.cppFiles.push_back("/Jeppes/TinyEngine/Scripting/Scripts/TestScript2.txt");
    
    engine.Compile(context);
    
    
    auto getResult = engine.GetFunction<int()>("GetResult");
    auto getValues = engine.GetFunction<std::vector<std::string>()>("GetValues");
        
    int result = getResult();
    std::cout << "result from script : " << result << "\n";
        
    for(auto& s : getValues()) {
        std::cout << "Value : " << s << "\n";
    }
    
    return 0;
}
