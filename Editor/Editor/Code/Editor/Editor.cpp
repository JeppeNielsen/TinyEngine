//
//  MainWindow.cpp
//  TinyEditor
//
//  Created by Jeppe Nielsen on 05/12/2021.
//

#include "Editor.hpp"
#include "OpenGL.hpp"
#include <string>

using namespace TinyEditor;


Editor::Editor() : scene(registry), windowFactory(scene) {
    
}

void Editor::Initialize() {

    context.ProjectRoot = "/Users/jeppe/Jeppes/TinyEngine/Editor/TestProjects/Pong";
    
    for(auto p : context.ProjectRoot) {
        std::cout << p << std::endl;
    }
    
    //for(auto const& dir_entry : iterator)
    //        std::cout << dir_entry << '\n';
    
    //scene.GetSystem<WindowSystem>().registry = &editorRegistry;
    //scene.GetSystem<WindowSystem>().inputDevice = &device.Input.Device();

    scene.GetSystem<InputSystem>().SetDevice(device.Input.Device());
    scene.GetSystem<PickableSystem>().screenSize = device.Screen.Size();
    scene.GetSystem<DraggableSystem>().screenSize = device.Screen.Size();
    
    scene.GetSystem<WindowSystem>().CreateMainWindow();
    
    vec2 screenSize = device.Screen.Size() / 2;
    
    windowCamera = scene.CreateGameObject();
    scene.AddComponent<Input>(windowCamera);
    scene.AddComponent<WorldTransform>(windowCamera);
    scene.AddComponent<Camera>(windowCamera);
    scene.AddComponent<LocalTransform>(windowCamera);
    scene.AddComponent<Hierarchy>(windowCamera);
    Camera& camera = scene.GetComponent<Camera>(windowCamera);
    camera.ViewSize = screenSize;
    camera.Near = -0.1f;
    camera.Far = 1.0f;
    
    auto& localTransform = scene.GetComponent<LocalTransform>(windowCamera);
    localTransform.position = vec3(screenSize,0.0f);
    
    windowFactory.CreateWindow(windowCamera, {0,0}, {200,200});
    windowFactory.CreateWindow(windowCamera, {200,0}, {200,200});

    this->device.Input.ButtonDown.Bind([&](ButtonEvent e){
        windowFactory.CreateWindow(windowCamera, {200,0}, {200,200});
    });
}

void Editor::Update(float dt) {
    scene.Update();
    registry.ResetChanged();
}

void Editor::Render() {
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT);
}
