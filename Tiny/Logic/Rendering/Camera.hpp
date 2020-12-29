//
//  Camera.hpp
//  Tiny
//
//  Created by Jeppe Nielsen on 27/07/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include "Math.hpp"
#include "Ray.hpp"
#include "WorldTransform.hpp"

namespace Tiny {
    struct Camera {
        glm::vec2 ViewSize;
        
        float Near;
        float Far;
        
        mat4x4 GetProjection() const;
     
        Ray GetRay(const WorldTransform &transform,
                   const ivec2& screenSize,
                   const ivec2& screenPosition) const;
        
    };
}
