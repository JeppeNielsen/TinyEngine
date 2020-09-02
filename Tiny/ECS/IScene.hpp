//
//  IScene.hpp
//  Tiny
//
//  Created by Jeppe Nielsen on 03/03/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include "GameObject.hpp"

namespace Tiny {
    struct IScene {
        virtual GameObject CreateGameObject() = 0;
        virtual void RemoveGameObject(const GameObject gameObject) = 0;
        virtual bool IsGameObjectRemoved(const GameObject gameObject) const = 0;
    };
}
