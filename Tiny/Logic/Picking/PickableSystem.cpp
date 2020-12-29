//
//  PickableSystem.cpp
//  Tiny
//
//  Created by Jeppe Nielsen on 21/08/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#include "PickableSystem.hpp"

using namespace Tiny;

void PickableSystem::Initialize(PickableOctreeSystem &octreeSystem) {
    this->octreeSystem = &octreeSystem;
}

void PickableSystem::Update(const WorldTransform &transform, const Camera &camera, const Input& input) {
    
    for(auto& resetPickable : resetPickables) {
        GetComponents(resetPickable.gameObject, [](Pickable& pickable, const Mesh& mesh, const WorldTransform& worldTransform) {
            pickable.down.clear();
            pickable.up.clear();
            pickable.clicked.clear();
        });
    }
    
    for(auto& touchDown : input.touchesDown) {
        TouchDown(transform, camera, input, touchDown);
    }
    
    resetPickables = activePickables;
    
    for(auto& touchUp : input.touchesUp) {
        TouchUp(transform, camera, input, touchUp);
    }
}
                 
void PickableSystem::TouchDown(const WorldTransform &transform, const Camera &camera, const Input &input, const InputTouch& touch) {
    
    auto touchPosition = input.touchPosition[touch.index];
    
    Ray ray = camera.GetRay(transform, screenSize, touchPosition.position);
    
    std::vector<GameObject> downs;
    octreeSystem->Query(ray, downs);
    
    for(auto down : downs) {
        
        GetComponents(down, [down, &transform, &camera, &input, &touch, &ray, this](Pickable& pickable, const Mesh& mesh, const WorldTransform& worldTransform) {
           
            Ray localRay = ray;
            localRay.Transform(worldTransform.worldInverse);
            IntersectionResult result;
            if (intersector.TryIntersect(mesh, localRay, result)) {
                
                PickEvent e(transform, camera, input);
                e.touch = touch;
                e.touchPosition = input.touchPosition[touch.index];
                e.worldPosition = ray.position + ray.direction * result.distance;
                e.worldNormal = result.normal;
                e.object = down;
                
                pickable.down.push_back(e);
            }
        });
        activePickables.push_back({ touch, down });
    }
}
                            
void PickableSystem::TouchUp(const WorldTransform &transform, const Camera &camera, const Input &input, const InputTouch& touch) {
    
    auto touchPosition = input.touchPosition[touch.index];
    
    Ray ray = camera.GetRay(transform, screenSize, touchPosition.position);
    
    std::vector<GameObject> ups;
    octreeSystem->Query(ray, ups);
    
    for(auto& activePickable : activePickables) {
        if (activePickable.touch.index == touch.index) {
            
            PickEvent e(transform, camera, input);
            e.touch = touch;
            e.touchPosition = input.touchPosition[touch.index];
            e.worldPosition = {0,0,0};
            e.object = activePickable.gameObject;
            
            bool clicked = std::find(ups.begin(), ups.end(), activePickable.gameObject) != ups.end();
           
            GetComponents(activePickable.gameObject, [clicked, &e, &input, &touch, &ray, this](Pickable& pickable, const Mesh& mesh, const WorldTransform& worldTransform) {
                                 
                pickable.up.push_back(e);
                
                if (clicked) {
                    
                    Ray localRay = ray;
                    localRay.Transform(worldTransform.worldInverse);
                    
                    IntersectionResult result;
                    if (intersector.TryIntersect(mesh, localRay, result)) {
                       
                        PickEvent clickPickEvent = e;
                        clickPickEvent.worldPosition = ray.position + ray.direction * result.distance;
                        clickPickEvent.worldNormal = result.normal;
                        
                        pickable.down.push_back(clickPickEvent);
                    }
                }
            });
            
        }
    }
    
    activePickables.erase(std::remove_if(activePickables.begin(), activePickables.end(), [&touch](auto& activePickable) {
        return activePickable.touch.index == touch.index;
    }), activePickables.end());
}
                            
