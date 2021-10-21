//
//  ScriptingContextFactory.cpp
//  ScriptingTesting
//
//  Created by Jeppe Nielsen on 20/10/2021.
//

#include "ScriptingContextFactory.hpp"

using namespace Tiny;

ScriptingContext ScriptingContextFactory::CreateContext() {
    
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
    
    
    context.hppFiles.push_back("../../Tiny/Reflection/TypeInfo.hpp");
    context.hppFiles.push_back("../../Tiny/Reflection/FieldInfo.hpp");
    context.cppFiles.push_back("../../Tiny/Reflection/TypeInfo.cpp");
    
    context.hppFiles.push_back("../../Tiny/Serialization/FieldSerializer.hpp");
    
    context.hppFiles.push_back("../../External/minijson_reader/minijson_reader.hpp");
    context.hppFiles.push_back("../../External/minijson_writer/minijson_writer.hpp");
    
    
    
    //context.cppFiles.push_back("../../Tiny/Tools/Timer.cpp");
    
    return context;
}
