//
// Created by Jeppe Nielsen on 30/12/2021.
//

#include "WindowContainerSystem.hpp"

using namespace Tiny;
using namespace TinyEditor;

void TinyEditor::WindowContainerSystem::Update(Tiny::GameObject gameObject,
                                               const WindowContainer &windowContainer,
                                               const Sizeable &sizeable, const Hierarchy &hierarchy,
                                               LocalTransform &localTransform) {


    for (auto child : hierarchy.children) {
        GetComponents(child, [] (Sizeable& sizeable, LocalTransform& localTransform) {

        });
    }

}
