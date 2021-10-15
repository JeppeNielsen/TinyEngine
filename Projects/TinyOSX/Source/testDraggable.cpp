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
#include "RenderSystem.hpp"
#include "WorldBoundingBoxSystem.hpp"
#include "WorldTransformSystem.hpp"
#include "HierarchySystem.hpp"
#include "InputSystem.hpp"
#include "PickableSystem.hpp"
#include "DraggableSystem.hpp"
#include <memory>
#include "QuadMeshSystem.hpp"
#include "MeshBoundingBoxSystem.hpp"

using namespace Tiny;


struct Rotator {
    float speed;
};

struct RotatorSystem : System<LocalTransform, const Rotator> {
    void Update(LocalTransform& local, const Rotator& rotator) {
        local.rotation *= glm::angleAxis(glm::radians(rotator.speed), vec3(0,0,1));
    }
    
    constexpr int EnableConcurrency() { return 5000; }
};

struct Collider {
    
    
};

using ColliderOctreeSystem = OctreeSystem<const Sizeable, const Collider>;

struct ColliderSystem :
SystemChanged<const Sizeable, const WorldTransform, const WorldBoundingBox, Collider>,
SystemDependencies<ColliderOctreeSystem> {
    
    ColliderOctreeSystem* octreeSystem;
    
    void Initialize(ColliderOctreeSystem& octreeSystem) {
        this->octreeSystem = &octreeSystem;
    }
    
    void Changed(const Sizeable& sizeable, const WorldTransform& worldTransform, const WorldBoundingBox& worldBoundingBox, Collider& collider) {
           
           
    }
  
    void Update(const Sizeable& sizeable, const WorldTransform& worldTransform, const WorldBoundingBox& worldBoundingBox, Collider& collider) {
        
        std::vector<GameObject> objects;
        octreeSystem->Query(worldBoundingBox.bounds, objects);
        
        if (objects.size()>1) {
            
            std::cout << "HIT" << std::endl;
        }
        
    }
    
};

struct Colorizer {
    float hue;
    float speed;
};

struct ColorizerSystem : System<Mesh, Colorizer> {
    void Update(Mesh& mesh, Colorizer& colorizer) {
        colorizer.hue += colorizer.speed;
        double dHue = 360.0 / mesh.vertices.size();
        for (int i=0; i<mesh.vertices.size(); ++i) {
            mesh.vertices[i].Color = Color::HslToRgb(colorizer.hue + dHue * i, 1.0, 1.0, 1.0);
        }
    }
};

struct KeyColorizer {
    std::string key;
    Color color;
};

struct KeyColorizerSystem : System<const Input, const KeyColorizer, Mesh> {
    
    void Update(const Input& input, const KeyColorizer& colorizer, Mesh& mesh) {
        if (std::find_if(input.keysDown.begin(), input.keysDown.end(), [&colorizer] (auto& k) { return colorizer.key == k.key; }) != input.keysDown.end())  {
        //if (input.keysDown.size()>0) {
            for (int i=0; i<mesh.vertices.size(); ++i) {
                mesh.vertices[i].Color = colorizer.color;
            }
        } else {
            for (int i=0; i<mesh.vertices.size(); ++i) {
                mesh.vertices[i].Color = Color(1.0f,1.0f,1.0f,1.0f);
            }
        }
        
    }
    
};


struct State : IState {
    using ComponentTypes = ComponentTypes<
        WorldBoundingBox, LocalBoundingBox, WorldTransform, Camera, Mesh, LocalTransform, Hierarchy,
        Input, Pickable, Draggable, Rotator, QuadMesh, Sizeable, Collider, Colorizer,
        KeyColorizer
    >;
    using Systems = SystemTypes<
        RenderOctreeSystem, RenderSystem, WorldBoundingBoxSystem, HierarchySystem, WorldTransformSystem,
        InputSystem, PickableSystem, DraggableSystem, RotatorSystem, QuadMeshSystem,
        MeshBoundingBoxSystem,
        ColliderOctreeSystem, ColliderSystem,
        ColorizerSystem,
        KeyColorizerSystem
    >;
    
    using Registry = Registry<ComponentTypes>;
    using Scene = Scene<Registry, Systems>;

    Registry registry;
    std::shared_ptr<Scene> scene;
    ivec2 camPos;
    
