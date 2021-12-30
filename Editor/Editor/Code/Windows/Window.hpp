//
//  Window.hpp
//  TinyEditor
//
//  Created by Jeppe Nielsen on 17/09/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include "Math.hpp"

namespace TinyEditor {
    class Window {
    public:
        bool updateFromOS = false;
        ivec2 osPosition;
        ivec2 osSize;
        vec3 color;
    };
}


