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
    
    ScriptingEngine engine("/Users/jeppe/Downloads/clang+llvm-10.0.0-x86_64-apple-darwin");
    ScriptingContext context;
    
    context.hppFiles.push_back("/Jeppes/TinyEngine/Scripting/Scripts/Vector2.hpp");
    context.cppFiles.push_back("/Jeppes/TinyEngine/Scripting/Scripts/TestScript.cpp");
    context.cppFiles.push_back("/Jeppes/TinyEngine/Scripting/Scripts/TestScript2.cpp");
    
    if(!engine.Compile(context)) {
        std::cout << " compilation failed" << std::endl;
        return 1;
    }
    
    auto getResult = engine.GetFunction<int()>("GetResult");
    auto getValues = engine.GetFunction<std::vector<std::string>()>("GetValues");
        
    int result = getResult();
    std::cout << "result from script : " << result << "\n";
        
    for(auto& s : getValues()) {
        std::cout << "Value : " << s << "\n";
    }
    
    context.cppFiles.push_back("/Jeppes/TinyEngine/Scripting/Scripts/TestScript3.cpp");
    if(!engine.Compile(context)) {
        std::cout << " compilation failed" << std::endl;
        return 1;
    }
    
    auto getSize = engine.GetFunction<int(int)>("GetSize");
    
    int size = getSize(333);
    std::cout << "result from recompiled script: " << size << "\n";
    
    
    Collection<int> collection;
    collection.inner = 123;
    
    auto getCollection = engine.GetFunction<int(Collection<int>&)>("GetCollection");
    
    int collectionSize = getCollection(collection);
    
    std::cout << "collection size: " << collectionSize << "\n";
    
    std::vector<Position> positions;
    
    auto addPosition = engine.GetFunction<void(std::vector<Position>&)>("AddPosition");
    
    addPosition(positions);
    addPosition(positions);
    addPosition(positions);
    
    for(auto pos : positions) {
        std::cout << "Pos.x = " << pos.x << " Pos.y = " << pos.y << std::endl;
    }
    
    return 0;
}
