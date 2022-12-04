//
//  ArchetypeContainer.hpp
//  ECS
//
//  Created by Jeppe Nielsen on 26/08/2022.
//

#pragma
#include <vector>
#include <tuple>
#include "GameObjectDatabase.hpp"
#include "GameObjectCollection.hpp"
#include "ReferenceComponent.hpp"
#include "TupleHelper.hpp"

namespace Tiny {

struct ArchetypeContainerBase {
    virtual ~ArchetypeContainerBase() {}
    virtual GameObject Create() = 0;
    virtual void Remove(const GameObject gameObject) = 0;
};

template<typename ...T>
struct ArchetypeContainer : ArchetypeContainerBase {
    using Components = std::tuple<T...>;
    std::vector<Components> components;
    GameObjectDatabase database;
    GameObjectCollection objects;
    
    GameObject Create() override {
        components.push_back({});
        auto gameObject = database.Create();
        objects.Add(gameObject);
        return gameObject;
    }
    
    void Remove(const GameObject gameObject) override {
        assert(objects.Contains(gameObject));
        auto index = objects.Get(gameObject);
        auto lastIndex = objects.Get(objects.Last());
        std::swap(components[index], components[lastIndex]);
        components.pop_back();
        objects.Remove(gameObject);
    }
    
    Components& GetComponents(const GameObject gameObject) {
        assert(objects.Contains(gameObject));
        auto index = objects.Get(gameObject);
        return components[index];
    }
    
    void SetTypeIndex(const std::uint32_t typeIndex) {
        database.SetTypeIndex(typeIndex);
    }
    
    template<typename TComponent>
    static constexpr auto& GetComponent(Components& components) {
        using DirectComponent = std::remove_const_t<std::remove_reference_t<TComponent>>;
        if constexpr (TupleHelper::tuple_contains_type<ReferenceComponent<DirectComponent>, Components>::value) {
            return std::get<ReferenceComponent<DirectComponent>>(components).value;
        } else {
            return std::get<DirectComponent>(components);
        }
    }
    
    template<typename Ret, typename Type, typename... Args>
    using MethodPtr = Ret(Type::*)(Args...);
    
    template <typename Ret, typename Type, typename... Args>
    void Invoke(MethodPtr<Ret, Type, Args...> ptr, Type* instance) {
        for (int i = 0; i < components.size(); ++i) {
            auto& component = components[i];
            //std::invoke(ptr, instance, (std::get<std::remove_const_t<std::remove_reference_t<Args>>>(component))...);
            std::invoke(ptr, instance, GetComponent<Args>(component)...);
        }
    }
    
};

}
