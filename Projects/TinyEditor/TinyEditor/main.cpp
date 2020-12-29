//
//  main.cpp
//  Tiny
//
//  Created by Jeppe Nielsen on 30/07/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#include "Engine.hpp"
#include "OpenGL.hpp"
#include "ECS.hpp"
#include "WindowSystem.hpp"
#include "InputSystem.hpp"
#include "HierarchySystem.hpp"
#include "HierarchyWorldTransformSystem.hpp"
#include "WorldTransformSystem.hpp"
#include "WorldBoundingBoxSystem.hpp"
#include "MeshBoundingBoxSystem.hpp"
#include "PickableSystem.hpp"
#include "DraggableSystem.hpp"
#include "QuadMeshSystem.hpp"
#include "WindowDragCancelSystem.hpp"
#include "EditorRegistry.hpp"

using namespace Tiny;
using namespace Editor;

struct State : IState {
    
    using ComponentTypes = ComponentTypes<
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
    using Systems = SystemTypes<
        InputSystem,
        WindowSystem,
        HierarchySystem, HierarchyWorldTransformSystem,
        WorldTransformSystem,
        WorldBoundingBoxSystem, MeshBoundingBoxSystem,
        PickableSystem, PickableOctreeSystem,
        DraggableSystem,
        QuadMeshSystem,
        WindowDragCancelSystem
    >;
    
    using Registry = Registry<ComponentTypes>;
    using Scene = Scene<Registry, Systems>;

    Registry registry;
    Scene scene;
    
    EditorRegistryType editorRegistry;
    
    VertexRenderer<Vertex>* vertexRenderer;
    Shader<Vertex>* shader;
    
    State() : scene(registry) {
        
    }
    
    void Initialize() override {
        
        
        scene.GetSystem<WindowSystem>().registry = &editorRegistry;
        
        scene.GetSystem<WindowSystem>().inputDevice = &device.Input.Device();
        
        
        scene.GetSystem<WindowSystem>().CreateMainWindow();
        
        
        vertexRenderer = new VertexRenderer<Vertex>();
        shader = new Shader<Vertex>();
        
        shader->Load(
            SHADER_SOURCE(
                attribute vec4 Position;
                attribute vec4 Color;
                uniform mat4 ViewProjection;
                varying vec4 vColor;
                void main() {
                    vColor = Color;
                    gl_Position = ViewProjection * Position;
                }
            )
            ,
            SHADER_SOURCE(
                varying vec4 vColor;
                            
                void main() {
                    gl_FragColor = vColor;
                }
            )
        );
        
        
        
        scene.GetSystem<WindowSystem>().vertexRenderer = vertexRenderer;
        scene.GetSystem<WindowSystem>().shader = shader;
        
        
        scene.GetSystem<InputSystem>().SetDevice(device.Input.Device());
        scene.GetSystem<PickableSystem>().screenSize = device.Screen.Size();
        scene.GetSystem<DraggableSystem>().screenSize = device.Screen.Size();
        
        vec2 screenSize = device.Screen.Size() / 2;
        
        {
            auto windowCamera = scene.CreateGameObject();
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
        }
        
        {
            CreateWindow({0.0f,0.0f}, {200.0f,200.0f}).color = {1.0f,0.0f,0.0f};
            //CreateWindow({200.0f,0.0f},{ 200.0f, 200.0f}).color = {0.0f,0.0f,1.0f};
            
        }
        
        device.Input.TouchDown.Bind([] (TouchEvent e) {
            std::cout << "Down : " << e.Position.x << "  " << e.Position.y << " : " << e.Index << "\n";
        });
        
        device.Input.TouchUp.Bind([] (TouchEvent e) {
            std::cout << "Up : " << e.Position.x << "  " << e.Position.y << " : "<< e.Index << "\n";
        });
        
        //scene.WriteGraph(std::cout);
        
        device.Input.ButtonDown.Bind([this] (ButtonEvent e) {
            if (e.Id == "n") {
                CreateWindow({0,0}, {300,200});
            }
        });
    }
    
    Window& CreateWindow(vec2 pos, vec2 size) {
        
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
        localTransform.position = vec3(pos,0.0f);
        
        return scene.GetComponent<Window>(windowGameObject);
    }
    
    void Update(float dt) override {
        //std::cout << 1.0f / dt << std::endl;
        scene.Update();
        registry.ResetChanged(); 
        editorRegistry.ResetChanged();
    }
    
    void Render() override {
        glClearColor(100/255.0f, 149/255.0f, 237/255.0f, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    
};

int main() {
    Engine e;
    e.Start<State>();
    return 0;
}
