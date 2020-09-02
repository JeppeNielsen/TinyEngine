//
//  TestComponentContainer.cpp
//  Tiny
//
//  Created by Jeppe Nielsen on 01/11/2019.
//  Copyright © 2019 Jeppe Nielsen. All rights reserved.
//

#include "TestComponentContainer.hpp"
#include "ComponentContainer.hpp"

using namespace Tiny::Tests;

void TestComponentContainer::Run() {

    struct Position {
        float x;
        float y;
    };

    RunTest("Create",[] () {
        ComponentContainer<Position> container;
        GameObject go = 0;
        container.Create(go);
        return container.elements.size() == 1;
    });

    RunTest("Destroy",[] () {
        ComponentContainer<Position> container;
        GameObject go = 0;
        container.Create(go);
        bool wasOne = container.elements.size() == 1;
        container.Remove(go);
        return container.elements.empty() && wasOne;
    });

    RunTest("Reference",[] () {
        ComponentContainer<Position> container;
        GameObject go1 = 0;
        GameObject go2 = 1;
        container.Create(go1);
        container.Reference(go2, go1);
        return &container.Get(go1) == &container.Get(go2);
    });
    
    RunTest("Create add to changedThisFrame",[] () {
        ComponentContainer<Position> container;
        GameObject go1 = 0;
        container.Create(go1);
        return container.changedThisFrame.objects.size() == 1;
    });
    
    RunTest("Get, adds to changedThisFrame",[] () {
        ComponentContainer<Position> container;
        GameObject go1 = 0;
        container.Create(go1);
        container.Get(go1);
        return container.changedThisFrame.objects.size() == 1;
    });
    
    RunTest("Double get only adds one entry in changedThisFrame",[] () {
        ComponentContainer<Position> container;
        GameObject go1 = 0;
        container.Create(go1);
        container.Get(go1);
        container.Get(go1);
        return container.changedThisFrame.objects.size() == 1;
    });
    
    RunTest("GetConst doesn't add to changedThisFrame",[] () {
        ComponentContainer<Position> container;
        GameObject go1 = 0;
        container.Create(go1);
        container.changedThisFrame.Clear();
        container.GetConst(go1);
        return container.changedThisFrame.objects.size() == 0;
    });
    
    RunTest("Reference also adds to changedThisFrame",[] () {
        ComponentContainer<Position> container;
        GameObject go1 = 0;
        GameObject go2 = 1;
        
        container.Create(go1);
        container.Reference(go2, go1);
        
        return container.changedThisFrame.objects.size() == 2;
    });
    
    RunTest("Get also adds changedThisFrame for references",[] () {
        ComponentContainer<Position> container;
        GameObject go1 = 0;
        GameObject go2 = 1;
        
        container.Create(go1);
        container.Reference(go2, go1);
        
        container.changedThisFrame.Clear();
        
        container.Get(go1);
        
        return container.changedThisFrame.objects.size() == 2;
    });

    RunTest("Remove referenced will not destroy element",[] () {
        ComponentContainer<Position> container;
        GameObject go1 = 0;
        GameObject go2 = 1;
        container.Create(go1);
        container.Reference(go2, go1);
        
        bool wasOne = container.elements.size() == 1;
        
        container.Remove(go1);
        
        bool stillOne = container.elements.size() == 1;
        
        container.Remove(go2);
        
        bool isNone = container.elements.empty();
        
        return wasOne && stillOne && isNone;
    });

    RunTest("Create variadic version",[] () {
        ComponentContainer<Position> container;
        GameObject go1 = 0;
        container.Create(go1, 1.0f, 2.0f);
        return container.Get(go1).x == 1.0f &&
               container.Get(go1).y == 2.0f;
    });
    
    RunTest("Remove element above",[] () {
        ComponentContainer<Position> container;
        GameObject go1 = 6;
        GameObject go2 = 7;
        container.Create(go1);
        container.Create(go2);
        
        container.Get(go2).x = 1.0f;
        
        container.Remove(go1);
        
        return container.Get(go2).x == 1.0f;
    });
    
    RunTest("Remove element above, two references inbetween",[] () {
        ComponentContainer<Position> container;
        GameObject go1 = 6;
        GameObject go2 = 7;
        container.Create(go1);
        
        
        container.Create(3);
        container.Reference(4, 3);
        
        container.Create(go2);

        container.Get(go2).x = 1.0f;
        
        container.Remove(go1);
        
        return container.Get(go2).x == 1.0f;
    });
    
    RunTest("Remove element above two references",[] () {
        ComponentContainer<Position> container;
        GameObject go1 = 0;
        GameObject go2 = 1;
        GameObject go3 = 2;
        container.Create(go1);
        container.Create(go2);
        container.Reference(go3, go2);
        
        container.Remove(go1);
        
        return &container.Get(go2) == &container.Get(go3);
    });
    
    RunTest("Remove elements in random order, two references inbetween",[] () {
        ComponentContainer<Position> container;
        GameObject go1 = 6;
        GameObject go2 = 7;
        container.Create(go1);
        
        
        container.Create(3);
        container.Reference(4, 3);
        
        container.Create(go2);

        container.Get(go2).x = 1.0f;
        
        container.Remove(go1);
        container.Remove(go2);
        container.Remove(3);
        container.Remove(4);
        
        return container.elements.size() == 0;
    });
}
