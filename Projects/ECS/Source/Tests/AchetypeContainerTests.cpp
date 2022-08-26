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
    struct Renderable {
        int imageNo;
    };
    ArchetypeContainer<int> container;
    container.Create(0);
    EXPECT_EQ(container.components.size(), 1);
}

TEST(ArchetypeContainer, CreateElement) {
    const int EXPECTED_VALUE = 123;
    
    struct Renderable {
        int imageNo = EXPECTED_VALUE;
    };
    ArchetypeContainer<Renderable> container;
    container.Create(0);
    EXPECT_EQ(std::get<0>(container.components[0]).imageNo, EXPECTED_VALUE);
}

}
