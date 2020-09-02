//
//  QuadTreeSystemTests.cpp
//  Tiny
//
//  Created by Jeppe Nielsen on 26/07/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#include "OctreeSystemTests.hpp"
#include "ECS.hpp"
#include "WorldBoundingBox.hpp"
#include "OctreeSystem.hpp"
#include <math.h>

#define ToRadians(degrees) (0.01745329251994329576923690768489 * degrees)

using namespace Tiny::Tests;
using namespace Tiny;

void OctreeSystemTests::Run() {
 
    using ComponentTypes = Tiny::ComponentTypes<WorldBoundingBox>;
    using Registry = Tiny::Registry<ComponentTypes>;
    using Systems = Tiny::SystemTypes<OctreeSystem<>>;
    using Scene = Tiny::Scene<Registry, Systems>;

    RunTest("Octree tree insert", [] () {
        Registry registry;
        Scene scene(registry);
        
        auto go = scene.CreateGameObject();
        scene.AddComponent<WorldBoundingBox>(go);
        scene.GetComponent<WorldBoundingBox>(go).bounds = {{0,0,0}, {10,10,10}};
        
        auto& system = scene.GetSystem<OctreeSystem<>>();
        
        scene.Update();
        
        return system.octree.nodes->operator[](0)->data == go;
    });
    
    RunTest("Quad tree removal", [] () {
        Registry registry;
        Scene scene(registry);
        
        auto go = scene.CreateGameObject();
        scene.AddComponent<WorldBoundingBox>(go);
        scene.GetComponent<WorldBoundingBox>(go).bounds = {{0,0,0}, {10,10,10}};
        
        scene.Update();
        
        scene.RemoveGameObject(go);
        
        auto& system = scene.GetSystem<OctreeSystem<>>();
        
        return system.octree.nodes->size() == 0;
    });
    
}

