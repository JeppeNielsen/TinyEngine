//
//  AchetypeContainerTest.cpp
//  ECS
//
//  Created by Jeppe Nielsen on 26/08/2022.
//

#include "gtest/gtest.h"
#include "ArchetypeContainer.hpp"

using namespace Tiny;

namespace {

TEST(ArchetypeContainer, CreateContainsOne) {
    ArchetypeContainer<int> container;
    container.Create();
    EXPECT_EQ(container.components.size(), 1);
}

TEST(ArchetypeContainer, Create) {
    const int EXPECTED_VALUE = 123;
    
    struct Renderable {
        int imageNo = EXPECTED_VALUE;
    };
    ArchetypeContainer<Renderable> container;
    container.Create();
    EXPECT_EQ(std::get<0>(container.components[0]).imageNo, EXPECTED_VALUE);
}

TEST(ArchetypeContainer, Create_GameObject_Returned) {
    const auto EXPECTED_VALUE = GameObject(0, 0, 0);
    ArchetypeContainer<int> container;
    auto gameObject = container.Create();
    EXPECT_EQ(gameObject, EXPECTED_VALUE);
}

TEST(ArchetypeContainer, Create_GameObject_Returned_Run_TWICE) {
    const auto EXPECTED_VALUE = GameObject(1, 0, 0);
    ArchetypeContainer<int> container;
    container.Create();
    auto gameObject2 = container.Create();
    EXPECT_EQ(gameObject2, EXPECTED_VALUE);
}

TEST(ArchetypeContainer, Remove) {
    struct Renderable {
        int imageNo;
    };
    ArchetypeContainer<Renderable> container;
    auto createdObject = container.Create();
    EXPECT_EQ(container.components.size(), 1);
    container.Remove(createdObject);
    EXPECT_EQ(container.components.size(), 0);
}

TEST(ArchetypeContainer, Remove2) {
    const int EXPECTED_VALUE = 2;
    struct Renderable {
        int imageNo;
    };
    ArchetypeContainer<Renderable> container;
    auto go1 = container.Create();
    auto go2 = container.Create();
    
    std::get<0>(container.GetComponents(go1)).imageNo = 1;
    std::get<0>(container.GetComponents(go2)).imageNo = EXPECTED_VALUE;
    
    container.Remove(go1);
    
    auto& components = container.GetComponents(go2);
    
    EXPECT_EQ(std::get<0>(components).imageNo, EXPECTED_VALUE);
}

TEST(ArchetypeContainer, SetType) {
    const auto EXPECTED_TYPE_INDEX = 2;
    const auto EXPECTED_GAMEOBJECT = GameObject(0, 0, EXPECTED_TYPE_INDEX);
   
    ArchetypeContainer<int> container;
    container.SetTypeIndex(EXPECTED_TYPE_INDEX);
    auto createdObject = container.Create();
    
    EXPECT_EQ(createdObject, EXPECTED_GAMEOBJECT);
}

TEST(ArchetypeContainer, MultpleComponents) {
    
    const auto EXPECTED_IMAGE_NO = 2;
    const auto EXPECTED_X = 123;
    const auto EXPECTED_Y = 456;
    
    struct Renderable {
        int imageNo = EXPECTED_IMAGE_NO;
    };
    
    struct Transform {
        int x = EXPECTED_X;
        int y = EXPECTED_Y;
    };
    
    ArchetypeContainer<Renderable, Transform> container;
    auto createdObject = container.Create();
    
    EXPECT_EQ(std::get<0>(container.GetComponents(createdObject)).imageNo, EXPECTED_IMAGE_NO);
    EXPECT_EQ(std::get<1>(container.GetComponents(createdObject)).x, EXPECTED_X);
    EXPECT_EQ(std::get<1>(container.GetComponents(createdObject)).y, EXPECTED_Y);
}

TEST(ArchetypeContainer, Invoke) {
    struct Renderable {
        int imageNo = 0;
    };
    
    ArchetypeContainer<Renderable> container;
    container.Create();
    
    static bool wasInvoked = false;
    
    struct System {
        void Update(const Renderable& rendable) {
            wasInvoked = true;
        }
    };
    
    System system;
    
    wasInvoked = false;
    container.Invoke(&System::Update, &system);
    
    EXPECT_TRUE(wasInvoked);
    
}

template<typename T>
struct Reference {
    T val;
    constexpr operator T&() { return val; }
    constexpr operator T() const { return val; }
};

TEST(ArchetypeContainer, ReferenceComponent) {
    
    const int EXPECTED_VALUE = 123;
    
    struct Renderable {
        int meshId;
    };
    
    static int receivedValue = 0;
    
    struct RenderSystem {
        void Step(Renderable& r) {
            receivedValue = r.meshId;
        }
    };
    
    
    ArchetypeContainer<Renderable> assetContainer;
    ArchetypeContainer<ReferenceComponent<Renderable>> worldContainer;
    
    auto asset = assetContainer.Create();
    auto instance = worldContainer.Create();
    std::get<ReferenceComponent<Renderable>>(worldContainer.GetComponents(instance)).value.meshId = EXPECTED_VALUE;
    
    RenderSystem renderSystem;
    
    worldContainer.Invoke(&RenderSystem::Step, &renderSystem);
    
    
    EXPECT_EQ(EXPECTED_VALUE, receivedValue);
}



}
