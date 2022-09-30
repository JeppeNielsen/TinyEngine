//
//  GameObjectTests.cpp
//  ECS
//
//  Created by Jeppe Nielsen on 26/08/2022.
//

#include "gtest/gtest.h"
#include "GameObjectCollection.hpp"

using namespace Tiny;

namespace {

TEST(GameObjectCollection, Add) {
    const GameObject go(0,0,0);
    GameObjectCollection collection;
    collection.Add(go);
    EXPECT_EQ(collection.objects.size(), 1);
}

TEST(GameObjectCollection, Remove) {
    const GameObject go(0,0,0);
    GameObjectCollection collection;
    collection.Add(go);
    collection.Remove(go);
    EXPECT_EQ(collection.objects.size(), 0);
}

TEST(GameObjectCollection, Contains) {
    const GameObject go(0,0,0);
    GameObjectCollection collection;
    collection.Add(go);
    EXPECT_TRUE(collection.Contains(go));
}

TEST(GameObjectCollection, NotContainsRemovedObject) {
    const GameObject go(0,0,0);
    GameObjectCollection collection;
    collection.Add(go);
    collection.Remove(go);
    EXPECT_FALSE(collection.Contains(go));
}

TEST(GameObjectCollection, Get) {
    const GameObject go1(0,0,0);
    const GameObject go2(1,0,0);
    GameObjectCollection collection;
    collection.Add(go1);
    collection.Add(go2);
    EXPECT_EQ(collection.Get(go1), 0);
    EXPECT_EQ(collection.Get(go2), 1);
}

TEST(GameObjectCollection, Get2) {
    const GameObject go1(0,0,0);
    const GameObject go2(1,0,0);
    const GameObject go3(2,0,0);
    
    GameObjectCollection collection;
    collection.Add(go1);
    collection.Add(go2);
    collection.Add(go3);
    
    collection.Remove(go2);
    
    EXPECT_EQ(collection.Get(go1), 0);
    EXPECT_EQ(collection.Get(go3), 1);
}

TEST(GameObjectCollection, Last) {
    const GameObject go(4,0,0);
    GameObjectCollection collection;
    collection.Add(go);
    EXPECT_EQ(go, collection.Last());
}

}
