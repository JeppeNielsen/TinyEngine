//
//  MainWindow.hpp
//  TinyEditor
//
//  Created by Jeppe Nielsen on 05/12/2021.
//

#include "Engine.hpp"
#include "OpenGL.hpp"
#include "ECS.hpp"
#include "Context/EditorContext.hpp"
#include "Registry/EditorRegistry.hpp"
#include "Windows/WindowFactory.hpp"

namespace TinyEditor {

class Editor : public Tiny::IState {
public:
    Editor();
    void Initialize();
    void Update(float dt);
    void Render();
private:

    GameObject windowCamera;

    EditorContext context;
    
    EditorRegistry registry;
    EditorScene scene;
    WindowFactory windowFactory;
    
};

}
