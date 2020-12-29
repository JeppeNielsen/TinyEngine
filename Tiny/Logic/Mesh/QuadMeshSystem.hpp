//
//  QuadMeshSystem.hpp
//  TinyEditor
//
//  Created by Jeppe Nielsen on 24/09/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include "ECS.hpp"
#include "QuadMesh.hpp"
#include "Mesh.hpp"
#include "Sizeable.hpp"

namespace Tiny {
    struct QuadMeshSystem : SystemChanged<const QuadMesh, const Sizeable, Mesh> {
    
        void Changed(const QuadMesh& quadMesh,
                    const Sizeable& sizeable,
                     Mesh& mesh);
        
        void Update(const QuadMesh& quadMesh,
                    const Sizeable& sizeable,
                    Mesh& mesh);
    };
}
