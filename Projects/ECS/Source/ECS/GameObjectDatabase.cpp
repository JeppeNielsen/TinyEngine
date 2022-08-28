//
//  GameObjectDatabase.cpp
//  Tiny
//
//  Created by Jeppe Nielsen on 08/10/2019.
//  Copyright © 2019 Jeppe Nielsen. All rights reserved.
//

#include "GameObjectDatabase.hpp"

using namespace Tiny;

GameObjectDatabase::GameObjectDatabase(std::uint32_t typeIndex) : typeIndex(typeIndex) {}

bool GameObjectDatabase::IsValid(const GameObject gameObject) const {
    const auto pos = gameObject.Index();
    return (pos < objects.size() && objects[pos] == gameObject);
}

GameObject GameObjectDatabase::Create() {
    GameObject object;

    if(available) {
        const auto objectIndex = next;
        const auto version = objects[objectIndex].Version();
        object = GameObject(objectIndex, version, typeIndex);
        next = objects[objectIndex].Index();
        objects[objectIndex] = object;
        --available;
    } else {
        object = GameObject(objects.size(), 0, typeIndex);
        objects.push_back(object);
    }
    return object;
}

void GameObjectDatabase::Remove(const GameObject gameObject) {
    const auto objectIndex = gameObject.Index();
    const auto version = gameObject.Version() + 1;
    const auto node = GameObject(available ? next : objectIndex + 1, version, typeIndex);
    
    objects[objectIndex] = node;
    next = objectIndex;
    ++available;
}

size_t GameObjectDatabase::Size() const {
    return objects.size();
}
