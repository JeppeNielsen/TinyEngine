//
//  PickableSystem.hpp
//  Tiny
//
//  Created by Jeppe Nielsen on 21/08/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include "ECS.hpp"
#include "WorldTransform.hpp"
#include "Camera.hpp"
#include "OctreeSystem.hpp"
#include "Mesh.hpp"
#include "VertexRenderer.hpp"
#include "Shader.hpp"
#include "TaskRunner.hpp"
#include "Pickable.hpp"
#include "Input.hpp"
#include "WorldTransformSystem.hpp"
#include "HierarchyWorldTransformSystem.hpp"

namespace Tiny {

using PickableOctreeSystem = OctreeSystem<const WorldTransform, const Pickable, const Mesh>;

struct PickableSystem :
    Tiny::System<const WorldTransform, const Camera, const Input>,
    Tiny::SystemDependencies<PickableOctreeSystem>,
    Tiny::ComponentView<Pickable>,
    Tiny::RemoveDependencies<PickableOctreeSystem, WorldTransformSystem, HierarchyWorldTransformSystem> {
        void Initialize(PickableOctreeSystem& octreeSystem);
        void Update(const WorldTransform& transform, const Camera& camera, const Input& input);
        void TouchDown(const WorldTransform& transform, const Camera& camera, const Input& input, const InputTouch& touch);
        void TouchUp(const WorldTransform& transform, const Camera& camera, const Input& input, const InputTouch& touch);
        
        PickableOctreeSystem* octreeSystem;
        ivec2 screenSize;
        
        struct DownPickable {
            InputTouch touch;
            Tiny::GameObject gameObject;
        };
        
        std::vector<DownPickable> activePickables;
        std::vector<DownPickable> resetPickables;
        
        
    };
}
