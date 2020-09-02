//
//  Transform.hpp
//  Tiny
//
//  Created by Jeppe Nielsen on 19/02/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include "Math.hpp"

namespace Tiny {
    struct LocalTransform {
        LocalTransform();
        glm::vec3 position;
        glm::quat rotation;
        glm::vec3 scale;
    };
}
