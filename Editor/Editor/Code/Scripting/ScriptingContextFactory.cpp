//
//  ScriptingContextFactory.cpp
//  ScriptingTesting
//
//  Created by Jeppe Nielsen on 20/10/2021.
//

#include "ScriptingContextFactory.hpp"

using namespace Tiny;

ScriptingContextFactory::ScriptingContextFactory(const std::string& tinyPath) : tinyPath(tinyPath) {
    
}

ScriptingContext ScriptingContextFactory::CreateContext() {
    
    ScriptingContext context;
    
    context.hppFiles.push_back(tinyPath+"/ECS/ComponentContainer.hpp");
    context.hppFiles.push_back(tinyPath+"/ECS/ComponentView.hpp");
    context.hppFiles.push_back(tinyPath+"/ECS/GameObject.hpp");
    context.hppFiles.push_back(tinyPath+"/ECS/GameObjectCollection.hpp");
    context.hppFiles.push_back(tinyPath+"/ECS/GameObjectDatabase.hpp");
    context.hppFiles.push_back(tinyPath+"/ECS/IScene.hpp");
    context.hppFiles.push_back(tinyPath+"/ECS/Registry.hpp");
    context.hppFiles.push_back(tinyPath+"/ECS/Scene.hpp");
    context.hppFiles.push_back(tinyPath+"/ECS/ECS.hpp");
    context.hppFiles.push_back(tinyPath+"/ECS/SceneModifier.hpp");
    context.hppFiles.push_back(tinyPath+"/ECS/SystemTask.hpp");
    
    context.hppFiles.push_back(tinyPath+"/ECS/Systems/RemoveDependencies.hpp");
    context.hppFiles.push_back(tinyPath+"/ECS/Systems/System.hpp");
    context.hppFiles.push_back(tinyPath+"/ECS/Systems/SystemBase.hpp");
    context.hppFiles.push_back(tinyPath+"/ECS/Systems/SystemChanged.hpp");
    
    context.hppFiles.push_back(tinyPath+"/ECS/Systems/SystemChangedGameObject.hpp");
    context.hppFiles.push_back(tinyPath+"/ECS/Systems/SystemDependencies.hpp");
    context.hppFiles.push_back(tinyPath+"/ECS/Systems/SystemTypes.hpp");
    
    context.hppFiles.push_back(tinyPath+"/Tools/Timer.hpp");
    
    context.cppFiles.push_back(tinyPath+"/ECS/GameObjectCollection.cpp");
    context.cppFiles.push_back(tinyPath+"/ECS/GameObjectDatabase.cpp");
    context.cppFiles.push_back(tinyPath+"/ECS/SystemTask.cpp");
    
    
    context.hppFiles.push_back(tinyPath+"/Reflection/TypeInfo.hpp");
    context.hppFiles.push_back(tinyPath+"/Reflection/FieldInfo.hpp");
    context.cppFiles.push_back(tinyPath+"/Reflection/TypeInfo.cpp");
    
    context.hppFiles.push_back(tinyPath+"/Serialization/FieldSerializer.hpp");
    
    context.hppFiles.push_back(tinyPath+"/../External/minijson_reader/minijson_reader.hpp");
    context.hppFiles.push_back(tinyPath+"/../External/minijson_writer/minijson_writer.hpp");
    
    //context.cppFiles.push_back("../../Tiny/Tools/Timer.cpp");
    
    return context;
}
