//
//  testScriptingEngine.cpp
//  TinyScripting
//
//  Created by Jeppe Nielsen on 11/01/2021.
//

#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>
#include <fstream>

#include "ScriptingEngine.hpp"
#include "ScriptingParser.hpp"
#include "ScriptingCreator.hpp"
#include "ScriptingContextFactory.hpp"

#include "IScene.hpp"
#include "TypeInfo.hpp"

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
    
    ScriptingContextFactory contextFactory;
    
    ScriptingContext parserContext = contextFactory.CreateContext();
    parserContext.cppFiles.push_back("Scripts/TestScript.cpp");
    
    ScriptingParser parser(clangPath);
    
    ScriptingParserResult parserResult;
    if (!parser.Parse(parserContext, [](auto s) { return true; }, parserResult)) {
        std::cout << "Parsing failed " << std::endl;
    }
    parserResult.ToStream(std::cout);
    
    if (true)
    {
        ScriptingCreator creator;
        std::ofstream file;
        file.open("ScriptMain.cpp");
        creator.WriteMainCppFile(file, parserResult);
    }
    
    ScriptingEngine engine(clangPath);
    
    ScriptingContext context = contextFactory.CreateContext();
    context.cppFiles.push_back("Scripts/TestScript.cpp");
    context.cppFiles.push_back("ScriptMain.cpp");
    
    while (true) {
        
        if(!engine.Compile(context)) {
            std::cout << " compilation failed:" << std::endl;
            std::cout << engine.GetCompilationErrors() << std::endl;
            return 1;
        }
        
        auto createRegistryFunction = engine.GetFunction<void*()>("CreateRegistry");
        auto createSceneFunction = engine.GetFunction<IScene*(void*)>("CreateScene");
        auto addComponentFunction = engine.GetFunction<void(IScene*, GameObject, int)>("AddComponent");
        auto getComponentFunction = engine.GetFunction<TypeInfo*(IScene*, GameObject, int)>("GetComponent");
        
        
        auto registry = createRegistryFunction();
        auto scene = createSceneFunction(registry);
        
        scene->Update();
        
        auto object1 = scene->CreateGameObject();
        addComponentFunction(scene, object1, 0);
        addComponentFunction(scene, object1, 1);
        
        
        TypeInfo* velocityInfo = getComponentFunction(scene, object1, 1);
        
        FieldInfo& xField = velocityInfo->fields[0];
        auto* field = xField.GetField<float>();
        *field = 123.0f;
        
        FieldInfo& yField = velocityInfo->fields[1];
        auto* fieldY = yField.GetField<float>();
        *fieldY = 1.0f;
        
        
        
        scene->Update();
        scene->Update();
        
         
        
        
        //std::chrono::nanoseconds sleepTime(100000);
        //std::this_thread::sleep_for(sleepTime);
        
        break;
    }
        
    return 0;
}
