#include <vector>
#include "Scene.hpp"
#include "SystemDependencies.hpp"

using namespace Tiny;

struct Vec2 {
    float x;
    float y;
};

struct Position {
    float x;
    float y;
};

struct Velocity {
    float x;
    float y;
};

struct VelocitySystem : System<Position, const Velocity> {
  
    void Update(Position& position, const Velocity& velocity) {
        position.x += velocity.x;
        position.y += velocity.y;
        
        std::cout<<"VelocitySystem : x: "<< position.x << ", y: "<<position.y << std::endl;
    }

};

struct PositionSystem : System<Position>, SystemDependencies<VelocitySystem> {
    
    
    void Initialize(VelocitySystem& vel) {
        
    }
  
    void Update(Position& position) {
        position.x += 1;
        position.y += 10;
        
        std::cout<<"PositionSystem : x: "<< position.x << ", y: "<<position.y << std::endl;
    
    }

};


struct AccSystem : System<Velocity> {
    
    void Initialize(PositionSystem& system) {
        
    }
    
    void Update(Velocity& vel) {
        vel.x = 0;
        vel.y = 0;
        
        std::cout<<"AccSystem : x: "<< vel.x << ", y: "<<vel.y << std::endl;
    
  
    }
    
};

