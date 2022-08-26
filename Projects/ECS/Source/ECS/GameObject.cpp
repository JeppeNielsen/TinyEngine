//
//  GameObject.cpp
//  ECS
//
//  Created by Jeppe Nielsen on 26/08/2022.
//

#include "GameObject.hpp"

using namespace Tiny;

GameObject::GameObject(uint64_t value) : value(value) {}
GameObject::GameObject(uint32_t index, uint32_t version, uint32_t type) {
    value = index << indexOffset | (uint64_t)version << versionOffset | (uint64_t)type << typeOffset;
}

uint32_t GameObject::Index() const {
    return value & indexMask;
}

uint32_t GameObject::Version() const {
    return (value & versionMask) >> versionOffset;
}

uint32_t GameObject::Type() const {
    return (value & typeMask) >> typeOffset;
}

bool GameObject::operator==(const GameObject& other) const {
    return value == other.value;
}

bool GameObject::operator!=(const GameObject& other) const {
    return value != other.value;
}
