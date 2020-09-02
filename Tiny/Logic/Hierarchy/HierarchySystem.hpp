//
//  AssignChildrenSystem.hpp
//  Tiny
//
//  Created by Jeppe Nielsen on 23/02/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include "Hierarchy.hpp"
#include "SystemChangedGameObject.hpp"
#include "ComponentView.hpp"

namespace Tiny {
    struct HierarchySystem :
        Tiny::SystemChangedGameObject<Hierarchy>,
        Tiny::SceneModifier<Hierarchy>,
        Tiny::ComponentView<Hierarchy> {
        
        void Update(Tiny::GameObject gameObject, Hierarchy& hierarchy);
        void GameObjectRemoved(Tiny::GameObject gameObject);
    };
}
