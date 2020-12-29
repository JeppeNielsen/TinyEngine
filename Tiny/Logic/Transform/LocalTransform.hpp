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
        glm::vec3 position = {0.0f,0.0f,0.0f};
        glm::quat rotation = quat(1.0f,0.0f,0.0f,0.0f);
        glm::vec3 scale = vec3(1.0f,1.0f,1.0f);
        
        mat4 GetLocalToParent() const;
    };
}
