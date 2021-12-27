//
//  WindowFactory.hpp
//  TinyEditor
//
//  Created by Jeppe Nielsen on 05/12/2021.
//

#pragma once
#include "Registry/EditorRegistry.hpp"
#include "GameObject.hpp"

namespace TinyEditor {
class WindowFactory {
public:
    WindowFactory(EditorScene& scene);
    
    Tiny::GameObject CreateWindow(GameObject parent, const glm::vec2& position, const glm::vec2& size);
    
private:
    EditorScene& scene;
};

}
