//
//  EditorScene.hpp
//  TinyEditor
//
//  Created by Jeppe Nielsen on 11/10/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include "ECS.hpp"
#include "EditorRegistry.hpp"

namespace Editor {

class EditorScene {
public:
    EditorScene(EditorRegistryType& registry, InputDevice& device, VertexRenderer<Vertex>* vertexRenderer, Shader<Vertex>* shader);
    void Update();
    void Render(ivec2 viewportSize);
    
private:
    GameObject CreateMesh();
    GameObject CreateQuad(const glm::vec3& pos, const glm::vec3& scale, GameObject meshObject, GameObject parent = GameObjectNull);
    
    EditorSceneType scene;
    InputDevice& device;
};

}
