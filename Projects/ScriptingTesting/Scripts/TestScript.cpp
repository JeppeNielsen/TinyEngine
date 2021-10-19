#include <vector>
#include "Scene.hpp"

using namespace Tiny;

struct Position {
    float x;
    float y;
};

struct Velocity {
    float x;
    float y;
};

struct VelocitySystem : Tiny::System<Position, const Velocity> {
  
    void Update(Position& position, const Velocity& velocity) {
        position.x += velocity.x;
        position.y += velocity.y;
    }

};



extern "C" {
    int GetResult() {
        
        using ComponentTypes = ComponentTypes<Position, Velocity>;
        using Registry = Registry<ComponentTypes>;
        using Systems = SystemTypes<VelocitySystem>;
        using Scene = Tiny::Scene<Registry, Systems>;
        
        Registry registry;
        
        Scene scene(registry);
        
        auto go = scene.CreateGameObject();
        
        scene.AddComponent<Position>(go);
        scene.AddComponent<Velocity>(go, 1.0f, -2.0f);
        
        scene.Update();
        scene.Update();
        
        auto position = scene.GetComponent<Position>(go);
        
        return (int)position.y;
        
    }
}
