//
//  Input.hpp
//  Tiny
//
//  Created by Jeppe Nielsen on 21/08/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include "Math.hpp"
#include <vector>
#include <string>
#include "InputManager.hpp"

namespace Tiny {

    struct TouchPosition {
        ivec2 position;
    };

    struct InputTouch {
        int index;
    };

    using TouchCollection = std::vector<InputTouch>;

    struct InputKey {
        std::string key;
        ModifierKey modifier;
    };

    using KeyCollection = std::vector<InputKey>;

    struct Input {
        TouchPosition touchPosition[10];
        TouchCollection touchesDown;
        TouchCollection touchesUp;
        KeyCollection keysDown;
        KeyCollection keysUp;
    };
}
