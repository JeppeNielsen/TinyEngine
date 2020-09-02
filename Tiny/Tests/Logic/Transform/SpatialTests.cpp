//
//  SpatialTests.cpp
//  Tiny
//
//  Created by Jeppe Nielsen on 19/02/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#include "SpatialTests.hpp"
#include "WorldTransformSystem.hpp"
#include "HierarchySystem.hpp"
#include "Timer.hpp"

using namespace Tiny::Tests;


void SpatialTests::Run() {

    using ComponentTypes = Tiny::ComponentTypes<LocalTransform, WorldTransform, Hierarchy>;
    using Registry = Tiny::Registry<ComponentTypes>;
    using Systems = Tiny::SystemTypes<WorldTransformSystem, HierarchyWorldTransformSystem, HierarchySystem>;
    using Scene = Tiny::Scene<Registry, Systems>;

    RunTest("LocalTransform ctor gives default values",[]() {
        LocalTransform t;
        
        return t.position == glm::vec3(0,0,0) &&
                t.rotation == quat(1,0,0,0) &&
                t.scale == glm::vec3(1,1,1);
    });
    
    RunTest("LocalTransform applied to WorldTransform",[]() {
        
        Registry registry;
        Scene scene(registry);
        
        const glm::vec3 position = {10,10,10};
        
        auto object = scene.CreateGameObject();
        scene.AddComponent<LocalTransform>(object);
        scene.AddComponent<WorldTransform>(object);
        scene.AddComponent<Hierarchy>(object);
        scene.GetComponent<LocalTransform>(object).position = position;
        
        scene.Update();
        
        auto actual = scene.GetComponent<WorldTransform>(object).world;
        auto expected = translate(mat4x4(1.0f), position);
        
        return actual == expected;
    });
    
    RunTest("Child LocalTransform Affected by Parent",[]() {
        
        Registry registry;
        Scene scene(registry);
        
        const glm::vec3 parentPosition = {10,10,10};
        const glm::vec3 childPosition = {20,20,20};
        
        auto parent = scene.CreateGameObject();
        scene.AddComponent<LocalTransform>(parent);
        scene.AddComponent<WorldTransform>(parent);
        scene.AddComponent<Hierarchy>(parent);
        scene.GetComponent<LocalTransform>(parent).position = parentPosition;
        
        auto child = scene.CreateGameObject();
        scene.AddComponent<LocalTransform>(child);
        scene.AddComponent<WorldTransform>(child);
        scene.AddComponent<Hierarchy>(child);
        
        scene.GetComponent<Hierarchy>(child).parent = parent;
        scene.GetComponent<LocalTransform>(child).position = childPosition;
        
        scene.Update();
        
        auto actual = scene.GetComponent<WorldTransform>(child).world;
        auto expected = translate(mat4x4(1.0f), parentPosition + childPosition);
        
        return actual == expected;
    });
    
    RunTest("Child reparented WorldTransform should reflect",[]() {
        
        Registry registry;
        Scene scene(registry);
        
        const glm::vec3 parentPosition = {10,10,10};
        const glm::vec3 childPosition = {20,20,20};
        
        auto parent = scene.CreateGameObject();
        scene.AddComponent<LocalTransform>(parent);
        scene.AddComponent<WorldTransform>(parent);
        scene.AddComponent<Hierarchy>(parent);
        scene.GetComponent<LocalTransform>(parent).position = parentPosition;
        
        auto child = scene.CreateGameObject();
        scene.AddComponent<LocalTransform>(child);
        scene.AddComponent<WorldTransform>(child);
        scene.AddComponent<Hierarchy>(child);
        
        scene.GetComponent<Hierarchy>(child).parent = parent;
        scene.GetComponent<LocalTransform>(child).position = childPosition;
        
        scene.Update();
        
        
        bool parentPositionWasApplied = scene.GetComponent<WorldTransform>(child).world ==
            translate(mat4x4(1.0f), parentPosition + childPosition);
   
        scene.GetComponent<Hierarchy>(child).parent = Tiny::GameObjectNull;
   
        scene.Update();
   
       bool parentPositionNotApplied = scene.GetComponent<WorldTransform>(child).world ==
        translate(mat4x4(1.0f), childPosition);
   
        return parentPositionWasApplied &&
               parentPositionNotApplied;
    });
    
    RunTest("Parent moved, Child should be moved also",[]() {
         
         Registry registry;
         Scene scene(registry);
         
         const glm::vec3 parentPositionStart = {10,10,10};
         const glm::vec3 parentPositionEnd = {20,20,20};
         const glm::vec3 childPosition = {20,20,20};
         
         auto parent = scene.CreateGameObject();
         scene.AddComponent<LocalTransform>(parent);
         scene.AddComponent<WorldTransform>(parent);
         scene.AddComponent<Hierarchy>(parent);
         scene.GetComponent<LocalTransform>(parent).position = parentPositionStart;
         
         auto child = scene.CreateGameObject();
         scene.AddComponent<LocalTransform>(child);
         scene.AddComponent<WorldTransform>(child);
         scene.AddComponent<Hierarchy>(child);
         
         scene.GetComponent<LocalTransform>(child).position = childPosition;
         scene.GetComponent<Hierarchy>(child).parent = parent;
         
         scene.Update();
         
        bool childPositionEqualsStart = scene.GetComponent<WorldTransform>(child).world ==
        translate(mat4x4(1.0f), parentPositionStart + childPosition);
        
         scene.GetComponent<LocalTransform>(parent).position = parentPositionEnd;
    
         scene.Update();
         
         auto childWorld = scene.GetComponent<WorldTransform>(child).world;
    
        bool childPositionEqualsEnd = childWorld ==
        translate(mat4x4(1.0f), parentPositionEnd + childPosition);
        
         return childPositionEqualsStart &&
                childPositionEqualsEnd;
     });
    
    
    RunTest("Multiple children affected by parent's movement",[]() {
         
        const int numChildren = 100;
        
        Registry registry;
        Scene scene(registry);

        const glm::vec3 parentPositionStart = {10,10,10};
        const glm::vec3 parentPositionEnd = {20,20,20};
        const glm::vec3 childPosition = {20,20,20};

        auto parent = scene.CreateGameObject();
        scene.AddComponent<LocalTransform>(parent);
        scene.AddComponent<WorldTransform>(parent);
        scene.AddComponent<Hierarchy>(parent);
        scene.GetComponent<LocalTransform>(parent).position = parentPositionStart;
         
        std::vector<Tiny::GameObject> children;
        
        for (int i=0; i<numChildren; ++i) {
            auto child = scene.CreateGameObject();
            scene.AddComponent<LocalTransform>(child);
            scene.AddComponent<WorldTransform>(child);
            scene.AddComponent<Hierarchy>(child);
            
            scene.GetComponent<LocalTransform>(child).position = childPosition;
            scene.GetComponent<Hierarchy>(child).parent = parent;
            children.push_back(child);
        }
        
        scene.Update();
        
        auto targetWorld = translate(mat4x4(1.0f), parentPositionStart + childPosition);
        
        bool anyNotAligned = false;
        for(auto child : children) {
            auto childWorld = scene.GetComponent<WorldTransform>(child).world;
            if (childWorld!=targetWorld) {
                anyNotAligned = true;
            }
        }
        
        return !anyNotAligned;
    });
    
}
