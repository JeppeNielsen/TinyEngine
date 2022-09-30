//
//  EntityCollection.hpp
//  Tiny
//
//  Created by Jeppe Nielsen on 08/10/2019.
//  Copyright © 2019 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include <vector>
#include "GameObject.hpp"

namespace Tiny {

class GameObjectCollection {
public:
    
    using Objects = std::vector<GameObject>;
    using Indicies = std::vector<std::uint32_t>;

    void Add(const GameObject object);
    void Remove(const GameObject object);
    bool Contains(const GameObject object) const;
    std::size_t Get(const GameObject object) const;
    void Clear();
    GameObject Last();

    Indicies indicies;
    Objects objects;
};
    
}
