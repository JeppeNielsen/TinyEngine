//
//  DraggableSystem.hpp
//  TinyEditor
//
//  Created by Jeppe Nielsen on 23/09/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#pragma once

#include "ECS.hpp"
#include "Draggable.hpp"
#include "Pickable.hpp"
#include "LocalTransform.hpp"
#include "WorldTransform.hpp"
#include "WorldTransformSystem.hpp"
#include "HierarchyWorldTransformSystem.hpp"

namespace Tiny {
    struct DraggableSystem : System<Draggable, const Pickable, const WorldTransform, LocalTransform>,
    Tiny::RemoveDependencies<WorldTransformSystem, HierarchyWorldTransformSystem> {

        void Update(Draggable& draggable,
                    const Pickable& pickable,
                    const WorldTransform& worldTransform,
                    LocalTransform& localTransform);
        
         std::function<ivec2()> screenSizeFunction;
    };
}
