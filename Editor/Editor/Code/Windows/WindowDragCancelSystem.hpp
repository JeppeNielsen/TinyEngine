//
//  WindowDragCancelSystem.hpp
//  TinyEditor
//
//  Created by Jeppe Nielsen on 09/10/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#pragma once

#include "ECS.hpp"
#include "Window.hpp"
#include "EditorWindow.hpp"
#include "Draggable.hpp"
#include "Sizeable.hpp"
#include "LocalTransform.hpp"
#include "WindowSystem.hpp"
#include "DraggableSystem.hpp"
#include "WorldTransformSystem.hpp"
#include "HierarchyWorldTransformSystem.hpp"

#include <map>

namespace TinyEditor {
struct WindowDragCancelSystem : Tiny::System<Window, Tiny::Draggable, Tiny::Sizeable, Tiny::LocalTransform>,
Tiny::RemoveDependencies<WindowSystem, Tiny::DraggableSystem> //}, Tiny::WorldTransformSystem, Tiny::HierarchyWorldTransformSystem>
{
public:
    void Update(Window& window, Tiny::Draggable& draggable, Tiny::Sizeable& sizeable, Tiny::LocalTransform& localTransform);
};
}
