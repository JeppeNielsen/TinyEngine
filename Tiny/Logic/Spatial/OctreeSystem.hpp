//
//  QuadTreeSystem.hpp
//  Tiny
//
//  Created by Jeppe Nielsen on 26/07/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include "ECS.hpp"
#include "WorldBoundingBox.hpp"
#include "Octree.hpp"
#include <deque>

namespace Tiny {
    template<typename ...T>
    struct OctreeSystem : Tiny::SystemChangedGameObject<const WorldBoundingBox, T...>{
        
        OctreeSystem() {
            octree.SetBoundingBox({{0,0,0}, {100000,100000,100000}});
            defaultNode.node = nullptr;
        }
    
        void Update(Tiny::GameObject gameObject, const WorldBoundingBox& worldBoundingBox, T& ... rest) {
            if (gameObject >= nodes.size()) {
                nodes.resize(gameObject + 1, defaultNode);
            }
            
            auto& node = nodes[gameObject];
            node.data = gameObject;
            node.box = worldBoundingBox.bounds;
            
            if (!node.node) {
                octree.Insert(node);
            } else {
                octree.Move(node);
            }
        }
        
        void GameObjectRemoved(Tiny::GameObject gameObject) {
            if (gameObject >= nodes.size()) {
                return;
            }
            
            auto& node = nodes[gameObject];
            octree.Remove(node);
        }
        
        
        void Query(const BoundingFrustum& frustum, std::vector<Tiny::GameObject> &gameObjects) const {
            octree.Get(frustum, gameObjects);
        }
        
        void Query(const Ray& ray, std::vector<Tiny::GameObject> &gameObjects) const {
            octree.Get(ray, gameObjects);
            //octree.GetRecursive(gameObjects);
        }

        Octree<Tiny::GameObject> octree;
        std::deque<OctreeNode<Tiny::GameObject>> nodes;
        OctreeNode<Tiny::GameObject> defaultNode;
   };
}
