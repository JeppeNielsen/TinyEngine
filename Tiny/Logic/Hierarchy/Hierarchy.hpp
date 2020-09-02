//
//  Hierarchy.hpp
//  Tiny
//
//  Created by Jeppe Nielsen on 25/02/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include "GameObject.hpp"
#include <vector>

namespace Tiny {
    struct Hierarchy {
        Tiny::GameObject parent = Tiny::GameObjectNull;
        Tiny::GameObject previousParent = Tiny::GameObjectNull;
        std::vector<Tiny::GameObject> children;
    };
}
