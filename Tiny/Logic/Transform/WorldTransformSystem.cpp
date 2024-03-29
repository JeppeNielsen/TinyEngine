//
//  TransformSystem.cpp
//  Tiny
//
//  Created by Jeppe Nielsen on 19/02/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#include "WorldTransformSystem.hpp"
#include <glm/mat4x4.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace Tiny;
using namespace glm;



void WorldTransformSystem::Initialize(HierarchyWorldTransformSystem&) {

}

void WorldTransformSystem::Changed(const LocalTransform& localTransform, const Hierarchy& hierarchy, WorldTransform& worldTransform) {
    worldTransform.isDirty = true;
}

void WorldTransformSystem::Update(const LocalTransform& localTransform, const Hierarchy& hierarchy, WorldTransform& worldTransform) {
    if (!worldTransform.isDirty) {
        return;
    }
    worldTransform.isDirty = false;
    
    const mat4x4 local = localTransform.GetLocalToParent();
    
    if (hierarchy.parent != Tiny::GameObjectNull) {
        WorldTransform* parentTransform;
        GetComponents(hierarchy.parent, [this, &parentTransform](const LocalTransform& parentLocalTransform, const Hierarchy& parentHierarchy, WorldTransform& parentWorldTransform) {
            Update(parentLocalTransform, parentHierarchy, parentWorldTransform);
            parentTransform = &parentWorldTransform;
        });
        worldTransform.world = parentTransform->world * local;
    } else {
        worldTransform.world = local;
    }
    worldTransform.worldInverse = glm::inverse(worldTransform.world);
}
