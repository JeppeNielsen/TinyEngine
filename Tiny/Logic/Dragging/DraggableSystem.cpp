//
//  DraggableSystem.cpp
//  TinyEditor
//
//  Created by Jeppe Nielsen on 23/09/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#include "DraggableSystem.hpp"

using namespace Tiny;

void DraggableSystem::Update(Draggable &draggable,
                             const Pickable &pickable,
                             const WorldTransform &worldTransform,
                             LocalTransform &localTransform) {
    
    if (!draggable.isDragging) {
        if (pickable.down.size()>0) {
            auto& downEvent = pickable.down[0];
            draggable.dragEvent = downEvent;
            draggable.isDragging = true;
            draggable.originPlane = Plane(downEvent.worldNormal, downEvent.worldPosition);
            vec4 downPositionInLocalSpace = vec4(downEvent.worldPosition, 1.0f);
            draggable.offset = worldTransform.worldInverse * downPositionInLocalSpace;
        }
    }
    
    for(auto& e : pickable.up) {
        if (e.touch.index == draggable.dragEvent.touch.index) {
            draggable.isDragging = false;
            break;
        }
    }
    
    if (draggable.isDragging) {
        auto ray = draggable.dragEvent.camera->GetRay(*draggable.dragEvent.cameraTransform, screenSize, draggable.dragEvent.input->touchPosition[draggable.dragEvent.touch.index].position);
        
        float distance;
     
        if (draggable.originPlane.IntersectsRay(ray, &distance)) {
            vec3 worldPosition = ray.position + ray.direction * distance;
            vec4 worldPosition4 = vec4(worldPosition, 1.0f);
            vec4 localPosition = worldTransform.worldInverse * worldPosition4;
            localPosition -= vec4(draggable.offset,0.0f);
            
            mat4 localToParent = localTransform.GetLocalToParent();
            localTransform.position = localToParent * localPosition;
        }
    }
    
}
