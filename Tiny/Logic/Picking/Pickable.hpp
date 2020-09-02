//
//  Pickable.hpp
//  Tiny
//
//  Created by Jeppe Nielsen on 21/08/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include "Input.hpp"
#include "GameObject.hpp"

namespace Tiny {

    struct PickEvent {
        
        GameObject object;
        TouchPosition touchPosition;
        InputTouch touch;
        vec3 worldPosition;
        
    };

    using PickeEventCollection = std::vector<PickEvent>;

    struct Pickable {
        PickeEventCollection down;
        PickeEventCollection up;
        PickeEventCollection clicked;
    };
}
