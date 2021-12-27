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
#include "Windows/WindowSystem.hpp"
#include "Windows/WindowDragCancelSystem.hpp"

using namespace Tiny;
using namespace TinyEditor;

using EditorComponents = ComponentTypes<
    Input,
    Window,
    Hierarchy,
    LocalTransform, WorldTransform,
    LocalBoundingBox, WorldBoundingBox,
    Pickable,
    Draggable,
    Mesh,
    QuadMesh,
    Sizeable,
    Camera
>;

using EditorSystems = SystemTypes<
    InputSystem,
    HierarchySystem, HierarchyWorldTransformSystem,
    WorldTransformSystem,
    WorldBoundingBoxSystem, MeshBoundingBoxSystem,
    PickableSystem, PickableOctreeSystem,
    DraggableSystem,
    QuadMeshSystem,
    WindowSystem,
    WindowDragCancelSystem
>;

using EditorRegistry = Registry<EditorComponents>;
using EditorScene = Scene<EditorRegistry, EditorSystems>;
