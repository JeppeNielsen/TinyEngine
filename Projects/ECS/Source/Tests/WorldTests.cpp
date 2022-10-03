//
//  WorldTests.cpp
//  ECS
//
//  Created by Jeppe Nielsen on 01/10/2022.
//

#include "gtest/gtest.h"
#include "World.hpp"

using namespace Tiny;

namespace {

struct Transform {
    int x = 0;
    int y = 0;
};

struct Velocity {
    int vx;
    int vy;
};

struct RotateSystem {
    void Step(Transform& transform) {
        
    }
};

struct VelocitySystem {
    void Step(Transform& transform, const Velocity& velocity) {
        transform.x += velocity.vx;
        transform.y += velocity.vy;
    }
};

using Archetypes = ArchetypeCollection<ArchetypeContainer<Transform>, ArchetypeContainer<Transform, Velocity>>;

using Registry = Registry<Archetypes>;

using Systems = SystemCollection<Archetypes, RotateSystem, VelocitySystem>;

TEST(World, Step) {
    
    Registry registry;
    World<Registry, Systems> world(registry);
    
    auto pivot = registry.CreateGameObject(0);
    auto bullet = registry.CreateGameObject(1);
    
    auto& components = registry.GetComponents<1>(bullet);
    std::get<1>(components).vx = 1;
    
    
    EXPECT_EQ(std::get<0>(components).x, 0);
    world.Step();
    EXPECT_EQ(std::get<0>(components).x, 1);
}


}

