//
//  GameObject.hpp
//  ECS
//
//  Created by Jeppe Nielsen on 26/08/2022.
//

#pragma once
#include <cstdlib>

namespace Tiny {

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
    GameObject(uint64_t value);
    GameObject(uint32_t index, uint32_t version, uint32_t type);

    uint32_t Index() const;
    
    uint32_t Version() const;
    
    uint32_t Type() const;
    
    bool operator==(const GameObject& other) const;
    
    bool operator!=(const GameObject& other) const;
};

}
