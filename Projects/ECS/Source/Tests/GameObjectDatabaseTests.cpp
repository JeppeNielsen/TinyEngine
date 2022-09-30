//
//  GameObjectTests.cpp
//  ECS
//
//  Created by Jeppe Nielsen on 26/08/2022.
//

#include "gtest/gtest.h"
#include "GameObjectDatabase.hpp"

using namespace Tiny;

namespace {

TEST(GameObjectDatabase, Create) {
    const auto EXPECTED = GameObject(0, 0, 0);
    
    GameObjectDatabase database;
    GameObject go = database.Create();
    EXPECT_EQ(go, EXPECTED);
}

TEST(GameObjectDatabase, Create_Called_Twice) {
    const auto EXPECTED1 = GameObject(0, 0, 0);
    const auto EXPECTED2 = GameObject(1, 0, 0);
    
    GameObjectDatabase database;
    GameObject go1 = database.Create();
    EXPECT_EQ(go1, EXPECTED1);
    GameObject go2 = database.Create();
    EXPECT_EQ(go2, EXPECTED2);
}

TEST(GameObjectDatabase, Remove_Not_Valid) {
    GameObjectDatabase database;
    GameObject go = database.Create();
    database.Remove(go);
    EXPECT_FALSE(database.IsValid(go));
}

TEST(GameObjectDatabase, Remove_And_Recreate) {
    GameObjectDatabase database;
    GameObject go1 = database.Create();
    database.Remove(go1);
    GameObject go2 = database.Create();
    EXPECT_TRUE(database.IsValid(go2));
}

TEST(GameObjectDatabase, Remove_And_Recreate_NotSameHandle) {
    GameObjectDatabase database;
    GameObject go1 = database.Create();
    database.Remove(go1);
    GameObject go2 = database.Create();
    EXPECT_NE(go1, go2);
}

TEST(GameObjectDatabase, Remove_And_Recreate_Version_Different) {
    GameObjectDatabase database;
    GameObject go1 = database.Create();
    database.Remove(go1);
    GameObject go2 = database.Create();
    EXPECT_NE(go1.Version(), go2.Version());
}

TEST(GameObjectDatabase, Removal_OF_Two_And_Recreated_IndexEq_VersionNe) {
    GameObjectDatabase database;
    GameObject go1 = database.Create();
    GameObject go2 = database.Create();
    
    database.Remove(go1);
    database.Remove(go2);
    
    GameObject go4 = database.Create();
    GameObject go3 = database.Create();
    
    EXPECT_EQ(go1.Index(), go3.Index());
    EXPECT_EQ(go2.Index(), go4.Index());
    EXPECT_NE(go1.Version(), go3.Version());
    EXPECT_NE(go2.Version(), go4.Version());
}

TEST(GameObjectDatabase, SetTypeIndex) {
    const int EXPECTED_TYPEINDEX = 54;
    
    GameObjectDatabase database;
    database.SetTypeIndex(EXPECTED_TYPEINDEX);
    GameObject go = database.Create();
    
    EXPECT_EQ(go.Type(), EXPECTED_TYPEINDEX);
}

}
