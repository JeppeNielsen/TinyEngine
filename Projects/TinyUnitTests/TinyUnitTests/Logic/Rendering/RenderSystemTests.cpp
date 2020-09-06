//
//  RenderSystemTests.cpp
//  Tiny
//
//  Created by Jeppe Nielsen on 27/07/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#include "RenderSystemTests.hpp"
#include "RenderSystem.hpp"
#include "OctreeSystem.hpp"

using namespace Tiny;

void RenderSystemTests::Run() {

    using ComponentTypes = Tiny::ComponentTypes<WorldBoundingBox, WorldTransform, Camera, Mesh>;
    using Registry = Tiny::Registry<ComponentTypes>;
    using Systems = Tiny::SystemTypes<RenderOctreeSystem, RenderSystem>;
    using Scene = Tiny::Scene<Registry, Systems>;

    RunTest("Render System ",[]() {
        
        Registry registry;
        Scene scene(registry);
        
        auto cameraGameObject = scene.CreateGameObject();
        scene.AddComponent<WorldTransform>(cameraGameObject);
        scene.AddComponent<Camera>(cameraGameObject, glm::vec2(1024,768));

        auto renderObject1 = scene.CreateGameObject();
        scene.AddComponent<WorldBoundingBox>(renderObject1, BoundingBox({0,0.0f,0.0f}, glm::vec3(256,256,256)));
    
        auto renderObject2 = scene.CreateGameObject();
        scene.AddComponent<WorldBoundingBox>(renderObject2, BoundingBox({3000,20,20}, glm::vec3(256,256,256)));
    
        scene.Update();
        
        scene.GetComponent<WorldBoundingBox>(renderObject2).bounds.center = {0.0f,0.0f,0.0f};
        
        scene.Update();
        
        return true;
    });
    
}
