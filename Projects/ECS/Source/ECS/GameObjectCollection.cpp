//
//  EntityCollection.cpp
//  Tiny
//
//  Created by Jeppe Nielsen on 08/10/2019.
//  Copyright © 2019 Jeppe Nielsen. All rights reserved.
//

#include "GameObjectCollection.hpp"
#include <assert.h>

using namespace Tiny;

const auto NullIndex = std::numeric_limits<std::uint32_t>::max();

GameObjectCollection::GameObjectCollection(std::uint32_t typeIndex) : typeIndex(typeIndex) {}

void GameObjectCollection::Add(const GameObject object) {
    assert(!Contains(object));
    const auto objectIndex = object.Index();
    if (objectIndex>=indicies.size()) {
        indicies.resize(objectIndex + 1, NullIndex);
    }
    indicies[objectIndex] = objects.size();
    objects.emplace_back(object);
}

void GameObjectCollection::Remove(const GameObject object) {
    assert(Contains(object));
    const auto objectIndex = object.Index();
    const auto last = objects.back();
    const auto lastIndex = last.Index();
    
    const auto indexInObjects = indicies[objectIndex];
    const auto lastIndexInObjects = indicies[lastIndex];
    
    indicies[lastIndex] = indexInObjects;
    indicies[objectIndex] = NullIndex;
    
    objects[indexInObjects] = objects[lastIndexInObjects];
    objects.pop_back();
}

bool GameObjectCollection::Contains(const GameObject object) const {
    const auto index = object.Index();
    return index<indicies.size() && indicies[index] != NullIndex;
}

std::size_t GameObjectCollection::Get(const GameObject object) const {
    return indicies[object.Index()];
}

void GameObjectCollection::Clear() {
    indicies.clear();
    objects.clear();
}

