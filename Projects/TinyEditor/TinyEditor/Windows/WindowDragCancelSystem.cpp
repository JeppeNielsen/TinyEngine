//
//  WindowDragCancelSystem.cpp
//  TinyEditor
//
//  Created by Jeppe Nielsen on 09/10/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#include "WindowDragCancelSystem.hpp"

using namespace Editor;
using namespace Tiny;

void WindowDragCancelSystem::Update(Editor::Window& window, Tiny::Draggable& draggable, Tiny::Sizeable& sizeable, Tiny::LocalTransform& localTransform) {
    if (!window.updateFromOS) return;
    draggable.isDragging = false;
    sizeable.size = vec3(window.osSize.x, window.osSize.y,0.0f);
    localTransform.position = vec3(window.osPosition.x, window.osPosition.y,0.0f);
    window.updateFromOS = false;
}
