//
//  AssignChildrenSystem.cpp
//  Tiny
//
//  Created by Jeppe Nielsen on 23/02/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#include "HierarchySystem.hpp"

using namespace Tiny;
using namespace Tiny;

void HierarchySystem::Update(GameObject gameObject, Hierarchy& hierarchy) {
    auto previousParent = hierarchy.previousParent;
    auto currentParent = hierarchy.parent;
    
    if (previousParent != GameObjectNull) {
       GetComponents(previousParent, [gameObject](Hierarchy& hierarchy) {
           auto& children = hierarchy.children;
           children.erase(std::find(children.begin(), children.end(), gameObject));
       });
    }
    
    if (currentParent != GameObjectNull) {
       GetComponents(currentParent, [gameObject](Hierarchy& hierarchy) {
           hierarchy.children.push_back(gameObject);
       });
    }
    
    hierarchy.previousParent = currentParent;
}

void HierarchySystem::GameObjectRemoved(GameObject gameObject) {
    GetComponents(gameObject, [gameObject, this](Hierarchy& hierarchy) {
        if (hierarchy.parent != GameObjectNull && !IsGameObjectRemoved(hierarchy.parent)) {
            GetComponents(hierarchy.parent, [gameObject, this](Hierarchy& parentHierarchy) {
                auto it = std::find(parentHierarchy.children.begin(), parentHierarchy.children.end(), gameObject);
                parentHierarchy.children.erase(it);
            });
            hierarchy.parent = GameObjectNull;
            hierarchy.previousParent = GameObjectNull;
        }
        
        for (auto child : hierarchy.children) {
            RemoveGameObject(child);
        }
    });
}
