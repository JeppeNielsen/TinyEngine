//
//  EditorScene.cpp
//  TinyEditor
//
//  Created by Jeppe Nielsen on 11/10/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#include "EditorScene.hpp"

using namespace Editor;

EditorScene::EditorScene(EditorRegistryType& registry, InputDevice& device, VertexRenderer<Vertex>* vertexRenderer, Shader<Vertex>* shader) : scene(registry), device(device) {
    
    scene.GetSystem<InputSystem>().SetDevice(device);
    scene.GetSystem<RenderSystem>().vertexRenderer = vertexRenderer;
    scene.GetSystem<RenderSystem>().shader = shader;
    
    //scene.GetSystem<PickableSystem>().screenSize = device.Screen.Size;
    
    {
        auto cameraGO = scene.CreateGameObject();
        scene.AddComponent<WorldTransform>(cameraGO, glm::translate(glm::mat4x4(1.0f), glm::vec3(0.0f,0.0f,0.0f)));
        scene.AddComponent<Camera>(cameraGO, glm::vec2(8,8), -0.1f, 10.0f);
        scene.AddComponent<LocalTransform>(cameraGO);
        scene.AddComponent<Hierarchy>(cameraGO);
        scene.AddComponent<Input>(cameraGO);
    }
    auto mesh = CreateMesh();
    auto first = CreateQuad({0,0,0}, {2,2,1}, mesh);
    CreateQuad({3,0,0}, {2,2,1}, mesh, first);
    
    //scene.Log = true;
}

GameObject EditorScene::CreateMesh() {
    auto quadGO = scene.CreateGameObject();
    scene.AddComponent<Mesh>(quadGO);
    auto& mesh = scene.GetComponent<Mesh>(quadGO);
    
    mesh.vertices.push_back({ { -0.5f,-0.5f,0.0f }, {0,0}, Color(0.0f, 0.0f, 1.0f) });
    mesh.vertices.push_back({ { 0.5f,-0.5f,0.0f }, {1,0}, Color(0.0f, 0.0f, 1.0f) });
    mesh.vertices.push_back({ { 0.5f,0.5f,0.0f }, {1,1}, Color(1.0f, 1.0f, 1.0f) });
    mesh.vertices.push_back({ { -0.5f,0.5f,0.0f }, {0,1}, Color(1.0f, 1.0f, 1.0f) });
    
    mesh.triangles.push_back(0);
    mesh.triangles.push_back(1);
    mesh.triangles.push_back(2);
    
    mesh.triangles.push_back(0);
    mesh.triangles.push_back(2);
    mesh.triangles.push_back(3);

    return quadGO;
}

GameObject EditorScene::CreateQuad(const glm::vec3& pos, const glm::vec3& scale, GameObject meshObject, GameObject parent) {
    
    auto quadGO = scene.CreateGameObject();
    
    LocalTransform local;
    local.position = pos;
    local.scale = scale;
    
    scene.AddComponent<LocalTransform>(quadGO, local);
    scene.AddComponent<WorldTransform>(quadGO);
    scene.AddComponent<Hierarchy>(quadGO);
    scene.ReferenceComponent<Mesh>(quadGO, meshObject);
    
    scene.GetComponent<Hierarchy>(quadGO).parent = parent;
    
    BoundingBox boundingBox;
    boundingBox.center = {0,0,0};
    boundingBox.extends = {0.5f,0.5f,0.5f};
    
    scene.AddComponent<LocalBoundingBox>(quadGO, boundingBox);
    scene.AddComponent<WorldBoundingBox>(quadGO);
    
    scene.AddComponent<Rotator>(quadGO, 1.0f);
    //scene.AddComponent<Draggable>(quadGO);
    scene.AddComponent<Pickable>(quadGO);
    
    return quadGO;
}

void EditorScene::Update() {
    scene.Update();
}

void EditorScene::Render(ivec2 viewportSize) {
    scene.GetSystem<RenderSystem>().RenderScene();
}
