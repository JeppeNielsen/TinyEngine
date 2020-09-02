//
//  ComponentView.h
//  Tiny
//
//  Created by Jeppe Nielsen on 06/11/2019.
//  Copyright © 2019 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include "ComponentContainer.hpp"
#include "TupleHelper.hpp"
#include "HasMethodHelper.hpp"

namespace Tiny {
    namespace Internal {
        HAS_METHOD(SetComponents)
        HAS_METHOD(IsComponentView)
    }

    template<typename ...T>
    struct ComponentView {
        using Components = std::tuple<ComponentContainer<std::remove_const_t<T>>*...>;
        
        template<typename O>
        constexpr std::tuple<O*> GetComponentType(const O* ptr) const {
            return std::make_tuple((O*)nullptr);
        }
        
        template<typename O>
        constexpr std::tuple<O*> GetComponentType(O* ptr) const {
            return std::make_tuple((O*)1);
        }

        constexpr std::tuple<T*...> GetComponentViewTypes() {
            return std::tuple_cat(GetComponentType((T*)nullptr)...);
        }
        
        void IsComponentView() {
            
        }
        
        Components componentsPtrs;
        template<typename Components>
        void SetComponents(Components& components) {
            TupleHelper::Iterate(componentsPtrs, [this, &components](auto ptr) {
                using ComponentType = std::remove_const_t<std::remove_pointer_t<decltype(ptr)>>;
                std::get<decltype(ptr)>(componentsPtrs) = &std::get<ComponentType>(components);
            });
        }
        
        template<typename O>
        const O& Get(const GameObject gameObject, const O* ptr) const {
            return
            (const O&)std::get<ComponentContainer<std::remove_const_t<O>>*>(componentsPtrs)->GetConst(gameObject);
        }
        
        template<typename O>
        O& Get(const GameObject gameObject, O* ptr) const {
            return
            (O&)std::get<ComponentContainer<std::remove_const_t<O>>*>(componentsPtrs)->Get(gameObject);
        }
       
        template<typename Func>
        void GetComponents(const GameObject gameObject, Func&& func) const {
            const int size = sizeof...(T);
        
            bool contains[] { std::get<ComponentContainer<std::remove_const_t<T>>*>(componentsPtrs)->gameObjects.Contains(gameObject)... };
            for(int i=0; i<size; ++i) {
                if (!contains[i]) {
                    return;
                }
            }
            //func(std::get<ComponentContainer<std::remove_const_t<T>>*>(componentsPtrs)->Get(gameObject)...);
            func(Get(gameObject, (T*)nullptr)...);
        }
        
        template<typename ComponentType>
        bool HasComponentViewType() {
            return TupleHelper::HasType<ComponentType, std::tuple<T...> >::value;
        }
    };
}