    void Initialize() override {
        
        scene = std::make_shared<Scene>(registry);
        scene->GetSystem<InputSystem>().SetDevice(device.Input.Device());
        scene->GetSystem<PickableSystem>().screenSize = device.Screen.Size;
        scene->GetSystem<DraggableSystem>().screenSize = device.Screen.Size;
        
        device.Screen.Size.Changed.Bind([this] {
            
            scene->GetSystem<PickableSystem>().screenSize = device.Screen.Size;
            scene->GetSystem<DraggableSystem>().screenSize = device.Screen.Size;
        
        });
        
        
        auto cameraGO = scene->CreateGameObject();
        scene->AddComponent<WorldTransform>(cameraGO, glm::translate(glm::mat4x4(1.0f), glm::vec3(0.0f,0.0f,0.0f)));
        scene->AddComponent<Camera>(cameraGO, glm::vec2(4,4), -0.1f, 10.0f);
        scene->AddComponent<LocalTransform>(cameraGO);
        scene->AddComponent<Hierarchy>(cameraGO);
        scene->AddComponent<Input>(cameraGO);
        
        //scene->AddComponent<Rotator>(cameraGO, -0.5f);
        
        auto quad1 = CreateQuad({0,0,0}, {1.0f,1.0f,1.0f}, false);
        //scene->GetComponent<LocalTransform>(quad1).rotation = sglm::angleAxis(glm::radians(45.0f), vec3(0,0,1));
        
        auto quad2 = CreateQuad({3.0f,0,0}, {1.0f,1.0f,1.0f}, false, quad1);
        
        scene->AddComponent<KeyColorizer>(quad2, "A", Color(1.0f,0.0f,0.0f,1.0f));
        scene->ReferenceComponent<Input>(quad2, cameraGO);
        
       /* device.Input.ButtonDown.Bind([this, quad2](ButtonEvent button) {
            Sizeable& sizeable = scene->GetComponent<Sizeable>(quad2);
            
            if (button.Id == "A") {
                sizeable.size += vec3(0.5f,0.0f,0.0f);
            }
           
        });
        */
        
        Shader<Vertex>* shader = new Shader<Vertex>();
        
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
        scene->GetSystem<RenderSystem>().shader = shader;
        
        
        VertexRenderer<Vertex>* vertexRenderer = new VertexRenderer<Vertex>();
        
        scene->GetSystem<RenderSystem>().vertexRenderer = vertexRenderer;
        
    }
    
    GameObject CreateQuad(const glm::vec3& pos, const glm::vec3& scale, bool rotate, GameObject parent = GameObjectNull) {
        
        auto quadGO = scene->CreateGameObject();
        
        LocalTransform local;
        local.position = pos;
        local.scale = scale;
        
        scene->AddComponent<LocalTransform>(quadGO, local);
        scene->AddComponent<WorldTransform>(quadGO);
        scene->AddComponent<Hierarchy>(quadGO);
        scene->AddComponent<Mesh>(quadGO);
        scene->AddComponent<QuadMesh>(quadGO);
        scene->AddComponent<Sizeable>(quadGO, vec3(1,1,0));
        
        scene->GetComponent<Hierarchy>(quadGO).parent = parent;
        
        scene->AddComponent<LocalBoundingBox>(quadGO);
        scene->AddComponent<WorldBoundingBox>(quadGO);
        
        scene->AddComponent<Pickable>(quadGO);
        scene->AddComponent<Draggable>(quadGO);
        scene->AddComponent<Collider>(quadGO);
        
        //scene->AddComponent<Colorizer>(quadGO, 0.0f, 1.0f);
        
        if (rotate) {
            scene->AddComponent<Rotator>(quadGO, 1.0f);
        }

        return quadGO;
    }
    
    
    void Update(float dt) override {
        scene->Update();
        auto mousePos = device.Input.GetTouchPosition(0);
        
        glm::vec2 screenSize = {device.Screen.Size().x, device.Screen.Size().y};
        glm::vec2 mPos = {mousePos.x, mousePos.y};
        
        //vec2 pos =((screenSize * 0.5f - mPos) - screenSize*0.5f) * 0.01f;
        
        //vec2 pos = mPos * 0.005f;
        //scene->GetComponent<LocalTransform>(0).position = vec3(pos,0);
        
        std::cout <<"fps: " << 1.0f / dt<< "\n";
        
        registry.ResetChanged();
    }
    
    void Render() override {
        glClearColor(100/255.0f, 149/255.0f, 237/255.0f, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        Timer timer;
        timer.Start();
        scene->GetSystem<RenderSystem>().RenderScene();
        //std::cout << "Rendering :  " << timer.Stop() * 1000.0f<<"\n";
        
    }
};



int main() {
    Engine e;
    e.Start<State>();
    return 0;
}
