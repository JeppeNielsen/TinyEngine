//
//  Transform.cpp
//  Tiny
//
//  Created by Jeppe Nielsen on 19/02/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#include "LocalTransform.hpp"
#include <glm/gtx/quaternion.hpp>

using namespace Tiny;

LocalTransform::LocalTransform() : position({0.0f,0.0f,0.0f}), rotation(quat(1.0f,0.0f,0.0f,0.0f)), scale({1.0f,1.0f,1.0f}) {
    
}

mat4 LocalTransform::GetLocalToParent() const {
    return glm::scale(glm::translate(mat4x4(1.0f), position), scale) * glm::toMat4(rotation);
}
