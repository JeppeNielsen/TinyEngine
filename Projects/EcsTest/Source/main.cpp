

#include <iostream>

#include "ECS.hpp"

struct Position {
    float x = 0;
    float y = 0;
};

struct Velocity {
    float vx = 1;
    float vy = 2;
};

struct VelocitySystem : Tiny::System<const Velocity, Position> {

    void Update(const Velocity& velocity, Position& position) {
        position.x += velocity.vx;
        position.y += velocity.vy;
    }

};

using Components = Tiny::ComponentTypes<Position, Velocity>;
using Systems = Tiny::SystemTypes<VelocitySystem>;

using Registry = Tiny::Registry<Components>;
using Scene = Tiny::Scene<Registry, Systems>;

int main() {

    Registry registry;
    Scene scene(registry);

    auto go1 = scene.CreateGameObject();
    scene.AddComponent<Position>(go1);
    scene.AddComponent<Velocity>(go1);

    scene.Update();

    scene.RemoveGameObject(234);

    scene.Update();

    auto pos = scene.GetComponent<Position>(go1);

    std::cout << "pos.x = "<< pos.x << " pos.y = " << pos.y << std::endl;

    std::cout << "Hello world" << std::endl;

	return 0;
}