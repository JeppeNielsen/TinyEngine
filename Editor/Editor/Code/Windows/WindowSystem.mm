//
//  WindowSystem.cpp
//  TinyEditor
//
//  Created by Jeppe Nielsen on 17/09/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#include "WindowSystem.hpp"

using namespace TinyEditor;
using namespace Tiny;

void WindowSystem::CreateMainWindow() {
    mainWindow.CreateMain("Editor", 1280, 720);
}

void WindowSystem::Update(GameObject gameObject, const Window &window, const Tiny::WorldTransform &worldTransform, const Tiny::Sizeable& sizeable) {
    
    auto& editorWindow = windows[gameObject];
    if (!editorWindow.IsCreated()) {
        editorWindow.size = ivec2(sizeable.size.x, sizeable.size.y);
        editorWindow.CreateTool(mainWindow.GetHandle(), "Tool window");
        editorWindow.color = window.color;
       //editorWindow.editorScene = new EditorScene(*registry, *inputDevice, vertexRenderer, shader);
    }
    
    if (editorWindow.needsUpdate) {
        editorWindow.needsUpdate = false;
        Window* modifyWindow = (Window*)&window;
        modifyWindow->updateFromOS = true;
        modifyWindow->osSize = editorWindow.size;
        modifyWindow->osPosition = editorWindow.position;
    }
    
    if (!editorWindow.isDead) {
        vec4 worldPosition = {0.0f,0.0f,0.0f,1.0f};
        worldPosition = worldTransform.world * worldPosition;
        editorWindow.SetFrame(worldPosition, sizeable.size);
        editorWindow.Update();
    } else {
        Modify([gameObject] (SceneModifier& modifier) {
            modifier.RemoveGameObject(gameObject);
        });
    }
}

void WindowSystem::GameObjectRemoved(Tiny::GameObject gameObject) {
    auto it = windows.find(gameObject);
    it->second.Close();
    windows.erase(it);
}
