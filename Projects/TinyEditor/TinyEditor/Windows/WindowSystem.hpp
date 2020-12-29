//
//  WindowSystem.hpp
//  TinyEditor
//
//  Created by Jeppe Nielsen on 17/09/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#pragma once

#include "ECS.hpp"
#include "Window.hpp"
#include "EditorWindow.hpp"
#include "WorldTransform.hpp"
#include "Sizeable.hpp"
#include "EditorRegistry.hpp"
#include <map>

namespace Editor {
struct WindowSystem : Tiny::SystemChangedGameObject<const Editor::Window, const Tiny::WorldTransform, const Tiny::Sizeable>,
Tiny::SceneModifier<Editor::Window> {
public:
    
    void CreateMainWindow();
    void Update(Tiny::GameObject gameObject, const Editor::Window& window, const Tiny::WorldTransform& worldTransform, const Tiny::Sizeable& sizeable);
    
    
    void GameObjectRemoved(Tiny::GameObject gameObject);
    
    using Windows = std::map<Tiny::GameObject, EditorWindow>;
    Windows windows;
    
    EditorWindow mainWindow;
    EditorRegistryType* registry;
    InputDevice* inputDevice;
    
    
    
    VertexRenderer<Vertex>* vertexRenderer;
    Shader<Vertex>* shader;
    
};
}

