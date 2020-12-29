//
//  EditorRegistry.hpp
//  TinyEditor
//
//  Created by Jeppe Nielsen on 11/10/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include "ECS.hpp"
#include "RenderSystem.hpp"
#include "InputSystem.hpp"
#include "HierarchySystem.hpp"
#include "HierarchyWorldTransformSystem.hpp"
#include "WorldTransformSystem.hpp"
#include "WorldBoundingBoxSystem.hpp"
#include "MeshBoundingBoxSystem.hpp"
#include "PickableSystem.hpp"
#include "DraggableSystem.hpp"
#include "QuadMeshSystem.hpp"
#include "WorldBoundingBoxSystem.hpp"
#include "WorldBoundingBoxSystem.hpp"
#include "WorldBoundingBoxSystem.hpp"
#include "WorldBoundingBoxSystem.hpp"

using namespace Tiny;


struct Rotator {
    float speed;
};

struct RotatorSystem : System<LocalTransform, const Rotator> {
    void Update(LocalTransform& local, const Rotator& rotator) {
        local.rotation *= glm::angleAxis(glm::radians(rotator.speed), vec3(0,0,1));
    }
    
    constexpr int EnableConcurrency() { return 5000; }
};


using EditorComponentTypes = ComponentTypes<
    Input,
    Hierarchy,
    LocalTransform, WorldTransform,
    LocalBoundingBox, WorldBoundingBox,
    Pickable,
    Draggable,
    Mesh,
    QuadMesh,
    Sizeable,
    Camera,
    Rotator
>;

using EditorSystems = SystemTypes<
    InputSystem,
    HierarchySystem, HierarchyWorldTransformSystem,
    WorldTransformSystem,
    WorldBoundingBoxSystem, MeshBoundingBoxSystem,
    PickableSystem, PickableOctreeSystem,
    DraggableSystem,
    QuadMeshSystem,
    RenderSystem,
    RotatorSystem
>;

using EditorRegistryType = Registry<EditorComponentTypes>;
using EditorSceneType = Scene<EditorRegistryType, EditorSystems>;
