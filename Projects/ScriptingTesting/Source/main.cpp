//
//  testScriptingEngine.cpp
//  TinyScripting
//
//  Created by Jeppe Nielsen on 11/01/2021.
//

#include <iostream>
#include "ScriptingEngine.hpp"
#include "ScriptingParser.hpp"
#include <chrono>
#include <thread>
#include <sstream>

using namespace Tiny;


template<class T>
struct Collection {
    T inner;
};

struct Position {
    int x;
    int y;
};

const std::string clangPath = "/Users/jeppe/Jeppes/clang+llvm-10.0.0-x86_64-apple-darwin";

int main() {
    
    ScriptingContext context;
    
    context.hppFiles.push_back("../../Tiny/ECS/ComponentContainer.hpp");
    context.hppFiles.push_back("../../Tiny/ECS/ComponentView.hpp");
    context.hppFiles.push_back("../../Tiny/ECS/GameObject.hpp");
    context.hppFiles.push_back("../../Tiny/ECS/GameObjectCollection.hpp");
    context.hppFiles.push_back("../../Tiny/ECS/GameObjectDatabase.hpp");
    context.hppFiles.push_back("../../Tiny/ECS/IScene.hpp");
    context.hppFiles.push_back("../../Tiny/ECS/Registry.hpp");
    context.hppFiles.push_back("../../Tiny/ECS/Scene.hpp");
    context.hppFiles.push_back("../../Tiny/ECS/ECS.hpp");
    context.hppFiles.push_back("../../Tiny/ECS/SceneModifier.hpp");
    context.hppFiles.push_back("../../Tiny/ECS/SystemTask.hpp");
    
    context.hppFiles.push_back("../../Tiny/ECS/Systems/RemoveDependencies.hpp");
    context.hppFiles.push_back("../../Tiny/ECS/Systems/System.hpp");
    context.hppFiles.push_back("../../Tiny/ECS/Systems/SystemBase.hpp");
    context.hppFiles.push_back("../../Tiny/ECS/Systems/SystemChanged.hpp");
    
    context.hppFiles.push_back("../../Tiny/ECS/Systems/SystemChangedGameObject.hpp");
    context.hppFiles.push_back("../../Tiny/ECS/Systems/SystemDependencies.hpp");
    context.hppFiles.push_back("../../Tiny/ECS/Systems/SystemTypes.hpp");
    
    context.hppFiles.push_back("../../Tiny/Tools/Timer.hpp");
    
    
    context.cppFiles.push_back("../../Tiny/ECS/GameObjectCollection.cpp");
    context.cppFiles.push_back("../../Tiny/ECS/GameObjectDatabase.cpp");
    context.cppFiles.push_back("../../Tiny/ECS/SystemTask.cpp");
    
    //context.cppFiles.push_back("../../Tiny/Tools/Timer.cpp");
    
    context.cppFiles.push_back("Scripts/TestScript.cpp");
    
    
    
    ScriptingParser parser(clangPath);
    
    ScriptingParserResult parserResult;
    if (!parser.Parse(context, [](auto s) { return true; }, parserResult)) {
        std::cout << "Parsing failed " << std::endl;
    }
    
    std::cout << "Components:"<<std::endl;
    for(auto g : parserResult.components) {
        std::cout << g.name << std::endl;
        
        for(auto field : g.fields) {
            std::cout << " -> " << field.type << " : " <<  field.name << std::endl;
        }
    }
    
    std::cout << "Systems:"<<std::endl;
    for (auto s : parserResult.systems) {
        std::cout << s.name << std::endl;
    }
    
    return 0;
    
    ScriptingEngine engine(clangPath);
    
    
    while (true) {
        
        
        //freopen("new_stdout","w",stdout);
       
        if(!engine.Compile(context)) {
            std::cout << " compilation failed:" << std::endl;
            std::cout << engine.GetCompilationErrors() << std::endl;
            return 1;
        }
        
        //freopen("/dev/tty","r",stdout);
        
        auto getResult = engine.GetFunction<int()>("GetResult");
        int result = getResult();
        std::cout << "result from script : " << result << "\n";
        
        std::chrono::nanoseconds sleepTime(100000);
        
        std::this_thread::sleep_for(sleepTime);
        
        break;
    }
        
    return 0;
}
