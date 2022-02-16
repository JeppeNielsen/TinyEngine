//
// Created by Jeppe Nielsen on 30/12/2021.
//

#pragma once
#include "ECS.hpp"
#include "WindowContainer.hpp"
#include "Window.hpp"
#include "Sizeable.hpp"
#include "Hierarchy.hpp"
#include "LocalTransform.hpp"

namespace TinyEditor {
    class WindowContainerSystem : Tiny::SystemChangedGameObject<const WindowContainer, const Tiny::Sizeable, const Tiny::Hierarchy, Tiny::LocalTransform>,
                                  Tiny::ComponentView<Tiny::Sizeable, Tiny::LocalTransform> {

        void Update(Tiny::GameObject gameObject, const WindowContainer& windowContainer, const Tiny::Sizeable& sizeable, const Tiny::Hierarchy& hierarchy, Tiny::LocalTransform& localTransform);

    };
}

