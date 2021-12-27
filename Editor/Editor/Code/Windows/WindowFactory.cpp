//
//  WindowFactory.cpp
//  TinyEditor
//
//  Created by Jeppe Nielsen on 05/12/2021.
//

#include "WindowFactory.hpp"

using namespace TinyEditor;
using namespace Tiny;

WindowFactory::WindowFactory(EditorScene& scene) : scene(scene) {}

GameObject WindowFactory::CreateWindow(GameObject parent, const glm::vec2 &position, const glm::vec2 &size) {
    
    auto windowGameObject = scene.CreateGameObject();
    
    scene.AddComponent<Window>(windowGameObject);
    scene.AddComponent<Hierarchy>(windowGameObject);
    scene.AddComponent<LocalTransform>(windowGameObject);
    scene.AddComponent<WorldTransform>(windowGameObject);
    scene.AddComponent<LocalBoundingBox>(windowGameObject);
    scene.AddComponent<WorldBoundingBox>(windowGameObject);
    scene.AddComponent<Mesh>(windowGameObject);
    scene.AddComponent<QuadMesh>(windowGameObject);
    scene.AddComponent<Sizeable>(windowGameObject, vec3(size,0));
    scene.AddComponent<Pickable>(windowGameObject);
    scene.AddComponent<Draggable>(windowGameObject);
    
    auto& localTransform = scene.GetComponent<LocalTransform>(windowGameObject);
    localTransform.position = vec3(position,0.0f);
    
    //scene.GetComponent<Hierarchy>(windowGameObject).parent = parent;
    
    return windowGameObject;
    
}


