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
    container.Create(0);
    EXPECT_EQ(container.components.size(), 1);
}

TEST(ArchetypeContainer, Create) {
    const int EXPECTED_VALUE = 123;
    
    struct Renderable {
        int imageNo = EXPECTED_VALUE;
    };
    ArchetypeContainer<Renderable> container;
    container.Create(0);
    EXPECT_EQ(std::get<0>(container.components[0]).imageNo, EXPECTED_VALUE);
}

TEST(ArchetypeContainer, Create_GameObject_Returned) {
    const auto EXPECTED_VALUE = GameObject(0, 0, 0);
    ArchetypeContainer<int> container;
    auto gameObject = container.Create(0);
    EXPECT_EQ(gameObject, EXPECTED_VALUE);
}

TEST(ArchetypeContainer, Create_GameObject_Returned_Run_TWICE) {
    const auto EXPECTED_VALUE = GameObject(1, 0, 0);
    ArchetypeContainer<int> container;
    container.Create(0);
    auto gameObject2 = container.Create(0);
    EXPECT_EQ(gameObject2, EXPECTED_VALUE);
}

TEST(ArchetypeContainer, Remove) {
    const int EXPECTED_VALUE = 123;
    struct Renderable {
        int imageNo = EXPECTED_VALUE;
    };
    ArchetypeContainer<Renderable> container;
    auto createdObject = container.Create(0);
    EXPECT_EQ(container.components.size(), 1);
    container.Remove(createdObject);
    EXPECT_EQ(container.components.size(), 0);
}

}
