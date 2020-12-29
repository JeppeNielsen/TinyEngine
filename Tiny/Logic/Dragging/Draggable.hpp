//
//  Draggable.hpp
//  TinyEditor
//
//  Created by Jeppe Nielsen on 23/09/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include "Math.hpp"
#include "Pickable.hpp"
#include "Plane.hpp"

namespace Tiny {
    struct Draggable {
        PickEvent dragEvent;
        Plane originPlane;
        vec3 offset;
        bool isDragging = false;
    };
}
