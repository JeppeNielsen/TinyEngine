//
//  MeshBoundingBoxSystem.hpp
//  TinyOSX
//
//  Created by Jeppe Nielsen on 24/09/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//


#pragma once
#include "ECS.hpp"
#include "Mesh.hpp"
#include "LocalBoundingBox.hpp"

namespace Tiny {
    struct MeshBoundingBoxSystem : SystemChanged<const Mesh, LocalBoundingBox> {
    
        void Changed(const Mesh& mesh, LocalBoundingBox& localBoundingBox);
        
        void Update(const Mesh& mesh, LocalBoundingBox& localBoundingBox);
    };
}
