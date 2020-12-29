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
#include "Camera.hpp"
#include "WorldTransform.hpp"

namespace Tiny {

    struct PickEvent {
        
        PickEvent() = default;
        
        PickEvent(const WorldTransform& cameraTransform, const Camera& camera, const Input& input)
            : cameraTransform(&cameraTransform), camera(&camera), input(&input) {
        }
        
        GameObject object;
        TouchPosition touchPosition;
        InputTouch touch;
        vec3 worldPosition;
        vec3 worldNormal;
        const WorldTransform* cameraTransform;
        const Camera* camera;
        const Input* input;
    };

    using PickeEventCollection = std::vector<PickEvent>;

    struct Pickable {
        PickeEventCollection down;
        PickeEventCollection up;
        PickeEventCollection clicked;
    };
}
