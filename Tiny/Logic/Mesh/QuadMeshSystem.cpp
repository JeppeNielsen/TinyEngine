//
//  QuadMeshSystem.cpp
//  TinyEditor
//
//  Created by Jeppe Nielsen on 24/09/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#include "QuadMeshSystem.hpp"


using namespace Tiny;

void QuadMeshSystem::Changed(const QuadMesh &quadMesh, const Sizeable &sizeable, Mesh &mesh) {
    
}

void QuadMeshSystem::Update(const QuadMesh &quadMesh, const Sizeable &sizeable, Mesh &mesh) {
    
    mesh.vertices.clear();
    mesh.triangles.clear();
    
    /*mesh.vertices.push_back({ { 0.0f, 0.0f, 0.0f }, {0,0}, Color(0.0f, 0.0f, 1.0f) });
    mesh.vertices.push_back({ { sizeable.size.x, 0.0f, 0.0f }, {1.0f,0}, Color(0.0f, 0.0f, 1.0f) });
    mesh.vertices.push_back({ { sizeable.size.x, sizeable.size.y, 0.0f }, {1.0f,1.0f}, Color(0.0f, 0.0f, 1.0f) });
    mesh.vertices.push_back({ { 0.0f, sizeable.size.y, 0.0f }, {0,0}, Color(0.0f, 1.0f, 1.0f) });
    */
    
    const float height = 32;
    
    mesh.vertices.push_back({ { 0.0f, sizeable.size.y - height, 0.0f }, {0,0}, Color(0.0f, 0.0f, 1.0f) });
    mesh.vertices.push_back({ { sizeable.size.x, sizeable.size.y - height, 0.0f }, {1.0f,0}, Color(0.0f, 0.0f, 1.0f) });
    mesh.vertices.push_back({ { sizeable.size.x, sizeable.size.y, 0.0f }, {1.0f,1.0f}, Color(0.0f, 0.0f, 1.0f) });
    mesh.vertices.push_back({ { 0.0f, sizeable.size.y, 0.0f }, {0,0}, Color(0.0f, 1.0f, 1.0f) });
    
    
    mesh.triangles.push_back(0);
    mesh.triangles.push_back(1);
    mesh.triangles.push_back(2);
    
    mesh.triangles.push_back(0);
    mesh.triangles.push_back(2);
    mesh.triangles.push_back(3);
    
}
