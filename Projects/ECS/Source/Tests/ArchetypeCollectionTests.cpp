//
//  ArchetypeCollectionTests.cpp
//  ECS
//
//  Created by Jeppe Nielsen on 26/08/2022.
//

#include "gtest/gtest.h"
#include "ArchetypeCollection.hpp"
#include "ArchetypeContainer.hpp"

using namespace Tiny;

namespace {

struct Transform {
    int x;
    int y;
};

struct Renderable {
    int imageNo;
};

using TransformContainer = ArchetypeContainer<Transform>;
using TransformRenderableContainer = ArchetypeContainer<Transform, Renderable>;

TEST(ArchetypeCollection, Size) {
    ArchetypeCollection<TransformContainer, TransformRenderableContainer> collection;
    EXPECT_EQ(collection.Size, 2);
}

TEST(ArchetypeCollection, GetArcheTypesMatchesTuple) {
    ArchetypeCollection<TransformContainer, TransformRenderableContainer> collection;
    
    struct TransformSystem {
        void Step(Transform& t) {}
    };
    
    struct RenderSystem {
        void Step(Transform& t, Renderable& r) {}
    };
    
    struct NoneSystem {
        void Step(int bla) {}
    };
    
    auto systemsMatchingTransformSystem = collection.GetArcheTypesMatchesTuple<TransformSystem>();
    EXPECT_EQ(std::tuple_size_v<decltype(systemsMatchingTransformSystem)>, 2);
    
    auto systemsMatchingRendererSystem = collection.GetArcheTypesMatchesTuple<RenderSystem>();
    EXPECT_EQ(std::tuple_size_v<decltype(systemsMatchingRendererSystem)>, 1);
    
    auto systemsMatchingNoneSystem = collection.GetArcheTypesMatchesTuple<NoneSystem>();
    EXPECT_EQ(std::tuple_size_v<decltype(systemsMatchingNoneSystem)>, 0);
    
}

TEST(ArchetypeCollection, GetArcheTypesMatchesTuple_ConstParameter) {
    ArchetypeCollection<TransformContainer, TransformRenderableContainer> collection;
    
    struct TransformSystem {
        void Step(const Transform& t) {}
    };
    
    auto systemsMatchingTransformSystem = collection.GetArcheTypesMatchesTuple<TransformSystem>();
    EXPECT_EQ(std::tuple_size_v<decltype(systemsMatchingTransformSystem)>, 2);
}

}
