//
//  TestGameObjectDatabase.cpp
//  Tiny
//
//  Created by Jeppe Nielsen on 01/11/2019.
//  Copyright © 2019 Jeppe Nielsen. All rights reserved.
//
#include "gtest/gtest.h"
#include "GameObjectDatabase.hpp"

using namespace Tiny;

namespace {

    TEST(GameObjectDatabase, Create) {
        GameObjectDatabase database;
        auto object = database.Create();
        EXPECT_TRUE(database.IsValid(object));
    }

}
