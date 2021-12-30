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

using namespace Tiny;

struct State : IState {
    using ComponentTypes = ComponentTypes<
        WorldBoundingBox, LocalBoundingBox, WorldTransform, Camera, Mesh, LocalTransform, Hierarchy, Pickable, Input, Draggable
    >;
    using Systems = SystemTypes<
        RenderOctreeSystem, RenderSystem, WorldBoundingBoxSystem, HierarchySystem, WorldTransformSystem, PickableSystem, InputSystem, DraggableSystem
    >;
    
    using Registry = Registry<ComponentTypes>;
    using Scene = Scene<Registry, Systems>;

    Registry registry;
    std::shared_ptr<Scene> scene;
    GameObject meshObject;
    Shader<Vertex> shader;
    VertexRenderer<Vertex>* vertexRenderer;
    
    void Initialize() override {
        
        vertexRenderer = new VertexRenderer<Vertex>();
        
        shader.Load(
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
        
        scene = std::make_shared<Scene>(registry);
        scene->GetSystem<InputSystem>().SetDevice(device.Input.Device());
        scene->GetSystem<PickableSystem>().screenSizeFunction = [this]() { return device.Screen.Size; };
        scene->GetSystem<RenderSystem>().shader = &shader;
        scene->GetSystem<RenderSystem>().vertexRenderer = vertexRenderer;
        scene->GetSystem<DraggableSystem>().screenSizeFunction = [this]() { return device.Screen.Size; };
        
        auto cameraGO = scene->CreateGameObject();
        scene->AddComponent<WorldTransform>(cameraGO);
        scene->AddComponent<Camera>(cameraGO, glm::vec2(5,5), -0.1f, 10.0f);
        scene->AddComponent<LocalTransform>(cameraGO);
        scene->GetComponent<LocalTransform>(cameraGO).position = {0,0,0};


        scene->AddComponent<Hierarchy>(cameraGO);
        scene->AddComponent<Input>(cameraGO);


        meshObject = CreateMesh();
        
/*
        CreateQuad({-5,0,0}, {0.03f,10.0f,1.0f}, false);
        CreateQuad({5,0,0}, {0.03f,10.0f,1.0f}, false);
        CreateQuad({0,-5,0}, {10.0f,0.03f,1.0f}, false);
        CreateQuad({0,5,0}, {10,0.03f,1.0f}, false);
*/
        CreateQuad({0,0,0}, {2,2,1}, false);
    }
    
    GameObject CreateMesh() {
        auto quadGO = scene->CreateGameObject();
        scene->AddComponent<Mesh>(quadGO);
        auto& mesh = scene->GetComponent<Mesh>(quadGO);
        
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

        //scene->AddComponent<Colorizer>(quadGO, 1.0f, 2.0f);
        
        return quadGO;
    }
    
    GameObject CreateQuad(const glm::vec3& pos, const glm::vec3& scale, bool rotate, GameObject parent = GameObjectNull) {
        
        auto quadGO = scene->CreateGameObject();
        
        LocalTransform local;
        local.position = pos;
        local.scale = scale;
        
        scene->AddComponent<LocalTransform>(quadGO, local);
        scene->AddComponent<WorldTransform>(quadGO);
        scene->AddComponent<Hierarchy>(quadGO);
        scene->ReferenceComponent<Mesh>(quadGO, meshObject);
        
        scene->GetComponent<Hierarchy>(quadGO).parent = parent;
        
        BoundingBox boundingBox;
        boundingBox.center = {0,0,0};
        boundingBox.extends = {0.5f,0.5f,0.5f};
        
        scene->AddComponent<LocalBoundingBox>(quadGO, boundingBox);
        scene->AddComponent<WorldBoundingBox>(quadGO);

        scene->AddComponent<Pickable>(quadGO);
        scene->AddComponent<Draggable>(quadGO);

        return quadGO;
    }
    
    
    void Update(float dt) override {
        scene->Update();
        registry.ResetChanged();

        auto mousePos = device.Input.GetTouchPosition(0);

        glm::vec2 screenSize = {device.Screen.Size().x, device.Screen.Size().y};
        glm::vec2 mPos = {mousePos.x, mousePos.y};

        //vec2 pos =((screenSize * 0.5f - mPos) - screenSize*0.5f) * 0.01f;

        vec2 pos = mPos * 0.005f;
        //scene->GetComponent<LocalTransform>(0).position = vec3(pos,0);


        //std::cout << pos.x << "," << pos.y << std::endl;

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
