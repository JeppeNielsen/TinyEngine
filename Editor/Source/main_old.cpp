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
#include "Engine.hpp"
#include "OpenGL.hpp"

using namespace Tiny;


template<class T>
struct Collection {
    T inner;
};

struct Position {
    int x;
    int y;
};

const std::string clangPath = "/Users/jeppe/Jeppes/ClingBuild/build/Output";

struct MainScreen : IState {
  
    void Initialize() {
        
    }
    
    void Update(float dt) {
        
    }
    
    void Render() {
        glClearColor(1,1,1,0);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    
};


int main_old() {
    
    Tiny::Engine engine;
    engine.Start<MainScreen>();
    
    return 0;
    
    /*
    
    ScriptingContext scriptFiles;
    scriptFiles.cppFiles.push_back("Build/TestScript.cpp");
    
    ScriptingParser scriptParser(clangPath);
    
    ScriptingParserResult scriptParserResult;
    if (!scriptParser.Parse(scriptFiles, [](auto s) { return true; }, scriptParserResult)) {
        std::cout << "Parsing failed " << std::endl;
        return EXIT_FAILURE;
    }
    scriptParserResult.ToStream(std::cout);
    
    return 0;
    
    
    ScriptingEngine scriptRunner(clangPath);
    
    if (!scriptRunner.Compile(scriptFiles)) {
        std::cout << "Failed" << std::endl;
        return 0;
    }
    
    auto function = scriptRunner.GetFunction<int()>("TestMyScript");
    
    auto ret = function();
    std::cout << ret << std::endl;
    
    return 0;r
     */
     
    while (true) {
        
        auto startTime = std::chrono::high_resolution_clock::now();
    
    ScriptingContextFactory contextFactory("../../../Tiny");
    
    ScriptingContext parserContext = contextFactory.CreateContext();
    parserContext.cppFiles.push_back("Scripts/TestScript.cpp");
    
    ScriptingParser parser;
    
    ScriptingParserResult parserResult;
    if (!parser.Parse(parserContext, [](auto s) { return true; }, parserResult)) {
        std::cout << "Parsing failed " << std::endl;
        return EXIT_FAILURE;
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
    
        
        if(!engine.Compile(context)) {
            std::cout << " compilation failed:" << std::endl;
            std::cout << engine.GetCompilationErrors() << std::endl;
            continue;
        }
        
        auto createRegistryFunction = engine.GetFunction<void*()>("CreateRegistry");
        auto createSceneFunction = engine.GetFunction<IScene*(void*)>("CreateScene");
        auto addComponentFunction = engine.GetFunction<void(IScene*, GameObject, int)>("AddComponent");
        auto getComponentFunction = engine.GetFunction<TypeInfo*(IScene*, GameObject, int)>("GetComponent");
        
        auto deleteRegistryFunction = engine.GetFunction<void(void*)>("DeleteRegistry");
        auto deleteSceneFunction = engine.GetFunction<void(void*)>("DeleteScene");
        
        auto registry = createRegistryFunction();
        auto scene = createSceneFunction(registry);
        
        scene->Update();
        
        auto object1 = scene->CreateGameObject();
        addComponentFunction(scene, object1, 0);
        addComponentFunction(scene, object1, 1);
        addComponentFunction(scene, object1, 2);
        
        TypeInfo* velocityInfo = getComponentFunction(scene, object1, 2);
        
        FieldInfo& xField = velocityInfo->fields[0];
        auto* field = xField.GetField<float>();
        *field = 123.0f;
        
        FieldInfo& yField = velocityInfo->fields[1];
        auto* fieldY = yField.GetField<float>();
        *fieldY = 1.0f;
        
        TypeInfo* renderableInfo = getComponentFunction(scene, object1, 1);
        
        FieldInfo& imageNoField = renderableInfo->fields[0];
        auto* imageNo = imageNoField.GetField<int>();
        *imageNo = 12;
        
        
        for (int i=0; i<10; i++) {
            scene->Update();
        }
        
        deleteSceneFunction(scene);
        deleteRegistryFunction(registry);
        
        
        auto endTime = std::chrono::high_resolution_clock::now();
        
        auto diff = endTime - startTime;
        
        
        
        std::chrono::microseconds d = std::chrono::duration_cast< std::chrono::microseconds >( diff );
        
        std::cout << "Milliseconds : " << (float)d.count() / 1000000 << std::endl;

        //std::chrono::nanoseconds sleepTime(100000);
        //std::this_thread::sleep_for(sleepTime);
        
    }
        
    return 0;
}
