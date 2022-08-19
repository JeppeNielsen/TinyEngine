//
//  GameObject.hpp
//  NewEcs
//
//  Created by Jeppe Nielsen on 22/07/2022.
//
#pragma once

class GameObject {
    uint64_t value;

    static constexpr uint64_t indexMask =   0x00000000FFFFFFFF;
    static constexpr uint64_t versionMask = 0x0000FFFF00000000;
    static constexpr uint64_t typeMask =    0xFFFF000000000000;
    static constexpr uint32_t indexOffset   =  0;
    static constexpr uint32_t versionOffset = 32;
    static constexpr uint32_t typeOffset    = 48;
    
public:
    
    GameObject() = default;
    GameObject(uint64_t value) : value(value) {}
    GameObject(uint32_t index, uint32_t version, uint32_t type) {
        value = index << indexOffset | (uint64_t)version << versionOffset | (uint64_t)type << typeOffset;
    }

    uint32_t Index() const {
        return value & indexMask;
    }
    
    uint32_t Version() const {
        return (value & versionMask) >> versionOffset;
    }
    
    uint32_t Type() const {
        return (value & typeMask) >> typeOffset;
    }
    
    bool operator==(const GameObject& other) const {
        return value == other.value;
    }
    
    bool operator!=(const GameObject& other) const {
        return value != other.value;
    }
    
    const static GameObject Null;
};
