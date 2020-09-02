//
//  SystemBase.h
//  Tiny
//
//  Created by Jeppe Nielsen on 22/02/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include "TupleHelper.hpp"
#include "GameObjectCollection.hpp"
#include "ComponentContainer.hpp"
#include "SystemDependencies.hpp"
#include "SceneModifier.hpp"
#include "HasMethodHelper.hpp"

namespace Tiny {

namespace Internal {
    HAS_METHOD(GameObjectRemoved);
    HAS_METHOD(EnableConcurrency);
}

template<typename...T>
struct SystemBase {

    template<typename O>
    constexpr std::tuple<O*> GetComponentType(const O* ptr) const {
        return std::make_tuple((O*)nullptr);
    }
    
    template<typename O>
    constexpr std::tuple<O*> GetComponentType(O* ptr) const {
        return std::make_tuple((O*)1);
    }

    constexpr std::tuple<T*...> GetComponentTypes() {
        return std::tuple_cat(GetComponentType((T*)nullptr)...);
    }
    
    template<typename ComponentType>
    constexpr static bool HasComponentType() {
        return TupleHelper::HasType<ComponentType, std::tuple<T...> >::value;
    }

    template<typename O, typename Components>
    constexpr const O& Get(const GameObject gameObject, Components& components, const O* ptr) const {
        return (const O&)std::get<ComponentContainer<std::remove_const_t<O>>>(components).GetConst(gameObject);
    }
    
    template<typename O, typename Components>
    constexpr O& Get(const GameObject gameObject, Components& components, O* ptr) const {
        return (O&)((ComponentContainer<std::remove_const_t<O>>&)std::get<ComponentContainer<std::remove_const_t<O>>>(components)).GetNoChange(gameObject);
    }
   
    template<typename Components>
    constexpr std::tuple<T&...> GetComponentValuesFromGameObject(const GameObject gameObject, Components& components) const {
        return std::tie(Get(gameObject, components, (T*)nullptr)...);
    }
    
    template<typename Components>
    constexpr bool GameObjectContainsAll(const GameObject gameObject, Components& components) const {
        const int numElements = sizeof...(T);
        
        bool contains[] { std::get<ComponentContainer<std::remove_const_t<T>>>(components).gameObjects.Contains(gameObject)... };
        for(int i=0; i<numElements; ++i) {
            if (!contains[i]) {
                return false;
            }
        }
        return true;
    }
    
    template<typename Components>
    constexpr void TryAddGameObject(const GameObject gameObject, Components& components) {
        if (objects.Contains(gameObject)) return;
        if (!GameObjectContainsAll(gameObject, components)) return;
        objects.Add(gameObject);
    }
    
    template<typename Components>
    constexpr void TryRemoveGameObject(const GameObject gameObject, Components& components) {
        if (!objects.Contains(gameObject)) return;
        objects.Remove(gameObject);
    }
    
    template<typename O, typename Components>
    constexpr void ChangeComponent(const GameObject gameObject, Components& components, const O* ptr) const {
        /*empty*/ // no change for const components
    }
    
    template<typename O, typename Components>
    constexpr void ChangeComponent(const GameObject gameObject, Components& components, O* ptr) const {
        ((ComponentContainer<std::remove_const_t<O>>&)std::get<ComponentContainer<std::remove_const_t<O>>>(components)).SetChanged(gameObject);
    }
    
    template<typename Components>
    constexpr void ChangeComponents(const GameObject gameObject, Components& components) const {
        using expander = int[];
        (void) expander { 0, ((void)ChangeComponent(gameObject, components, (T*)nullptr),0)... };
    }
    
    template<typename Components>
    constexpr const GameObjectCollection::Objects& GetChangedObjects(const Components& components) {
        const int numElements = sizeof...(T);
        
        const GameObjectCollection::Objects* objects[] {
            &std::get<ComponentContainer<std::remove_const_t<T>>>(components).changedThisFrame.objects...
        };
        
        if (numElements == 1) {
            return *objects[0];
        }
        
        int singleIndexWithChanges = 0;
        int numContainersWithChanges = 0;
        for(int i=0; i<numElements; ++i) {
            if (objects[i]->size() > 0) {
                ++numContainersWithChanges;
                if (numContainersWithChanges > 1) {
                    break;
                }
                singleIndexWithChanges = i;
            }
        }
        
        if (numContainersWithChanges <= 1) {
            return *objects[singleIndexWithChanges];
        }
        
        changedObjects.Clear();
        for(int i = 0; i<numElements; ++i) {
            const auto& list = *objects[i];
            for(auto object : list) {
                if (!changedObjects.Contains(object)) {
                    changedObjects.Add(object);
                }
            }
        }
        
        return changedObjects.objects;
    }
    
    GameObjectCollection objects;
    GameObjectCollection changedObjects;
    
};

}
