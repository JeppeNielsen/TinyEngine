//
//  GameObjectTests.cpp
//  ECS
//
//  Created by Jeppe Nielsen on 26/08/2022.
//

#include "gtest/gtest.h"
#include "GameObject.hpp"

using namespace Tiny;

namespace {

TEST(GameObject, Index) {
    const int EXPECTED_INDEX = 342;
    GameObject gameOject(EXPECTED_INDEX, 0, 0);
    EXPECT_EQ(gameOject.Index(), EXPECTED_INDEX);
}

TEST(GameObject, Version) {
    const int EXPECTED_VERSION = 123;
    GameObject gameOject(0, EXPECTED_VERSION, 0);
    EXPECT_EQ(gameOject.Version(), EXPECTED_VERSION);
}

TEST(GameObject, Type) {
    const int EXPECTED_TYPE = 567;
    GameObject gameOject(0, 0, EXPECTED_TYPE);
    EXPECT_EQ(gameOject.Type(), EXPECTED_TYPE);
}

}
