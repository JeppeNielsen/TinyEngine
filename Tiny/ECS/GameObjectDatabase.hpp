//
//  GameObjectDatabase.hpp
//  Tiny
//
//  Created by Jeppe Nielsen on 08/10/2019.
//  Copyright © 2019 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include <vector>
#include "GameObject.hpp"

namespace Tiny {
    class GameObjectDatabase {
    public:
        bool IsValid(const GameObject gameObject) const;
        GameObject Create();
        void Remove(const GameObject gameObject);
        size_t Size() const;
    private:
        std::vector<GameObject> objects;
        std::size_t available {};
        GameObject next {};
    };
}
